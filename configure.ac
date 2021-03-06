##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
m4_define([v_maj], [0])
m4_define([v_min], [9])
m4_define([v_mic], [9])
m4_define([v_rev], m4_esyscmd([(svnversion "${SVN_REPO_PATH:-.}" | grep -v export || echo 0) | awk -F : '{printf("%s\n", $1);}' | tr -d ' :MSP\n']))
m4_if(v_rev, [0], [m4_define([v_rev], m4_esyscmd([git log 2> /dev/null | (grep -m1 git-svn-id || echo 0) | sed -e 's/.*@\([0-9]*\).*/\1/' | tr -d '\n']))])
##--   When released, remove the dnl on the below line
dnl m4_undefine([v_rev])
##--   When doing snapshots - change soname. remove dnl on below line
m4_define([relname], [ver-svn-06])
m4_define([v_rel], [-release relname])
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
m4_ifdef([v_rev], [m4_define([v_ver], [v_maj.v_min.v_mic.v_rev])],
[m4_define([v_ver], [v_maj.v_min.v_mic])])
m4_define([lt_rev], m4_eval(v_maj + v_min))
m4_define([lt_cur], v_mic)
m4_define([lt_age], v_min)
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
 
AC_INIT([eina], [v_ver], [enlightenment-devel@lists.sourceforge.net])
AC_PREREQ([2.59])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_ISC_POSIX

AM_INIT_AUTOMAKE([1.6 dist-bzip2])
AM_CONFIG_HEADER([config.h])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_LIBTOOL_WIN32_DLL
define([AC_LIBTOOL_LANG_CXX_CONFIG], [:])dnl
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])dnl
AC_PROG_LIBTOOL

##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
m4_ifdef([v_rev], , [m4_define([v_rev], [0])])
m4_ifdef([v_rel], , [m4_define([v_rel], [])])
AC_DEFINE_UNQUOTED(VMAJ, [v_maj], [Major version])
AC_DEFINE_UNQUOTED(VMIN, [v_min], [Minor version])
AC_DEFINE_UNQUOTED(VMIC, [v_mic], [Micro version])
AC_DEFINE_UNQUOTED(VREV, [v_rev], [Revison])
version_info="lt_rev:lt_cur:lt_age"
release_info="v_rel"
AC_SUBST(version_info)
AC_SUBST(release_info)
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##--##
VMAJ=v_maj
AC_SUBST(VMAJ)

### Needed information

requirement_eina=""

case "$host_os" in
   mingw32ce*)
      MODULE_ARCH="$host_os-$host_cpu"
      ;;
   *)
      MODULE_ARCH="$host_os-$host_cpu-$relname"
      ;;
esac
AC_SUBST(MODULE_ARCH)
AC_DEFINE_UNQUOTED(MODULE_ARCH, "${MODULE_ARCH}", "Module architecture")

case "$host_os" in
   mingw*)
      MODULE_EXT=".dll"
      ;;
   *)
      MODULE_EXT=".so"
      ;;
esac

AC_DEFINE_UNQUOTED(SHARED_LIB_SUFFIX, "${MODULE_EXT}", [Suffix for shared objects])

EFL_CHECK_CPU_MMX([have_mmx="yes"], [have_mmx="no"])
EFL_CHECK_CPU_SSE([have_sse="yes"], [have_sse="no"])
EFL_CHECK_CPU_SSE2([have_sse2="yes"], [have_sse2="no"])
EFL_CHECK_CPU_ALTIVEC([have_altivec="yes"], [have_altivec="no"])

EFL_CHECK_PTHREAD(["yes"],
   [have_pthread="yes"],
   [have_pthread="no"],
   [have_pthread_spinlock="yes"],
   [have_pthread_spinlock="no"])

### Additional options to configure

# Magic debug
AC_ARG_ENABLE([magic-debug],
   [AC_HELP_STRING([--disable-magic-debug], [disable magic debug of eina structure @<:@default=enabled@:>@])],
   [
    if test "x${enableval}" = "xyes" ; then
       have_magic_debug="yes"
    else
       have_magic_debug="no"
    fi
   ],
   [have_magic_debug="yes"])

AC_MSG_CHECKING([whether magic debug is enable])
AC_MSG_RESULT([${have_magic_debug}])

if test "x${have_magic_debug}" = "xyes" ; then
   EINA_CONFIGURE_MAGIC_DEBUG="#define EINA_MAGIC_DEBUG"
