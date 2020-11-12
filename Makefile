all: xbrzscale

xbrz/xbrz.o: xbrz/xbrz.cpp xbrz/xbrz.h
	g++ -std=c++17 -c -o xbrz/xbrz.o xbrz/xbrz.cpp -DNDEBUG

libxbrzscale.o: libxbrzscale.cpp xbrz/xbrz.h
	g++ -std=c++17 -c -o libxbrzscale.o libxbrzscale.cpp `sdl2-config --cflags`

xbrzscale.o: xbrzscale.cpp libxbrzscale.h xbrz/xbrz.h
	g++ -std=c++17 -c -o xbrzscale.o xbrzscale.cpp `sdl2-config --cflags`

libxbrzscale.a: libxbrzscale.o xbrz/xbrz.o
	ar qc libxbrzscale.a libxbrzscale.o xbrz/xbrz.o

xbrzscale: xbrzscale.o libxbrzscale.a
	g++ -o xbrzscale xbrzscale.o libxbrzscale.a -lSDL2_image `sdl2-config --libs`

clean:
	rm -vf xbrzscale.o xbrz/xbrz.o libxbrzscale.o libxbrzscale.a xbrzscale
