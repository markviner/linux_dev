CC = cc
CFLAGS = -Wall -std=c99

all: maze maze1 maze2 maze3

maze: maze.c
	$(CC) $(CFLAGS) maze.c -o maze

maze1.c: maze.c patch1.patch
	cp maze.c maze1.c
	patch maze1.c < patch1.patch

maze1: maze1.c
	$(CC) $(CFLAGS) maze1.c -o maze1

maze2.c: maze1.c patch2.patch
	cp maze1.c maze2.c
	patch maze2.c < patch2.patch

maze2: maze2.c
	$(CC) $(CFLAGS) maze2.c -o maze2

maze3.c: maze2.c patch3.patch
	cp maze2.c maze3.c
	patch maze3.c < patch3.patch

maze3: maze3.c
	$(CC) $(CFLAGS) maze3.c -o maze3

CYAN = \033[0;36m
YELLOW = \033[0;33m
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

run: all
	@printf "${YELLOW}%10s6x6${RESET}\n"
	./maze
	@echo ""
	@printf "${YELLOW}%10s4x4${RESET}\n"
	./maze1 4
	@echo ""
	@printf "${YELLOW}%10s5x5, aisle ':', wall '@'${RESET}\n"
	./maze2 ":@" 5
	@echo ""
	@printf "${YELLOW}%10s6x6, seed=42, aisle '.', wall '#'${RESET}\n"
	./maze3 42 ".#" 6

clean:
	rm -f maze maze1 maze2 maze3 maze1.c maze2.c maze3.c

.PHONY: all run clean