fi
AC_SUBST(EINA_CONFIGURE_MAGIC_DEBUG)

# Safety checks (avoid crashes on wrong api usage)
AC_ARG_ENABLE(safety-checks,
   [AC_HELP_STRING([--disable-safety-checks], [disable safety checks for NULL pointers and like. @<:@default=enabled@:>@])],
   [
    if test "x${enableval}" = "xyes" ; then
       have_safety_checks="yes"
    else
       have_safety_checks="no"
    fi
   ],
   [have_safety_checks="yes"])

AC_MSG_CHECKING(whether to do safety checking on api parameters)
AC_MSG_RESULT($have_safety_checks)

AM_CONDITIONAL(SAFETY_CHECKS, test "x$have_safety_checks" = "xyes")
if test "x$have_safety_checks" = "xyes"; then
  AC_DEFINE(EINA_SAFETY_CHECKS, 1, [disable safety checks for NULL pointers and like.])
  EINA_CONFIGURE_SAFETY_CHECKS="#define EINA_SAFETY_CHECKS"
fi
AC_SUBST(EINA_CONFIGURE_SAFETY_CHECKS)

with_max_log_level="<unset>"
AC_ARG_WITH(internal-maximum-log-level,
   [AC_HELP_STRING([--with-internal-maximum-log-level=NUMBER],
                   [limit eina internal log level to the given number, any call to EINA_LOG() with values greater than this will be compiled out, ignoring runtime settings, but saving function calls.])],
   [
    if test "x${withval}" != "xno"; then
       if echo "${withval}" | grep '^[[0-9]]\+$' >/dev/null 2>/dev/null; then
          AC_MSG_NOTICE([ignoring any EINA_LOG() with level greater than ${withval}])
          AC_DEFINE_UNQUOTED(EINA_LOG_LEVEL_MAXIMUM, ${withval}, [if set, logging is limited to this amount.])
          with_max_log_level="${withval}"
       else
          AC_MSG_ERROR([--with-internal-maximum-log-level takes a decimal number, got "${withval}" instead.])
       fi
    fi
    ], [:])

AC_ARG_ENABLE([amalgamation],
   [AC_HELP_STRING([--enable-amalgamation], [enable generation of one single file with all source code in it, helps compiler optimizations.])],
   [if test "x${enableval}" = "xyes"; then
       do_amalgamation="yes"
    else
       do_amalgamation="no"
    fi
   ],
   [do_amalgamation="no"]
)
AM_CONDITIONAL(EINA_AMALGAMATION, test "x${do_amalgamation}" = "xyes")

# Choose best memory pool
AC_ARG_ENABLE([default-mempool],
   [AC_HELP_STRING([--enable-default-mempool], [Default memory allocator could be faster for some computer. @<:@default=disabled@:>@])],
   [
    if test "x${enableval}" = "xyes"; then
       have_default_mempool="yes"
    else
       have_default_mempool="no"
    fi
   ],
   [have_default_mempool="no"]
)
AC_MSG_CHECKING([whether to use default mempool allocator])
AC_MSG_RESULT([${have_default_mempool}])

if test "x${have_default_mempool}" = "xyes" ; then
   EINA_CONFIGURE_DEFAULT_MEMPOOL="#define EINA_DEFAULT_MEMPOOL"
fi
AC_SUBST(EINA_CONFIGURE_DEFAULT_MEMPOOL)

# Report stringshare usage
AC_ARG_ENABLE([stringshare-usage],
   [AC_HELP_STRING([--enable-stringshare-usage], [Report stringshare usage on stringshare shutdown. @<:@default=disabled@:>@])],
   [
    if test "x${enableval}" = "xyes"; then
       have_stringshare_usage="yes"
    else
       have_stringshare_usage="no"
    fi
   ],
   [have_stringshare_usage="no"]
)
AC_MSG_CHECKING([whether to report stringshare usage])
AC_MSG_RESULT([${have_stringshare_usage}])

if test "x${have_stringshare_usage}" = "xyes"; then
   AC_DEFINE(EINA_STRINGSHARE_USAGE, 1, [Report Eina stringshare usage pattern])
fi

# Check if we want to benchmark on real data
enable_benchmark_e17="no"
AC_ARG_ENABLE([e17],
   [AC_HELP_STRING([--enable-e17], [enable heavy benchmark @<:@default=no@:>@])],
   [
    if test "x${enableval}" = "xyes" ; then
       enable_benchmark_e17="yes"
    else
       enable_benchmark_e17="no"
    fi
   ],
   [enable_benchmark_e17="no"])

