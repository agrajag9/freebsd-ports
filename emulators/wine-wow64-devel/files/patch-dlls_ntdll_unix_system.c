From 16dc8a447d18b510ed07cc1b79b2143f01cbf46d Mon Sep 17 00:00:00 2001
From: Katharine Chui <kwchuiaa@connect.ust.hk>
Date: Sat, 2 Mar 2024 12:40:11 +0100
Subject: [PATCH] Fix Cyberpunk 2077 spawning only one dispatcher thread in
 FreeBSD

Normally Cyberpunk 2077 spawns #cpu_threads of dispatcher threads.
However with Freebsd, since create_logical_proc_info was a stub,
the game would instead spawn a single dispatcher thread, causing
the game to just crawl.

Working around the issue by adding a barebone implementation of
create_logical_proc_info for FreeBSD so that the game would at
least get a thread count through ntdll.
---
 dlls/ntdll/unix/system.c | 92 ++++++++++++++++++++++++++++++++++++++++
 1 file changed, 92 insertions(+)

diff --git a/dlls/ntdll/unix/system.c b/dlls/ntdll/unix/system.c
index e9ed8b6f3a4..72dc12ba5a5 100644
--- dlls/ntdll/unix/system.c
+++ dlls/ntdll/unix/system.c
@@ -1329,6 +1329,98 @@ static NTSTATUS create_logical_proc_info(void)
     return STATUS_SUCCESS;
 }
 
+#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
+
+/*
+ * this is currently mostly a reduced clone of the macos implementation
+ * it only reports thread counts so that cb2077 don't spawn a single dispatch thread only, and would spawn #threads instead
+ * TODO list:
+ *   smt information
+ *   numa information
+ *   cache information
+ *   package count
+ * it is also tempting to rely on lscpu output, however that would make freebsd wine packaging dependent on lscpu, don't know if that's a good idea
+ * or perhaps go for cpuid directly? however that'd would introduce quite the amount of boiler plates
+ * yet another alternative would be to rely on /compat/linux/sys, however FreeBSD only lists the number of online cores without smt, numa, cache nor package information, and linux compat has to be enabled
+ */
+static NTSTATUS create_logical_proc_info(void)
+{
+    unsigned int pkgs_no, cores_no, lcpu_no, lcpu_per_core, cores_per_package;
+    ULONG_PTR all_cpus_mask = 0;
+    unsigned int i, p, j, k;
+    CACHE_DESCRIPTOR cache[10];
+
+    /* HW_NCPU works in FreeBSD */
+    lcpu_no = peb->NumberOfProcessors;
+
+    /* TODO assume one package */
+    pkgs_no = 1;
+
+    /* TODO assume no SMT */
+    /* physical core number can be fetch with sysctl kern.smp.cores */
+    cores_no = lcpu_no;
+
+    TRACE("%u logical CPUs from %u physical cores across %u packages\n",
+            lcpu_no, cores_no, pkgs_no);
+
+    lcpu_per_core = lcpu_no / cores_no;
+    cores_per_package = cores_no / pkgs_no;
+
+    for(p = 0; p < pkgs_no; ++p)
+    {
+        for(j = 0; j < cores_per_package && p * cores_per_package + j < cores_no; ++j)
+        {
+            ULONG_PTR mask = 0;
+            DWORD phys_core;
+
+            for(k = 0; k < lcpu_per_core; ++k) mask |= (ULONG_PTR)1 << (j * lcpu_per_core + k);
+
+            all_cpus_mask |= mask;
+
+            /* add to package */
+            if(!logical_proc_info_add_by_id( RelationProcessorPackage, p, mask ))
+                return STATUS_NO_MEMORY;
+
+            /* add new core */
+            phys_core = p * cores_per_package + j;
+            if(!logical_proc_info_add_by_id( RelationProcessorCore, phys_core, mask ))
+                return STATUS_NO_MEMORY;
+        }
+    }
+
+    /* TODO cache information */
+    memset(cache, 0, sizeof(cache));
+    cache[1].Level = 1;
+    cache[1].Type = CacheInstruction;
+    cache[1].Associativity = 8; /* reasonable default */
+    cache[1].LineSize = 0x40; /* reasonable default */
+    cache[2].Level = 1;
+    cache[2].Type = CacheData;
+    cache[2].Associativity = 8;
+    cache[2].LineSize = 0x40;
+    cache[3].Level = 2;
+    cache[3].Type = CacheUnified;
+    cache[3].Associativity = 8;
+    cache[3].LineSize = 0x40;
+    cache[4].Level = 3;
+    cache[4].Type = CacheUnified;
+    cache[4].Associativity = 12;
+    cache[4].LineSize = 0x40;
+    for(i = 0; i < 5; i++)
+    {
+        if(!logical_proc_info_add_cache( all_cpus_mask, &cache[i] ))
+            return STATUS_NO_MEMORY;
+    }
+
+    /* TODO numa infomration */
+    if(!logical_proc_info_add_numa_node( all_cpus_mask, 0 ))
+        return STATUS_NO_MEMORY;
+
+    logical_proc_info_add_group( lcpu_no, all_cpus_mask );
+
+    return STATUS_SUCCESS;
+}
+
 #else
 
 static NTSTATUS create_logical_proc_info(void)
-- 
GitLab

