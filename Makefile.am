ACLOCAL_AMFLAGS = -I m4

SUBDIRS = include/cscene lib

if ENABLE_TESTS
SUBDIRS+= tests
endif

SUBDIRS+= src

##
# During installation on Windows target, we need all DLLs required by the
# built executables
install-data-local:
if ENABLE_WIN32
	$(top_srcdir)/utils/ResolveDeps.sh \
		$(DESTDIR)$(prefix) \
		$(DESTDIR)$(prefix)/bin
endif

##
# Build an archive with the executables.
.PHONY: package
package: install
	tar cJf \
		cscene-$(PACKAGE_VERSION_STRING)-$(OS_HOST)-bin.tar.xz \
		-C $(DESTDIR) \
		.
	shasum \
		-a 256 \
		cscene-$(PACKAGE_VERSION_STRING)-$(OS_HOST)-bin.tar.xz \
		> cscene-$(PACKAGE_VERSION_STRING)-$(OS_HOST)-bin.tar.xz.SHA256SUM
