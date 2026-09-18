CC      = gcc
CFLAGS  = -Wall -Werror -g

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGET  = $(BIN_DIR)/todo
SRCS    = $(wildcard $(SRC_DIR)/*.c)
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

debug:
	gdb ./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

re: clean all

run: all
	./$(TARGET)

.PHONY: all clean re run
