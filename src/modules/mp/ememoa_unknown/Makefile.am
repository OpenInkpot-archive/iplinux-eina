MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = \
-I. \
-I$(top_srcdir)/src/include \
-I$(top_builddir)/src/include \
@EINA_CPPFLAGS@ \
@EINA_CFLAGS@ \
@EMEMOA_CFLAGS@ \
@EFL_EINA_BUILD@

if EINA_BUILD_EMEMOA_UNKNOWN
if !EINA_STATIC_BUILD_EMEMOA_UNKNOWN

controllerdir = $(libdir)/eina/modules/mp/ememoa_unknown/$(MODULE_ARCH)
controller_LTLIBRARIES = module.la

module_la_SOURCES = \
eina_ememoa_unknown.c

module_la_LIBADD       = $(top_builddir)/src/lib/libeina.la @EMEMOA_LIBS@ @EINA_LIBS@
module_la_LDFLAGS      = -no-undefined @lt_enable_auto_import@ -module -avoid-version
module_la_LIBTOOLFLAGS = --tag=disable-static

endif
endif

clean-local:
	rm -rf *.gcno
