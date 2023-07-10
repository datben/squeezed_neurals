LIBS = libs/** -lm
CFLAGS = -Wall -O1
CC = gcc

EXE = target/main

INPUT_FILE = pokeball.png
OUTPUT_FILE = target/pokeball-2.png

# INPUT_FILE = ben-pxl.jpg
# OUTPUT_FILE = target/ben-pxl-2.png

SRC_FILES = main.c \
	pixel.c \
	neuron.c \
	math_utils.c \
	layer.c \
	neural_network.c

COMPILED_FILES = $(foreach item,$(SRC_FILES:.c=.o) ,target/build/src/$(item))

target/build/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

build: $(COMPILED_FILES)
	gcc $^ -o $(EXE) $(LIBS)

clean:
	rm -r target

run: build
	./$(EXE) $(INPUT_FILE) $(OUTPUT_FILE)

all: clean build run