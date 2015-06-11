/**
 * CLTMatrix
 * Copyright (C) 2014-2015 PhiBo (DinoTools)
 *
 * This file is part of CLTMatrix.
 *
 * CLTMatrix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * CLTMatrix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CLTMATRIX_GFX_H_
#define _CLTMATRIX_GFX_H_

#define CLTMATRIX_GFX_MAJOR 1
#define CLTMATRIX_GFX_MINOR 0
#define CLTMATRIX_GFX_PATCH 0

#define CLTMATRIX_GFX_VERSION (CLTMATRIX_GFX_MAJOR * 10000 \
		              + CLTMATRIX_GFX_MINOR * 100 \
		              + CLTMATRIX_GFX_PATCH)

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
 #include "pins_arduino.h"
#endif

#define CLTMatrixBitsPerColor 8

#define CLTMatrixScreenWidth 8
#define CLTMatrixScreenHeight 8

#include <avr/io.h>

#define PC7     7
#define PC6     6
#define PC5     5
#define PC4     4
#define PC3     3
#define PC2     2
#define PC1     1
#define PC0     0

#define PB7     7
#define PB6     6
#define PB5     5
#define PB4     4
#define PB3     3
#define PB2     2
#define PB1     1
#define PB0     0
 
#include <avr/interrupt.h>

#include "Adafruit_GFX.h"

#ifndef GFX_COLOR_MODE
#define GFX_COLOR_16BIT 0
#define GFX_COLOR_8BIT 1
#define GFX_COLOR_RGB24BIT 2
#define GFX_COLOR_MODE 0
typedef uint16_t GFX_Color_t;
typedef int16_t GFX_Coord_t;
#endif

// this type is for internal use only
typedef struct {uint8_t r; uint8_t g; uint8_t b;} CLTMatrix_Color_t;

class CLTMatrix : public Adafruit_GFX {
  public:
    CLTMatrix_Color_t *writeBuffer;
    CLTMatrix_Color_t *activeBuffer;

    uint8_t line;

    CLTMatrix();
    CLTMatrix(int height, int width);

    void
      begin(void),
      drawPixel(GFX_Coord_t x, GFX_Coord_t y, GFX_Color_t color),
      init(void),
      init_io(void),
      init_tc2(void),
      fillColor(GFX_Color_t color),
      run(void),
      swapBuffers(boolean copy);

    GFX_Color_t
      color(uint8_t r, uint8_t g, uint8_t b);

    GFX_Color_t
      getActivePixel(GFX_Coord_t x, GFX_Coord_t y),
      getWritePixel(GFX_Coord_t x, GFX_Coord_t y);

    uint8_t
      step;

  private:
    CLTMatrix_Color_t
      *_getActivePixel(GFX_Coord_t x, GFX_Coord_t y),
      *_getWritePixel(GFX_Coord_t x, GFX_Coord_t y);

};
#endif
