CC=clang

all: filter images

images: dir grayscale reflect blur edges sepia

filter:
	$(CC) -fsanitize=signed-integer-overflow -fsanitize=undefined -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -o filter filter.c helpers.c

dir:
	mkdir -p output

grayscale:
	./filter -g images/yard.bmp output/grayscale.bmp

reflect:
	./filter -r images/yard.bmp output/reflect.bmp

blur:
	./filter -b images/yard.bmp output/blur.bmp

edges:
	./filter -e images/yard.bmp output/edges.bmp

sepia:
	./filter -s images/yard.bmp output/sepia.bmp

