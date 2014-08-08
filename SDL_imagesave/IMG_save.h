/** \file 
 *  This is a convenience header that allows both savejpg.h and savepng.h to be included
 *  in a single directive.
 *
 *  \author Chris &lt;chris@starforge.co.uk&gt;
 *  \version 0.1
 *  \date 6 Aug 2010 
 *  \todo Add support for additional image formats (TGA, PCX, and gif for example)
 *
 *  \mainpage SDL image writers
 *  \section overview Overview
 *  
 *  SDL_image is one of the most commonly used libraries for loading images into SDL applications:
 *  it provides loaders for the most commonly used graphics formats, a simple interface, and
 *  the ability to load from RWops in addition to files. Unfortunately, it completely lacks
 *  any ability to save surfaces as images in any format, and SDL itself only supports saving 
 *  as BMP. This is my attempt to partially address this issue: here you will find functions 
 *  that allow SDL Surfaces to be saved as JPEG and PNG data to either RWops or files.
 *   
 *  \section starting Getting started
 *
 *  In order to use the save functions, you will need to include IMG_savejpg.h if you want to
 *  write images as JPEG files, IMG_savepng.h if you want to write PNG files, or you can just
 *  include IMG_save.h if you want to save as both in different places in your code. Once you
 *  have done this, you will need to make sure that the .c files are being compiled and linked
 *  with your application. In theory you shouldn't need to explicitly link the jpeg and png 
 *  libraries if you are linking SDL_image already.
 *
 *  \section jpegsave Saving a SDL_Surface as JPEG
 *
 *  There are two options available when saving a surface as a jpeg: you may either use the
 *  IMG_SaveJPG() function to save the surface to a jpeg file, or IMG_SavePNG_RW() to save 
 *  the surface as jpeg data to a RWops data source. The prototypes of the two functions are
 *  very similar:
 *  <pre>
 *  int IMG_SaveJPG(const char *filename, SDL_Surface *surf, int quality);
 *  int IMG_SaveJPG_RW(SDL_RWops *dest, SDL_Surface *surf, int quality);</pre>
 *  The functions will save the specified surface to either the named file, or the RWops,
 *  at the quality specified. <code>quality</code> should be in the range 0 to 100, with 
 *  higher values producing larger but less lossy images. 
 *
 *  It is important to note that, as JPEG does not support palettised images or alpha
 *  channels, any surfaces that make use of these will be converted internally to truecolour
 *  format without alpha before it is saved. This process is completely transparent to your 
 *  code, and the surface you pass in will not be modified. 
 *
 *  \section pngsave Saving a SDL_Surface as PNG
 *
 *  As with JPEG saving, you may either use IMG_SavePNG() to save a surface to a png file, or
 *  IMG_SavePNG_RW() to save the surface as png data to a RWops data source. The prototypes
 *  should look familiar:
 *  <pre>
 *  int IMG_SavePNG(const char *filename, SDL_Surface *surf, int compression);
 *  int IMG_SavePNG_RW(SDL_RWops *dest, SDL_Surface *surf, int compression);</pre>
 *  The functions will save the specified surface to either the named file, or the RWops
 *  at the specified compression level. <code>compression</code> should be in the
 *  range 0 to 9, or -1 if you want to use zlib's default compression level. If you include
 *  zlib.h you can use the constants Z_NO_COMPRESSION, Z_BEST_SPEED, Z_BEST_COMPRESSION, or
 *  Z_DEFAULT_COMPRESSION if you prefer.
 *
 *  The PNG save code supports palettised surfaces, and will save the transparency
 *  information for the surface if SDL_SRCCOLORKEY is set and the image is palettised.
 *  True colour images with alpha channels are supported, but colour transparency via
 *  colorkey is not currently supported.
 *  
 */
/*  
 * Copyright (c) 2010, Chris Page <chris@starforge.co.uk>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this 
 *    list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice, this 
 *    list of conditions and the following disclaimer in the documentation and/or 
 *    other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __IMG_SAVE_
#define __IMG_SAVE_

#include <IMG_savepng.h>
#include <IMG_savejpg.h>

#endif //#ifndef __IMG_SAVE_
