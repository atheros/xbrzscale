all: xbrzscale

xbrz/xbrz.o: xbrz/xbrz.cpp xbrz/xbrz.h
	g++ -std=c++11 -c -o xbrz/xbrz.o xbrz/xbrz.cpp -DNDEBUG

xbrzscale.o: xbrzscale.cpp xbrz/xbrz.h
	g++ -std=c++11 -c -o xbrzscale.o xbrzscale.cpp `sdl2-config --cflags`

xbrzscale: xbrzscale.o xbrz/xbrz.o
	g++ -o xbrzscale xbrzscale.o xbrz/xbrz.o -lSDL2_image `sdl2-config --libs`

clean:
	rm -f xbrzscale.o xbrz/xbrz.o xbrzscale