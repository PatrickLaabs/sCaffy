# Makefile

CC = gcc
CFLAGS = -Wall -Iinclude
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/sCaffy

all: $(TARGET)

$(TARGET):
	mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/scaffy.c -o $(TARGET)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $%.o

clean:
	rm -f $(TARGET)
	rm -r $(BUILD_DIR)

.PHONY: all clean
