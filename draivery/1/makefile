CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -O2
TARGET=devzero_reader

all: $(TARGET)

$(TARGET): devzero_reader.c
	$(CC) $(CFLAGS) -o $(TARGET) devzero_reader.c

clean:
	rm -f $(TARGET)

.PHONY: all clean