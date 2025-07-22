MAKEFLAGS+=--no-print-directory

SRC_DIR:=src/
INCLUDE_DIR:=include/
SRC_FILES:=$(wildcard $(SRC_DIR)*.c)

CC:=gcc
C_FLAGS:=-W -Wextra -Wall -pedantic-errors -I$(INCLUDE_DIR)

test: $(SRC_FILES)
	@make clean
	$(CC) $(C_FLAGS) $(SRC_FILES) -o test

debug: $(SRC_FILES)
	@make clean
	$(CC) -g $(C_FLAGS) $(SRC_FILES) -o test-debug

clean:
	@rm -f test test-debug
	@echo Files cleaned up
