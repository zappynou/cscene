lib_LTLIBRARIES = libcscene.la

libcscene_la_SOURCES = \
	gui/gtk/scene-click.c \
	gui/gtk/scene-drag.c \
	gui/gtk/scene-scale.c \
	gui/gtk/scene.c \
	version.c

libcscene_la_CFLAGS = \
	$(GTK4_CFLAGS)

libcscene_la_LDFLAGS = \
	$(GTK4_LIBS) \
	-no-undefined \
	-revision=$(PACKAGE_VERSION_STRING)
