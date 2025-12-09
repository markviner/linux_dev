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
AC_DEFINE_UNQUOTED([LOCALEDIR], ["${prefix}/share/locale"], [Locale directory])

AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN"; then
   AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi
AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])

AC_CHECK_PROGS([HELP2MAN], [help2man])
AM_CONDITIONAL([HAVE_HELP2MAN], [test -n "$HELP2MAN"])

AC_CONFIG_FILES([
 Makefile
 src/Makefile
 po/Makefile.in
 Doxyfile
])

AC_OUTPUT
