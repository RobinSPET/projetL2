# Directories
INCLUDE_DIR = include
OBJ_DIR = obj
SRC_DIR = src
JAVA_DIR = java
SCRIPT_DIR = script
BUILD_DIR = build

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -fPIC -I$(INCLUDE_DIR) -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lm

# Program names
PROG = intersections
TEST = runtest
LIB = $(JAVA_DIR)/libintersections.so
EXPE = $(SCRIPT_DIR)/expe
SDL_EXEC = $(BUILD_DIR)/projetL2

# Java includes
JAVA_HOME = /usr/lib/jvm/java-11-openjdk-amd64
JAVA_INCLUDES = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux

# Dependencies
_DEPS = util.h rational.h list.h tree.h geometry.h algo.h
DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

_OBJ = util.o rational.o list.o tree.o geometry.o algo.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

# Source files for SDL
SDL_SRC = $(SRC_DIR)/main.c
SDL_OBJ = $(SDL_SRC:.c=.o)

.PHONY: all run test jni expe clean cleanall memorycheck testmemorycheck

# Target for both projects
all: $(PROG) $(TEST) $(LIB) $(EXPE) $(SDL_EXEC)

# Rules for SDL project
$(SDL_EXEC): $(SDL_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

run: $(PROG)
	./$(PROG) $(in) $(out) $(algo)

test: $(TEST)
	./$(TEST)

jni: $(LIB)

expe: $(EXPE)

clean:
	rm -f $(OBJ_DIR)/*.o $(SDL_OBJ)
	rm -f $(SDL_EXEC)

delete:
	rm -f $(PROG)

deletetest:
	rm -f $(TEST)

deletelib:
	rm -f $(LIB)

deleteexpe:
	rm -f $(EXPE)

cleanall: clean delete deletetest deletelib deleteexpe

memorycheck: $(PROG)
	valgrind ./$(PROG) $(in) $(out) $(algo)

testmemorycheck: $(TEST)
	valgrind ./$(TEST)

$(PROG): $(OBJ) $(OBJ_DIR)/main.o
	$(CC) -o $@ $^ -lm

$(TEST): $(OBJ) $(OBJ_DIR)/test.o
	$(CC) -o $@ $^ -lm

$(EXPE): $(OBJ) $(OBJ_DIR)/expe.o
	$(CC) -o $@ $^ -lm

$(LIB): $(OBJ) $(OBJ_DIR)/application_Intersections.o
	$(CC) -shared -o $@ $^ -lm

# Rule to compile SDL object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
