AC_INIT([rhasher], [0.1], [student@example.com])
AM_INIT_AUTOMAKE([foreign -Wall])
AC_PROG_CC

# check rhash installation
AC_CHECK_HEADER([rhash.h], [], [AC_MSG_ERROR([unable to find rhash.h])])
AC_CHECK_LIB([rhash], [rhash_library_init],
    [RHASH_LIBS="-lrhash"],
    [AC_MSG_ERROR([unable to find librhash])])
AC_SUBST(RHASH_LIBS)

# check readline installation
AC_ARG_ENABLE([readline],
    [AS_HELP_STRING([--enable-readline], [Use libreadline for input (optional)])],
    [use_readline=$enableval], [use_readline=no])

if test "x$use_readline" = "xyes"; then
    AC_CHECK_LIB([readline], [readline], [READLINE_LIBS="-lreadline"],
        [AC_MSG_WARN([libreadline not found, so building without it])])
    AC_DEFINE([USE_READLINE], [1], [Use readline()])
fi
AC_SUBST(READLINE_LIBS)

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
