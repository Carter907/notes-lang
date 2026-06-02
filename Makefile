SHELL=/usr/bin/bash

CC = gcc
CD = gdb

PROG_NAME = app

# dirs
LIB_DIR = ./lib
SRC_DIR = ./src
BUILD_DIR = ./target
TEST_DIR = ./tests

# sources
CLIENT_SRC = main.c
SOURCES = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/**/*.c)
TEST_SOURCES = test.c

VER = c23

# flags
BASE_CFLAGS = -std=$(VER) -g -Wall -Werror
CLIENT_CFLAGS= $(BASE_CFLAGS) -fsanitize=address,undefined,leak -fsanitize-trap=undefined
CFLAGS = $(BASE_CFLAGS)

# other libs used by client

LIBS = -lm -ledit

# libs used by testing framework

TEST_LIBS = -lcunit


run: $(BUILD_DIR)/$(PROG_NAME)
	$(BUILD_DIR)/$(PROG_NAME)

# build client app
build: $(SOURCES)
	@echo building $(SOURCES) ...
	mkdir -p $(BUILD_DIR)
	$(CC) -o $(PROG_NAME) $(CLIENT_CFLAGS) $(SOURCES) $(LIBS)
	mv $(PROG_NAME) $(BUILD_DIR)

# run tests
test: $(TEST_DIR)/$(TEST_SOURCES)
	mkdir -p $(BUILD_DIR)/tests
	$(CC) -I$(SRC_DIR) -o $(PROG_NAME)_test $(CFLAGS) $(SRC_DIR)/$(SOURCES) $(TEST_DIR)/$(TEST_SOURCES) $(TEST_LIBS)
	mv $(PROG_NAME)_test $(BUILD_DIR)/tests
	$(BUILD_DIR)/tests/$(PROG_NAME)_test

format: $(SOURCES)
	@echo formatting $^ ...
	clang-format -i $^

install: $(BUILD_DIR)/$(PROG_NAME)
	cp $^ /usr/local/bin/$(PROG_NAME)

uninstall:
	rm /usr/local/bin/$(PROG_NAME)

# remove lib and build dirs
clean: $(BUILD_DIR)
	rm -rf $^

# run debugger
debug: build
	$(CD) $(BUILD_DIR)/$(PROG_NAME)
