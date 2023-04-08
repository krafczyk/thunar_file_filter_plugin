#include "file_filter_provider.h"

static void   file_filter_provider_menu_provider_init   (ThunarxMenuProviderIface *iface);
static void   file_filter_provider_finalize             (GObject                  *object);
static GList *file_filter_provider_get_file_menu_items  (ThunarxMenuProvider      *menu_provider,
                                                         GtkWidget                *window,
                                                         GList                    *files);
static GList *file_filter_provider_get_dnd_menu_items   (ThunarxMenuProvider      *menu_provider,
                                                         GtkWidget                *window,
                                                         ThunarxFileInfo          *folder,
                                                         GList                    *files);
static void   file_filter_provider_execute              (TapProvider              *tap_provider,
                                                         GPid                    (*action) (const gchar *folder,
                                                                                    GList       *files,
                                                                                    GtkWidget   *window,
                                                                                    GError     **error),
                                                         GtkWidget                *window,
                                                         const gchar              *folder,
                                                         GList                    *files,
                                                         const gchar              *error_message);
static void   file_filter_provider_child_watch          (GPid                      pid,
                                                         gint                      status,
                                                         gpointer                  user_data);

/* Implement a custom menu provider */
struct _FileFilterProviderClass {
  GObjectClass __parent__;
};

struct _FileFilterProvider {
  GObject __parent__;
};
