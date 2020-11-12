all: xbrzscale

xbrz/xbrz.o: xbrz/xbrz.cpp xbrz/xbrz.h
	g++ -std=c++17 -c -o xbrz/xbrz.o xbrz/xbrz.cpp -DNDEBUG -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

libxbrzscale.o: libxbrzscale.cpp xbrz/xbrz.h
	g++ -std=c++17 -c -o libxbrzscale.o libxbrzscale.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

xbrzscale.o: xbrzscale.cpp libxbrzscale.h xbrz/xbrz.h
	g++ -std=c++17 -c -o xbrzscale.o xbrzscale.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

libxbrzscale.a: libxbrzscale.o xbrz/xbrz.o
	ar qc libxbrzscale.a libxbrzscale.o xbrz/xbrz.o

xbrzscale: xbrzscale.o libxbrzscale.a
	g++ -o xbrzscale xbrzscale.o libxbrzscale.a -lSDL2_image -lSDL2main -lSDL2 -lSDL2_image -lmingw32

clean:
	rm -vf xbrzscale.o xbrz/xbrz.o libxbrzscale.o libxbrzscale.a xbrzscale
