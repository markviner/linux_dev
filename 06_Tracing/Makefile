CC = cc
CFLAGS = -Wall -Wextra -O2

GENERATES = move libprotect.so
TRASH = *.o *~ .move* infile outfile PROTECT_file

.PHONY: all test clean

all: move libprotect.so

move: move.c
	$(CC) $(CFLAGS) -o $@ move.c

libprotect.so: protect.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ protect.c -ldl

CYAN = \033[0;36m
YELLOW = \033[0;33m
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
test: all
	@printf "${YELLOW}%10sSimple test${RESET}\n"

	@rm -f infile outfile PROTECT_file
	@printf "${CYAN}%0secho 'hello' > infile\n./move infile outfile || ('move failed'; exit 1)${RESET}\n"
	@echo "hello" > infile
	@./move infile outfile || (printf "${RED}%0smove failed${RESET}\n"; exit 1)
	@if [ -f outfile ] && [ ! -f infile ]; then \
		printf "${GREEN}%0sOK: moved\n"; \
	else \
		printf "${RED}%0sFAIL: move${RESET}\n"; exit 1; \
	fi
	@rm -f outfile

	@printf "${YELLOW}%10sLD_PRELOAD protect test${RESET}\n"

	@printf "${CYAN}%0secho "orig" > infile\necho "KEEPME" > PROTECT_file\nLD_PRELOAD=./libprotect.so ./move infile PROTECT_file || true${RESET}\n"
	@echo "orig" > infile
	@echo "KEEPME" > PROTECT_file
	@LD_PRELOAD=./libprotect.so ./move infile PROTECT_file || true
	@if [ -f PROTECT_file ]; then \
		printf "${GREEN}%0sOK: PROTECT file still exists${RESET}\n"; \
	else \
		printf "${RED}%0sFAIL: PROTECT removed${RESET}\n"; exit 1; \
	fi
	@rm -f PROTECT_file || true

	@printf "${YELLOW}%10sinject error on open (syscall 1)${RESET}\n"
	@rm -f infile outfile .move*
	@echo "test2" > infile
	@printf "${CYAN}%0sstrace -P infile -e fault=openat:error=EACCES:when=1 ./move infile outfile 2>/dev/null || true${RESET}\n"
	@strace -P infile -e fault=openat:error=EACCES:when=1 ./move infile outfile 2>/dev/null || true
	@if [ -f infile ]; then \
		printf "${GREEN}%0sOK: infile preserved after open failure${RESET}\n"; \
	else \
		printf "${RED}%0sFAIL: infile lost${RESET}\n"; exit 1; \
	fi
	@rm -f infile outfile .move*
	
	@printf "${YELLOW}%10sinject error on read${RESET}\n"
	@rm -f infile outfile .move*
	@echo "test3" > infile
	@printf "${CYAN}%0sstrace -P infile -e fault=read:error=EIO:when=1 ./move infile outfile 2>/dev/null || true${RESET}\n"
	@strace -P infile -e fault=read:error=EIO:when=1 ./move infile outfile 2>/dev/null || true
	@if [ -f infile ] && [ ! -f outfile ]; then \
		printf "${GREEN}%0sOK: infile preserved, outfile not created after read failure${RESET}\n"; \
	else \
		printf "${RED}%0sFAIL: wrong state after read failure${RESET}\n"; exit 1; \
	fi
	@rm -f infile outfile .move*
	
	@printf "${YELLOW}%10sinject error on write to temp${RESET}\n"
	@rm -f infile outfile .move*
	@echo "test4" > infile
	@printf "${CYAN}%0sstrace -e fault=write:error=ENOSPC:when=1 -e trace=write ./move infile outfile 2>/dev/null || true${RESET}\n"
	@strace -e fault=write:error=ENOSPC:when=1 -e trace=write ./move infile outfile 2>/dev/null || true
	@if [ -f infile ] && [ ! -f outfile ]; then \
		printf "${GREEN}%0sOK: infile preserved, outfile not created after write failure${RESET}\n"; \
	else \
		printf "${RED}%0sFAIL: wrong state after write failure${RESET}\n"; exit 1; \
	fi
	@rm -f infile outfile .move*
	
	@printf "${YELLOW}%10sinject error on final unlink (success expected)${RESET}\n"
	@rm -f infile outfile .move*
	@echo "test8" > infile
	@printf "${CYAN}%0sstrace -P infile -e fault=unlink:error=EACCES:when=1 ./move infile outfile 2>/dev/null || true${RESET}\n"
	@strace -P infile -e fault=unlink:error=EACCES:when=1 ./move infile outfile 2>/dev/null || true
	@if [ -f outfile ]; then \
		printf "${GREEN}%0sOK: outfile created even if final unlink failed${RESET}\n"; \
	else \
		printf "${RED}%0sFAIL: outfile not created${RESET}\n"; exit 1; \
	fi
	@rm -f infile outfile .move*
	
	@printf "\n${GREEN}%0sAll tests passed!${RESET}\n"
clean:
	$(RM) -v $(TRASH) $(GENERATES)
