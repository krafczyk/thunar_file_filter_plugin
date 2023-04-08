//#include <stdio.h>
//#include <glib-object.h>
//#include <thunarx/thunarx.h>
//#include <gtk/gtk.h>
//#include <gio/gio.h>

#include "file_filter_plugin.h"


/* Plugin initialization and shutdown functions */
G_MODULE_EXPORT void thunar_extension_initialize (ThunarxProviderPlugin *plugin);
G_MODULE_EXPORT void thunar_extension_shutdown (void);
G_MODULE_EXPORT void thunar_extension_list_types (const GType** types, gint* n_types);

static GType type_list[1];

void thunar_extension_initialize (ThunarxProviderPlugin *plugin) {
  const gchar* mismatch;

  /* verify that the thunarx versions are compatible */
  mismatch = thunarx_check_version (THUNARX_MAJOR_VERSION, THUNARX_MINOR_VERSION, THUNARX_MICRO_VERSION);
  if (G_UNLIKELY (mismatch != NULL)) {
      g_warning ("Version mismatch: %s", mismatch);
      return;
  }

  #ifdef G_ENABLE_DEBUG
  g_messgae("Initializing file_filter_plugin extension");
  #endif

  /* register types provided by the plugin */
  my_thunar_plugin_register_type (G_TYPE_MODULE (plugin));

  /* setup the plugin provider type list */
  type_list[0] = my_thunar_plugin_get_type ();
}

void thunar_extension_shutdown (void) {
  // Perform any cleanup for your plugin here
  #ifdef G_ENABLE_DEBUG
  g_message("Shutting down file_filter_plugin plugin");
  #endif
}

void thunar_extension_list_types (const GType **types, gint *n_types) {
  *types = type_list;
  *n_types = G_N_ELEMENTS (type_list);
}



///////



static void my_thunar_plugin_menu_provider_init (ThunarxMenuProviderIface *iface);

G_DEFINE_DYNAMIC_TYPE_EXTENDED (FileFilterProvider, my_thunar_plugin, G_TYPE_OBJECT, 0,
                                THUNARX_IMPLEMENT_INTERFACE_DYNAMIC (THUNARX_TYPE_MENU_PROVIDER,
                                                                     my_thunar_plugin_menu_provider_init))

/* Function to show a dialog for entering the regex pattern */
static void show_filter_dialog (ThunarxFileInfo *file_info, GtkWidget *parent) {
  // Create the dialog
  GtkWidget *dialog = gtk_dialog_new_with_buttons ("Filter files by regex",
                                                   GTK_WINDOW (parent),
                                                   GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   "_Close", GTK_RESPONSE_ACCEPT,
                                                   NULL);

  // Create the content area
  GtkWidget *content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));

  // Create a label and entry
  GtkWidget *label = gtk_label_new ("Enter regex pattern:");
  GtkWidget *entry = gtk_entry_new ();

  // Add the widgets to the content area
  gtk_box_pack_start (GTK_BOX (content_area), label, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (content_area), entry, TRUE, TRUE, 2);

  // Show all widgets
  gtk_widget_show_all (dialog);

  // Wait for the response and retrieve the pattern
  gint response = gtk_dialog_run (GTK_DIALOG (dialog));
  if (response == GTK_RESPONSE_ACCEPT) {
    const gchar *pattern = gtk_entry_get_text (GTK_ENTRY (entry));
    // Apply the regex pattern to filter the files
  }

  // Destroy the dialog
  gtk_widget_destroy (dialog);
}

/* Callback function for the context menu item */
static void on_filter_files_activate (GtkMenuItem *item, ThunarxFileInfo *file_info) {
  GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET (item));
  show_filter_dialog (file_info, toplevel);
}

/* Implementation of the menu provider interface */
static GList *my_thunar_plugin_get_file_actions (ThunarxMenuProvider *menu_provider,
                                                 GtkWidget           *window,
                                                 GList               *files) {
  if (files == NULL || g_list_length (files) != 1)
    return NULL;

  ThunarxFileInfo *file_info = THUNARX_FILE_INFO (files->data);

  // Create the context menu item
  GtkWidget *filter_files_item = gtk_menu_item_new_with_label ("Filter files by regex");
  g_signal_connect (filter_files_item, "activate", G_CALLBACK (on_filter_files_activate), file_info);

  // Return the item as a single-element GList
  return g_list_append (NULL, filter_files_item);
}

static void my_thunar_plugin_menu_provider_init (ThunarxMenuProviderIface *iface) {
  printf("my_thunar_plugin_menu_provider_init Initializing menu provider interface for plugin\n");
  iface->get_file_menu_items = my_thunar_plugin_get_file_actions;
}

