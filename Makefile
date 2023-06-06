


build: main.c
	gcc -o main.c -c libs/stb_image.h


clean:
	rm -f main

run:
	./main ben-pxl.jpg

all: clean build run