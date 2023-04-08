#ifndef __FILE_FILTER_PROVIDER_H__
#define __FILE_FILTER_PROVIDER_H__

#include <thunarx/thunarx.h>

G_BEGIN_DECLS;

typedef struct _FileFilterProviderClass FileFilterProviderClass;
typedef struct _FileFilterProvider FileFilterProvider;

#define FILE_FILTER_TYPE_PROVIDER             (file_filter_provider_get_type ())
#define FILE_FILTER_PROVIDER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), FILE_FILTER_TYPE_PROVIDER, FileFilterProvider))
#define FILE_FILTER_PROVIDER_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), FILE_FILTER_TYPE_PROVIDER, FileFilterProviderClass))
#define FILE_FILTER_IS_PROVIDER(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), FILE_FILTER_TYPE_PROVIDER))
#define FILE_FILTER_IS_PROVIDER_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), FILE_FILTER_TYPE_PROVIDER))
#define FILE_FILTER_PROVIDER_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), FILE_FILTER_TYPE_PROVIDER, FileFilterProviderClass))

GType file_filter_provider_get_type      (void) G_GNUC_CONST G_GNUC_INTERNAL;
void  file_filter_provider_register_type (ThunarxProviderPlugin *plugin) G_GNUC_INTERNAL;


G_END_DECLS;

#endif // __FILE_FILTER_PROVIDER_H__