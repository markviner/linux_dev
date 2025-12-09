ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src po

EXTRA_DIST = Doxyfile.in

if HAVE_DOXYGEN
doxygen-doc: Doxyfile
	$(DOXYGEN) Doxyfile

clean-local:
	rm -rf doxygen-doc
else
doxygen-doc:
	@echo "Doxygen not found, cannot generate documentation"
endif

if HAVE_HELP2MAN
dist_man_MANS = guessnum.1

guessnum.1: src/guessnum$(EXEEXT)
	$(HELP2MAN) --output=$@ --no-info --name="number guessing game" ./src/guessnum$(EXEEXT)
endif
