bin_PROGRAMS = run_unittests

run_unittests_SOURCES = \
	fff_symbols.cpp \
	test_version.cpp

run_unittests_CXXFLAGS =

run_unittests_CPPFLAGS = \
	$(CATCH2_CFLAGS)

run_unittests_LDADD = \
	$(top_builddir)/lib/libcscene.la \
	$(CATCH2_LIBS)
