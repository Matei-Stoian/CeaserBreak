CC = gcc
CFLAGS = -Wall -std=c99 
LDLIBS = -lm

TARGET = caesar_cipher
ANALYSIS = cipher_analysis
SRC = main.c caser.c
ANALYSIS_SRC = cipher_analysis.c caser.c

all: $(TARGET) $(ANALYSIS)

$(TARGET): $(SRC) caeser.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDLIBS)

$(ANALYSIS): $(ANALYSIS_SRC) caeser.h
	$(CC) $(CFLAGS) -o $(ANALYSIS) $(ANALYSIS_SRC) $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

analyze: $(ANALYSIS)
	./$(ANALYSIS)

clean:
	rm -f $(TARGET) $(ANALYSIS)

.PHONY: all run analyze clean


