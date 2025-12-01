CC = gcc
CFLAGS = -g -O2 -Wall -I/usr/include/check
LIBNAME = libgrowablebuf.a
TEST_NAME = test
CHECK_LIB = -lcheck

$(LIBNAME): growable_buf.o
	ar rcs $@ $^

growable_buf.o: growable_buf.c growable_buf.h
	$(CC) $(CFLAGS) -c growable_buf.c

$(TEST_NAME): tests.o $(LIBNAME)
	$(CC) $(CFLAGS) -o $@ $^ $(CHECK_LIB)

check: $(TEST_NAME)
	./$(TEST_NAME)

tests.o: tests.c growable_buf.h
	$(CC) $(CFLAGS) -c tests.c

clean:
	rm -f *.o $(LIBNAME) $(TEST_NAME)

coverage: check
	gcov growable_buf.c
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage
