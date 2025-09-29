CC = cc
CFLAGS = -Wall
AR = ar
ARFLAGS = rcs

SRC = prog.c fun.c const.c
OBJ = $(SRC:.c=.o)
PIC_OBJ = fun_pic.o const_pic.o

GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so \
            out_0_prog out_0_proga out_0_progso \
            out_1_prog out_1_proga out_1_progso \
            out_3_prog out_3_proga out_3_progso
TRASH = *.o *~ o.* $(OBJ:.o=.d) $(PIC_OBJ:.o=.d)

.PHONY: all clean distclean test help

all: prog prog-a prog-so

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

prog: $(OBJ)
	$(CC) $^ -o $@

prog-a: prog.o liboutput_static.a
	$(CC) prog.o liboutput_static.a -o $@

prog-so: prog.o liboutput.so
	$(CC) prog.o -L. -loutput -o $@

fun_pic.o: fun.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

const_pic.o: const.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

# libs
liboutput_static.a: fun.o const.o
	$(AR) $(ARFLAGS) $@ $^

liboutput.so: $(PIC_OBJ)
	$(CC) -shared -o $@ $^


CYAN = \033[0;36m
YELLOW = \033[0;33m
RESET = \033[0m
test: all
	@printf "${YELLOW}%10sRunning tests!${RESET}\n"
	./prog      > out_0_prog   2>&1
	./prog-a    > out_0_proga  2>&1
	LD_LIBRARY_PATH=. ./prog-so > out_0_progso 2>&1
	cmp out_0_prog out_0_proga
	cmp out_0_prog out_0_progso
	./prog x    > out_1_prog   2>&1
	./prog-a x  > out_1_proga  2>&1
	LD_LIBRARY_PATH=. ./prog-so x > out_1_progso 2>&1
	cmp out_1_prog out_1_proga
	cmp out_1_prog out_1_progso
	./prog a b c    > out_3_prog   2>&1
	./prog-a a b c  > out_3_proga  2>&1
	LD_LIBRARY_PATH=. ./prog-so a b c > out_3_progso 2>&1
	cmp out_3_prog out_3_proga
	cmp out_3_prog out_3_progso

clean:
	$(RM) -v $(TRASH) $(GENERATES) $(PIC_OBJ)

help:
	@echo -e "$(CYAN)Targets:$(RESET)"
	@echo -e "$(CYAN)  make [all]     - build binaries and libraries$(RESET)"
	@echo -e "$(CYAN)  make test      - run tests$(RESET)"
	@echo -e "$(CYAN)  make clean     - remove objects and outputs$(RESET)"
	@echo -e "$(CYAN)  make distclean - remove all generated files$(RESET)"
