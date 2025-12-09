#!/bin/sh
set -xe

echo "Running autopoint..."
autopoint --force

echo "Running aclocal..."
aclocal -I m4

echo "Running autoconf..."
autoconf

echo "Running autoheader..."
autoheader

echo "Running automake..."
automake --add-missing --copy --foreign

echo ""
echo "Now you can run:"
echo "  ./configure --prefix=/usr/local"
echo "  make"
echo "  make doxygen-doc  # to generate documentation"
echo "  make install"