AC_MSG_CHECKING([whether e17 real data benchmark are built])
AC_MSG_RESULT([${enable_benchmark_e17}])

AM_CONDITIONAL(EINA_ENABLE_BENCHMARK_E17, test "x${enable_benchmark_e17}" = "xyes")


### Checks for programs
AC_PROG_CC

# pkg-config
PKG_PROG_PKG_CONFIG

# Check whether pkg-config supports Requires.private
if $PKG_CONFIG --atleast-pkgconfig-version 0.22; then
   pkgconfig_requires_private="Requires.private"
else
   pkgconfig_requires_private="Requires"
fi
AC_SUBST(pkgconfig_requires_private)

# doxygen program for documentation building

EFL_CHECK_DOXYGEN([build_doc="yes"], [build_doc="no"])


### Checks for libraries

# Evil library for compilation on Windows CE

EFL_EINA_BUILD=""
case "$host_os" in
   mingw*)
      PKG_CHECK_MODULES([EVIL], [evil])
      AC_DEFINE(HAVE_EVIL, 1, [Set to 1 if evil package is installed])
      requirement_eina="evil"
      EFL_EINA_BUILD="-DEFL_EINA_BUILD"
   ;;
esac
AC_SUBST(EFL_EINA_BUILD)

# Check ememoa memory pool library

AC_ARG_ENABLE([ememoa],
   [AC_HELP_STRING([--enable-ememoa], [build ememoa memory pool module @<:@default=yes@:>@])],
   [
    if test "x${enableval}" = "xyes" ; then
       enable_ememoa="yes"
    else
       enable_ememoa="no"
    fi
   ],
   [enable_ememoa="yes"]
)
AC_MSG_CHECKING([whether to use ememoa for memory pool])
AC_MSG_RESULT([$enable_ememoa])

if test "x${enable_ememoa}" = "xyes" ; then
   PKG_CHECK_MODULES([EMEMOA],
      [ememoa >= 0.0.26 ],
      [enable_ememoa="yes"],
      [enable_ememoa="no"]
   )
fi

### Checks for header files
AC_HEADER_ASSERT
AC_HEADER_DIRENT
AC_HEADER_TIME

### Checks for types


### Checks for structures


### Checks for compiler characteristics
AC_C_CONST
AC_C_BIGENDIAN
AC_C_INLINE
AC_C___ATTRIBUTE__
AC_PROG_CC_STDC

EINA_CPPFLAGS=""
EINA_CFLAGS=""
case "$host_os" in
   mingw32ce*)
      EINA_CPPFLAGS="-D_WIN32_WCE=0x0420"
      EINA_CFLAGS="${EVIL_CFLAGS}"
      ;;
   mingw*)
      EINA_CPPFLAGS="-D_WIN32_WINNT=0x0501"
      EINA_CFLAGS="${EVIL_CFLAGS}"
      ;;
esac

m4_ifdef([v_mic],
   [
    EFL_COMPILER_FLAG([-Wall])
    EFL_COMPILER_FLAG([-W])
   ])

EFL_COMPILER_FLAG([-Wshadow])

AC_SUBST(EINA_CPPFLAGS)
AC_SUBST(EINA_CFLAGS)


### Checks for linker characteristics
EINA_LIBS=
lt_enable_auto_import=""
case "${host_os}" in
   mingw*)
      EINA_LIBS="-ldl ${EVIL_LIBS} -lm"
      lt_enable_auto_import="-Wl,--enable-auto-import"
   ;;
   dragonfly*|openbsd*)
      EINA_LIBS="-lm"
   ;;
   freebsd*|netbsd*)
      EINA_LIBS="-lrt -lm"
   ;;
   darwin*)
      EINA_LIBS="-lm"
   ;;
   cygwin*)
      EINA_LIBS="-ldl -lm"
   ;;
   *)
      EINA_LIBS="-ldl -lrt -lm"
   ;;
esac
AC_SUBST(EINA_LIBS)
AC_SUBST(lt_enable_auto_import)

EFL_LINKER_FLAG([-fno-strict-aliasing])


### Checks for library functions
AC_FUNC_ALLOCA
AC_CHECK_FUNCS(strlcpy)

#dlopen and dladdr
dlopen_libs=""
case "$host_os" in
   mingw*)
