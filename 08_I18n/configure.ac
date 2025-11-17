AC_INIT([guessnum], [1.0], [example@example.com])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign])

AC_PROG_CC

AC_CHECK_HEADERS([libgen.h unistd.h])
AC_CHECK_FUNCS([readlink dirname])

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.21])

AC_SUBST([localedir], ['${datadir}/locale'])

AC_CONFIG_FILES([
 Makefile
 src/Makefile
 po/Makefile.in
])

AC_OUTPUT
