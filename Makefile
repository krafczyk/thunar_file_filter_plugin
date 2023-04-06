PLUGIN_NAME = file_filter_plugin
SOURCE_FILES = file_filter_plugin.c
CFLAGS = `pkg-config --cflags thunarx-3` -shared -fPIC
LIBS = `pkg-config --libs thunarx-3`

all: $(PLUGIN_NAME).so

$(PLUGIN_NAME).so: $(SOURCE_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(PLUGIN_NAME).so
