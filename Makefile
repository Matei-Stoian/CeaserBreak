CC = gcc
CFLAGS = -Wall -std=c99 
LDLIBS = -lm

TARGET = caesar_cipher
SRC = main.c caser.c

all: $(TARGET)

$(TARGET): $(SRC) caeser.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)


