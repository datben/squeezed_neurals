LIBS = libs/** -lm
CFLAGS = -Wall
CC = gcc

INPUT_FILE = ben-pxl.jpg
OUTPUT_FILE = target/ben-pxl-2.png

target/build/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

create_dir:
	mkdir -p target && mkdir -p target/build && mkdir -p target/build/src 

build: target/build/src/main.o target/build/src/pixel.o
	gcc target/build/src/pixel.o target/build/src/main.o -o target/main $(LIBS)

clean:
	rm -r target

run: build
	./target/main $(INPUT_FILE) $(OUTPUT_FILE)

all: clean build run