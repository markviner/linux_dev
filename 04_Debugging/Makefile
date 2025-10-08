CC = cc
CFLAGS = -O0 -g
TARGET = range

all: $(TARGET)

$(TARGET): range.c
	$(CC) $(CFLAGS) $< -o $@

test: $(TARGET)
	gdb --batch --quiet -x test1.gdb 2>&1 | grep -E "^(@@@|start=)" > out1.txt
	gdb --batch --quiet -x test2.gdb 2>&1 | grep -E "^(@@@|iter=)" > out2.txt
	cmp out1.txt test1.txt
	cmp out2.txt test2.txt
	@echo "All tests passed!"

clean:
	rm -f $(TARGET) out*.txt

.PHONY: all test clean
