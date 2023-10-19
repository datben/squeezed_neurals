LIBS = libs/** -lm
CFLAGS = -Wall -O1
CC = g++

EXE = target/main

INPUT_FILE = pokeball.png

SRC_FILES = main.cpp \
	pixel.cpp \
	neuron.cpp \
	layer.cpp \

COMPILED_FILES = $(foreach item,$(SRC_FILES:.cpp=.o) ,target/build/src/$(item))

target/build/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

build: $(COMPILED_FILES)
	$(CC) $^ -o $(EXE) $(LIBS)

clean:
	rm -r target

run: build
	./$(EXE) $(INPUT_FILE)

all: clean build run