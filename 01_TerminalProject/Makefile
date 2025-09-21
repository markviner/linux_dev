CC=cc
CFLAGS=-Wall -Wextra -std=c11
LDLIBS=-lncurses
TARGET=Show
SRC=Show.c

# convert all .c files to .o filenames
OBJ=$(SRC:.c=.o)

DBG_TARGET=$(TARGET)_debug

.PHONY: all debug clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDLIBS)

debug: CFLAGS+=-g
debug: $(DBG_TARGET)

$(DBG_TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDLIBS)

# build any .o file from any .c file
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) -v $(OBJ) $(TARGET) $(DBG_TARGET)
