xBRZ upscaling commandline tool
===============================

Copyright (c) 2020 Przemysław Grzywacz <nexather@gmail.com>

This file is part of xbrzscale.

xbrzscale is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.



Overview
--------

This tool allows you to scale your graphics with xBRZ algorithm, see https://en.wikipedia.org/wiki/Pixel-art_scaling_algorithms#xBR_family


External code
-------------

The following external code is included in this repository:

* https://sourceforge.net/projects/xbrz/files/xBRZ/ - xBRZ implementation

Dependencies
------------

The following dependencies are needed to compile xbrzscale:

* libsdl2-dev
* libsdl2-image-dev

On Windows said dependencies can be installed by doing the following:

* [libsd12](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php)
* libsd12-image is done following the same process [with this download instead](https://www.libsdl.org/projects/SDL_image/)

Under OSX they can be installed using macports

* port install libsdl2_image
* port install libsdl2

Some additional libraries are needed. I'm sure you'll figure it out.

If you need SDL1.2 support, check sdl1.2 git branch.


Compiling
---------

For Mac and Linux:

run `make` and you should end up with a binary called `xbrzscale`.

For Windows:

run `mingw32-make -f Makefile-win` and you should end up with a binary called `xbrzscale.exe`

Usage
-----

	`xbrztool scale_factor input_image output_image`

* `scale_factor` - Controls how much your image should be scaled. It should be an integer between 2 and 5 (inclusive).
* `input_image` - Input image is the filename of the image you want to scale. Image format can be anything that SDL_image supports.
* `output_image` - Filename where the scaled image should be saved. The only supported format is PNG!

Please note I only tested the scaling on 32bit RGBA PNGs, I have no idea if this will work with 8bit indexed images.




