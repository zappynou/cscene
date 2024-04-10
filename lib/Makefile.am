lib_LTLIBRARIES = libcscene.la

libcscene_la_SOURCES = \
	version.c

libcscene_la_CFLAGS = \
	$(GTK4_CFLAGS)

libcscene_la_LDFLAGS = \
	$(GTK4_LIBS) \
	-no-undefined \
	-revision=$(PACKAGE_VERSION_STRING)
