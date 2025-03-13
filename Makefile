CC = gcc
CFLAGS = -Wall -Wextra -g
SRC_DIR = src
OBJ_DIR = build
BIN = image_processor

# Source files
SOURCES = main.c $(wildcard $(SRC_DIR)/*.c)
# Object files (keeping main.o in the root of OBJ_DIR)
MAIN_OBJ = $(OBJ_DIR)/main.o
LIB_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))
OBJECTS = $(MAIN_OBJ) $(LIB_OBJS)

all: directories $(BIN)

directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p output

$(BIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for main.c in the root directory
$(OBJ_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

# Rule for source files in src directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean directories
