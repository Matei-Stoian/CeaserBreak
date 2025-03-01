CC = gcc

CFLAGS = -Wall -Wextra -std=c99

TARGET = cesar_cipher

SRC = cracker.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
