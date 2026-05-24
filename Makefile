CC	= g++
LANG	= .cpp
all:
	${CC} -O3 src/main${LANG} -o ppm -lm

clean:
	cd outputs && rm output-*.ppm
