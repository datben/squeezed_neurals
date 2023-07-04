LIBS = libs/** -lm

INPUT_FILE = ben-pxl.jpg
OUTPUT_FILE = target/ben-pxl-2.png

build: src/main.c
	mkdir -p target && gcc -o target/main src/main.c $(LIBS)

clean:
	rm -r target

run:
	./target/main $(INPUT_FILE) $(OUTPUT_FILE)

all: clean build run