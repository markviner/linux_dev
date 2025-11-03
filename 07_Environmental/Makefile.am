bin_PROGRAMS = rhasher
rhasher_SOURCES = rhasher.c
rhasher_LDADD = $(RHASH_LIBS) $(READLINE_LIBS)

TESTS = test.sh
EXTRA_DIST = test.sh

check_SCRIPTS = test.sh

maintainer-clean-local:
	rm -rf Makefile.in aclocal.m4 autom4te.cache/ compile configure depcomp install-sh missing test-driver .deps/
