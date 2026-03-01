--- config_dialog.c.orig	2025-07-31 09:39:34 UTC
+++ config_dialog.c
@@ -37,6 +37,9 @@
 #include "waveform.h"
 #include "config_dialog.h"
 
+#pragma GCC diagnostic push
+#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
+
 void
 on_button_config (GtkMenuItem *menuitem, gpointer user_data)
 {
@@ -76,8 +79,6 @@ on_button_config (GtkMenuItem *menuitem, gpointer user
     GtkWidget *applybutton1;
     GtkWidget *cancelbutton1;
     GtkWidget *okbutton1;
-#pragma GCC diagnostic push
-#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
     waveform_properties = gtk_dialog_new ();
     gtk_window_set_transient_for (GTK_WINDOW (waveform_properties), GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(menuitem))));
     gtk_window_set_title (GTK_WINDOW (waveform_properties), "Waveform Properties");
@@ -311,6 +312,6 @@ on_button_config (GtkMenuItem *menuitem, gpointer user
         break;
     }
     gtk_widget_destroy (waveform_properties);
-#pragma GCC diagnostic pop
     return;
 }
+#pragma GCC diagnostic pop