# managed by evil
      AC_DEFINE(HAVE_DLADDR)
      ;;
   *)
      AC_CHECK_FUNCS([dlopen], [res="yes"], [res="no"])
      if test "x${res}" = "xyes" ; then
         AC_CHECK_FUNCS([dladdr], [AC_DEFINE(HAVE_DLADDR)])
      else
         AC_CHECK_LIB([dl], [dlopen], [res="yes"], [res="no"])
         if test "x${res}" = "xyes" ; then
            AC_CHECK_LIB([dl], [dladdr], [AC_DEFINE(HAVE_DLADDR)])
            dlopen_libs="-ldl"
         else
            AC_MSG_ERROR([Cannot find dlopen])
         fi
      fi
      ;;
esac
AC_SUBST(dlopen_libs)

EFL_CHECK_FNMATCH([], [AC_MSG_ERROR([Cannot find fnmatch()])])

# iconv library
have_iconv="no"
AC_ARG_WITH([iconv-link],
   AC_HELP_STRING([--with-iconv-link=ICONV_LINK], [explicitly specify an iconv link option]),
   [
    LIBS="$withval $LIBS"
    have_iconv="yes"
   ])

AC_MSG_CHECKING(for explicit iconv link options)
if test "x${iconv_libs}" = "x" ; then
   AC_MSG_RESULT([no explicit iconv link option])
else
   AC_MSG_RESULT([$iconv_libs])
fi

if test "x${have_iconv}" = "xno" ; then
   AC_CHECK_HEADERS([iconv.h], [have_iconv="yes"])

   if test "x${have_iconv}" = "xyes" ; then
      AC_MSG_CHECKING([whether iconv() is in libc])
      
      AC_LINK_IFELSE(
         [AC_LANG_PROGRAM(
             [[
#include <stdlib.h>
#include <iconv.h>
             ]],
             [[
iconv_t ic;
size_t count = iconv(ic, NULL, NULL, NULL, NULL);
             ]])],
         [have_iconv="yes"],
         [have_iconv="no"])

      AC_MSG_RESULT([${have_iconv}])
   fi

   if test "x${have_iconv}" = "xno" ; then
      AC_MSG_CHECKING([whether iconv() is in libiconv.a])

      LIBS_save="${LIBS}"
      LIBS="-liconv $LIBS"
      AC_LINK_IFELSE(
         [AC_LANG_PROGRAM(
             [[
#include <stdlib.h>
#include <iconv.h>
             ]],
             [[
iconv_t ic;
size_t count;
count = iconv(ic, NULL, NULL, NULL, NULL);
             ]])],
         [have_iconv="yes"],
         [
          have_iconv="no"
          LIBS=${LIBS_save}
         ])

      AC_MSG_RESULT([${have_iconv}])
   fi

   if test "x${have_iconv}" = "xno" ; then
      AC_MSG_CHECKING([whether iconv() is in libiconv_plug.a])

      LIBS_save="${LIBS}"
      LIBS="-liconv_plug $LIBS"
      AC_LINK_IFELSE(
         [AC_LANG_PROGRAM(
             [[
#include <stdlib.h>
#include <iconv.h>
             ]],
             [[
iconv_t ic;
size_t count = iconv(ic, NULL, NULL, NULL, NULL);
             ]])],
         [have_iconv="yes"],
         [
          have_iconv="no"
          LIBS=${LIBS_save}
         ])

      AC_MSG_RESULT([${have_iconv}])
   fi
fi

if test "x${have_iconv}" = "xyes" ; then
   AC_DEFINE([HAVE_ICONV], [1], [Set to 1 if iconv library is installed])
fi


### Modules

if test "x${have_default_mempool}" = "xyes" ; then
   enable_chained_pool="no"
   enable_pass_through="static"
else
   enable_chained_pool="static"
   enable_pass_through="no"
fi

EINA_CHECK_MODULE([chained-pool],   [${enable_chained_pool}], [chained pool])
EINA_CHECK_MODULE([ememoa-fixed],   [${enable_ememoa}],       [ememoa fixed])
EINA_CHECK_MODULE([ememoa-unknown], [${enable_ememoa}],       [ememoa unknown])
EINA_CHECK_MODULE([fixed-bitmap],   [no],                     [fixed bitmap])
EINA_CHECK_MODULE([pass-through],   [${enable_pass_through}], [pass through])
EINA_CHECK_MODULE([buddy],          [no],                     [buddy])


