--- vumeter.c.orig	2025-07-31 09:52:18 UTC
+++ vumeter.c
@@ -390,6 +390,8 @@ on_config_changed (gpointer user_data, uintptr_t ctx)
     return 0;
 }
 
+#pragma GCC diagnostic push
+#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
 static void
 on_button_config (GtkMenuItem *menuitem, gpointer user_data)
 {
@@ -437,8 +439,6 @@ on_button_config (GtkMenuItem *menuitem, gpointer user
     GtkWidget *applybutton1;
     GtkWidget *cancelbutton1;
     GtkWidget *okbutton1;
-#pragma GCC diagnostic push
-#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
     vumeter_properties = gtk_dialog_new ();
     gtk_window_set_title (GTK_WINDOW (vumeter_properties), "vumeter Properties");
     gtk_window_set_type_hint (GTK_WINDOW (vumeter_properties), GDK_WINDOW_TYPE_HINT_DIALOG);
@@ -758,9 +758,9 @@ on_button_config (GtkMenuItem *menuitem, gpointer user
         break;
     }
     gtk_widget_destroy (vumeter_properties);
-#pragma GCC diagnostic pop
     return;
 }
+#pragma GCC diagnostic pop
 
 ///// vumeter vis
 void
@@ -830,12 +830,8 @@ vumeter_draw_retro (w_vumeter_t *w, cairo_t *cr, int w
 {
     if (!w->surf_png) {
         char path[PATH_MAX];
-        const char *home_dir = getenv ("HOME");
-        if (home_dir && strcmp(home_dir, "") == 0) {
-            home_dir = NULL;
-        }
-        const int sz = snprintf (path, PATH_MAX, "%s/vumeter.png", home_dir);
-        if (!home_dir || !path) {
+        if (snprintf (path, PATH_MAX, "%s/vumeter.png",
+          deadbeef->get_pixmap_dir()) < 0) { 
             return;
         }
         w->surf_png = cairo_image_surface_create_from_png (path);
