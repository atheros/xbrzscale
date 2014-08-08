all: xbrzscale

xbrz/xbrz.o: xbrz/xbrz.cpp xbrz/xbrz.h
	g++ -std=c++0x -c -o xbrz/xbrz.o xbrz/xbrz.cpp -DNDEBUG

#savepng.o: savepng.c
#	g++ -c -o savepng.o savepng.c `sdl-config --cflags`

SDL_imagesave/IMG_savepng.o: SDL_imagesave/IMG_savepng.c SDL_imagesave/IMG_savepng.h SDL_imagesave/IMG_save.h
	g++ -c -o SDL_imagesave/IMG_savepng.o SDL_imagesave/IMG_savepng.c `sdl-config --cflags` -ISDL_imagesave

xbrzscale.o: xbrzscale.cpp SDL_imagesave/IMG_savepng.h xbrz/xbrz.h
	g++ -std=c++0x -c -o xbrzscale.o xbrzscale.cpp `sdl-config --cflags`

SDL_imagesave/IMG_savepng.o:
xbrzscale: xbrzscale.o SDL_imagesave/IMG_savepng.o xbrz/xbrz.o
	g++ -o xbrzscale xbrzscale.o SDL_imagesave/IMG_savepng.o xbrz/xbrz.o -lSDL_image `sdl-config --libs`

clean:
	rm -f xbrzscale.o xbrz/xbrz.o SDL_imagesave/IMG_savepng.o xbrzscale