### Make the debug preprocessor configurable

### Unit tests, coverage and benchmarking

EFL_CHECK_TESTS([enable_tests="yes"], [enable_tests="no"])

EFL_CHECK_COVERAGE([${enable_tests}], [enable_coverage="yes"], [enable_coverage="no"])
EINA_CFLAGS="${EINA_CFLAGS} ${EFL_COVERAGE_CFLAGS}"
EINA_LIBS="${EINA_LIBS} ${EFL_COVERAGE_LIBS}"
if test "x$enable_coverage" = "xyes" ; then
   EINA_CFLAGS="${EINA_CFLAGS} ${EFL_DEBUG_CFLAGS}"
fi

EFL_CHECK_BENCHMARK([enable_benchmark="yes"], [enable_benchmark="no"])
EINA_BENCH_MODULE([glib], [${enable_benchmark}], [glib-2.0], [enable_benchmark_glib="yes"], [enable_benchmark_glib="no"])

AC_SUBST(requirement_eina)

### Create the .pc.in file according to the major version
#cat > ${srcdir}/eina-${VMAJ}.pc.in << EOF
#prefix=@prefix@
#exec_prefix=@exec_prefix@
#libdir=@libdir@
#includedir=@includedir@
#
#Name: Eina
#Description: A Library that implements fast data types and miscellaneous tools
#Requires:
#Version: @VERSION@
#Libs: -L${libdir} -leina
#Libs.private: -ldl
#Cflags: -I${includedir}/eina-@VMAJ@ -I${includedir}/eina-@VMAJ@/eina
#EOF

AC_CONFIG_FILES([
Makefile
eina-0.pc
eina.spec
doc/Makefile
src/Makefile
src/include/Makefile
src/include/eina_config.h
src/lib/Makefile
src/modules/Makefile
src/modules/mp/Makefile
src/modules/mp/chained_pool/Makefile
src/modules/mp/ememoa_fixed/Makefile
src/modules/mp/ememoa_unknown/Makefile
src/modules/mp/pass_through/Makefile
src/modules/mp/fixed_bitmap/Makefile
src/modules/mp/buddy/Makefile
src/tests/Makefile
])

AC_OUTPUT

#####################################################################
## Info

echo
echo
echo
echo "------------------------------------------------------------------------"
echo "$PACKAGE $VERSION"
echo "------------------------------------------------------------------------"
echo
echo
echo "Configuration Options Summary:"
echo
echo "  Magic debug..........: ${have_magic_debug}"
echo "  Safety checks........: ${have_safety_checks}"
echo "  Maximum log level....: ${with_max_log_level}"
echo "  Report string usage..: ${have_stringshare_usage}"
echo "  Default mempool......: ${have_default_mempool}"
echo "  Thread Support.......: ${have_pthread} (spinlock: ${have_pthread_spinlock})"
echo "  Amalgamation.........: ${do_amalgamation}"
echo "  Iconv support........: ${have_iconv}"
echo
echo "  Documentation........: ${build_doc}"
echo "  Tests................: ${enable_tests}"
echo "  Coverage.............: ${enable_coverage}"
echo "  Benchmark............: ${enable_benchmark}"
if test "x${enable_benchmark}" = "xyes" ; then
echo "    Glib...............: ${enable_benchmark_glib}"
echo "    E17 real data......: ${enable_benchmark_e17}"
fi
echo
echo "  CPU Specific Extensions:"
echo "    MMX................: ${have_mmx}"
echo "    SSE................: ${have_sse}"
echo "    SSE2...............: ${have_sse2}"
echo "    ALTIVEC............: ${have_altivec}"
echo
echo "  Memory pools:"
echo "    Chained pool.......: ${enable_chained_pool}"
echo "    Ememoa fixed.......: ${enable_ememoa_fixed}"
echo "    Ememoa unknown.....: ${enable_ememoa_unknown}"
echo "    Fixed bitmap.......: ${enable_fixed_bitmap}"
echo "    Pass through.......: ${enable_pass_through}"
echo "    Buddy..............: ${enable_buddy}"
echo
echo "Compilation............: make (or gmake)"
echo "  CPPFLAGS.............: $CPPFLAGS"
echo "  CFLAGS...............: $CFLAGS"
echo "  LDFLAGS..............: $LDFLAGS"
echo
echo "Installation...........: make install (as root if needed, with 'su' or 'sudo')"
echo "  prefix...............: $prefix"
echo
