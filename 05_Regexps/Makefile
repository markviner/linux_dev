CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = esubc

all: $(TARGET)

$(TARGET): esub.c
	$(CC) $(CFLAGS) -o $(TARGET) esub.c

CYAN = \033[0;36m
YELLOW = \033[0;33m
GREEN = \033[0;32m
RESET = \033[0m

test: $(TARGET)
	@printf "${YELLOW}%10sTest 1${RESET}\n"
	@printf "${CYAN}./$(TARGET) '(regular) (express)ion(s?)' 'to \\2 emotion\\3 \\1ly' 'Learn regular expressions!'${RESET}\n"
	@./$(TARGET) '(regular) (express)ion(s?)' 'to \2 emotion\3 \1ly' 'Learn regular expressions!' > test_out.txt
	@echo 'Learn regular expressions!' | sed -E 's/(regular) (express)ion(s?)/to \2 emotion\3 \1ly/' > sed_out.txt
	@diff test_out.txt sed_out.txt && printf "${GREEN}PASS${RESET}\n" || echo "FAIL"
	
	@printf "\n${YELLOW}%10sTest 2${RESET}\n"
	@printf "${CYAN}./$(TARGET) 'world' 'universe' 'hello world'${RESET}\n"
	@./$(TARGET) 'world' 'universe' 'hello world' > test_out.txt
	@echo 'hello world' | sed -E 's/world/universe/' > sed_out.txt
	@diff test_out.txt sed_out.txt && printf "${GREEN}PASS${RESET}\n" || echo "FAIL"
	
	@printf "\n${YELLOW}%10sTest 3${RESET}\n"
	@printf "${CYAN}./$(TARGET) '([0-9]+)' 'number:\\1' 'test 123 end'${RESET}\n"
	@./$(TARGET) '([0-9]+)' 'number:\1' 'test 123 end' > test_out.txt
	@echo 'test 123 end' | sed -E 's/([0-9]+)/number:\1/' > sed_out.txt
	@diff test_out.txt sed_out.txt && printf "${GREEN}PASS${RESET}\n" || echo "FAIL"
	
	@printf "\n${YELLOW}%10sTest 4 (multiple groups)${RESET}\n"
	@printf "${CYAN}./$(TARGET) '([a-z]+) ([0-9]+)' '\\2-\\1' 'word 456 text'${RESET}\n"
	@./$(TARGET) '([a-z]+) ([0-9]+)' '\2-\1' 'word 456 text' > test_out.txt
	@echo 'word 456 text' | sed -E 's/([a-z]+) ([0-9]+)/\2-\1/' > sed_out.txt
	@diff test_out.txt sed_out.txt && printf "${GREEN}PASS${RESET}\n" || echo "FAIL"
	
	@printf "\n${YELLOW}%10sTest 5 (no match)${RESET}\n"
	@printf "${CYAN}./$(TARGET) '[0-9]+' 'NUMBER' 'no numbers here'${RESET}\n"
	@./$(TARGET) '[0-9]+' 'NUMBER' 'no numbers here' > test_out.txt
	@echo 'no numbers here' | sed -E 's/[0-9]+/NUMBER/' > sed_out.txt
	@diff test_out.txt sed_out.txt && printf "${GREEN}PASS${RESET}\n" || echo "FAIL"
	
	@printf "\n${YELLOW}%10sError Test 1 (invalid regex)${RESET}\n"
	@printf "${CYAN}./$(TARGET) '[' 'x' 'test'${RESET}\n"
	@./$(TARGET) '[' 'x' 'test' 2>&1 | grep -iq "error" && printf "${GREEN}PASS (error detected)${RESET}\n" || echo "FAIL"
	
	@printf "\n${YELLOW}%10sError Test 2 (unclosed parenthesis)${RESET}\n"
	@printf "${CYAN}./$(TARGET) '(abc' 'x' 'test'${RESET}\n"
	@./$(TARGET) '(abc' 'x' 'test' 2>&1 | grep -iq "error" && printf "${GREEN}PASS (error detected)${RESET}\n" || echo "FAIL"
	
	@printf "\n${YELLOW}%10sError Test 3 (wrong number of arguments)${RESET}\n"
	@printf "${CYAN}./$(TARGET) 'pattern' 'subst'${RESET}\n"
	@./$(TARGET) 'pattern' 'subst' 2>&1 | grep -iq "usage" && printf "${GREEN}PASS (usage message)${RESET}\n" || echo "FAIL"

clean:
	rm -f $(TARGET) test_out.txt sed_out.txt *.o

.PHONY: all test clean
