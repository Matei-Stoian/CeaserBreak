CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -lm
LDLIBS = -lm

TARGET = caesar_cipher
SRC = main.c caser.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c caeser.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all run clean
