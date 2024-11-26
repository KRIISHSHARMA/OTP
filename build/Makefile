CC = gcc
CFLAGS = -Wall -g
SRC_DIR = ..
BIN_DIR = ../bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
TARGETS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%)

all: $(TARGETS)

$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean