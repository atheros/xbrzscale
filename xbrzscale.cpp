/*
 * Copyright (c) 2014 Przemysław Grzywacz <nexather@gmail.com>
 * This file is part of xbrzscale.
 *
 * xbrzscale is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <cstdint>

#include "SDL.h"
#include "SDL_image.h"


#include "xbrz/xbrz.h"
//#include "savepng.h"
#include "SDL_imagesave/IMG_savepng.h"


inline Uint32 SDL_GetPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

inline void SDL_PutPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}


SDL_Surface* createARGBSurface(int w, int h) {
	return SDL_CreateRGBSurface(0, w, h, 32, 0xff0000U, 0xff00U, 0xffU, 0xff000000U);
}

/*
void displayImage(SDL_Surface* surface, const char* message) {
	fprintf(stdout, "Display: %s\n", message);
	SDL_Surface* video = SDL_SetVideoMode(640, 480, 0, 0);
	if (!video) {
		fprintf(stderr, "Failed to open display: %s\n", SDL_GetError());
		return;
	}

	SDL_Event e;
	bool done = false;
	bool expose = true;
	while(!done) {
		while(SDL_PollEvent(&e)) {
			if (e.type == SDL_KEYUP) {
				done = true;
			} else if (e.type == SDL_VIDEOEXPOSE) {
				expose = true;
			}
		}

		if (expose) {
			printf("expose\n");
			expose = false;
			SDL_Rect dest;

			dest.x = 640 / 2 - surface->w / 2;
			dest.y = 480 / 2 - surface->h / 2;
			SDL_BlitSurface(surface, NULL, video, &dest);
			SDL_Flip(video);
		}
	}
}
*/

int main(int argc, char* argv[]) {
	if (argc != 4) {
		fprintf(stderr, "usage: xbrzscale scale_factor input_image output_image\n");
		fprintf(stderr, "scale_factor can be between 2 and 5\n");
		return 1;
	}
	
	int scale = atoi(argv[1]);
	char* in_file = argv[2];
	char* out_file = argv[3];
	
	if (scale < 2 || scale > 5) {
		fprintf(stderr, "scale_factor must be between 2 and 5 (inclusive), got %i\n", scale);
		return 1;
	}
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	
	SDL_Surface* src_img = IMG_Load(in_file);
	if (!src_img) {
		fprintf(stderr, "Failed to load source image '%s': %s\n", in_file, IMG_GetError());
		return 1;
	}
	
//	displayImage(src_img, "Source image");

	int src_width = src_img->w;
	int src_height = src_img->h;
	int dst_width = src_width * scale;
	int dst_height = src_height * scale;


	int x, y, offset;
	Uint8 r, g, b, a;

	uint32_t *in_data = new uint32_t[src_img->w * src_img->h];
	offset = 0;
	for(y = 0; y < src_img->h; y++) {
		for(x = 0; x < src_img->w; x++) {
			uint32_t c = SDL_GetPixel(src_img, x, y);
			SDL_GetRGBA(c, src_img->format, &r, &g, &b, &a);
			//fprintf(stdout, "%02x%02x%02x%02x ", a, r, g, b);
			in_data[offset] = (
						(uint32_t(a) << 24)
						| (uint32_t(r) << 16)
						| (uint32_t(g) << 8)
						| (uint32_t(b))
					);
//			fprintf(stdout, "%08x ", in_data[offset]);
			offset++;
		}
//		fprintf(stdout, "\n");
	}
	SDL_FreeSurface(src_img);

	
	printf("Scaling image...\n");
	uint32_t* dest = new uint32_t[dst_width * dst_height];
	
	xbrz::scale(scale, in_data, dest, src_width, src_height);
	delete [] in_data;
	
	printf("Saving image...\n");
	SDL_Surface* dst_img = createARGBSurface(dst_width, dst_height);
	if (!dst_img) {
		delete [] dest;
		fprintf(stderr, "Failed to create SDL surface: %s\n", SDL_GetError());
		return 1;
	}

	offset = 0;
	for(y = 0; y < dst_height; y++) {
		for(x = 0; x < dst_width; x++) {
			a = ((dest[offset] >> 24) & 0xff);
			r = (dest[offset] >> 16) & 0xff;
			g = (dest[offset] >> 8) & 0xff;
			b = (dest[offset]) & 0xff;
			uint32_t c = SDL_MapRGBA(dst_img->format, r, g, b, a);
//			fprintf(stdout, "%02x%02x%02x%02x ", a, r, g, b);
//			fprintf(stdout, "%08x ", c);
//			fprintf(stdout, "%08x ", dest[offset]);
			SDL_PutPixel(dst_img, x, y, c);
//			SDL_PutPixel(dst_img, x, y, (a || r || g || b) ? 0xffffffffU : 0);
			offset++;
		}
//		fprintf(stdout, "\n");
	}

//	displayImage(dst_img, "Image after color conversion");

	/*
	if (SDL_SavePNG(dst_img, out_file) != 0) {
		fprintf(stderr, "Failed to save output image: %s\n", SDL_GetError());
		return 1;
	}*/
	IMG_SavePNG(out_file, dst_img, -1);
	
	SDL_FreeSurface(dst_img);
	
	SDL_Quit();
	return 0;
}
