/**
 * CLTMatrix
 * Copyright (C) 2014 Philipp Seidel (DinoTools)
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

#include "CLTMatrix_GFX.h"

static CLTMatrix *activePanel = NULL;

CLTMatrix::CLTMatrix() : Adafruit_GFX(CLTMatrixScreenWidth, CLTMatrixScreenHeight)
{
  // create two buffers
  uint16_t len = CLTMatrixScreenWidth * CLTMatrixScreenHeight * sizeof(CLTMatrix_Color_t);
  this->writeBuffer = (CLTMatrix_Color_t *)malloc(len);
#if CLTMATRIX_LOW_MEM == 1
  this->activeBuffer = writeBuffer;
#else
  this->activeBuffer = (CLTMatrix_Color_t *)malloc(len);
#endif
  memset(this->writeBuffer, 0, len);
  memset(this->activeBuffer, 0, len);
  this->line = 0;
}

/**
 * Initialize the matrix and set it as active.
 */
void CLTMatrix::begin(void) {
  activePanel = this;
}

/**
 * Helper function to prepare color data
 *
 * @param r: Red value 0-255
 * @param g: Green value 0-255
 * @param b: Blue value 0-255
 *
 * @return: Color data
 */
GFX_Color_t CLTMatrix::color(uint8_t r, uint8_t g, uint8_t b)
{
#if GFX_COLOR_MODE == GFX_COLOR_16BIT
  GFX_Color_t color;
  color = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
#elif GFX_COLOR_MODE == GFX_COLOR_RGB24BIT
  GFX_Color_t color = {r, g, b};
#endif
  return color;
}

/**
 * Draw a Pixel
 *
 * @param x: X-coordinate
 * @param y: Y-coordinate
 * @param color: The color value
 */
void CLTMatrix::drawPixel(GFX_Coord_t x, GFX_Coord_t y, GFX_Color_t color)
{
  if(x > 7 || y > 7 || x < 0 || y < 0)
    return;
  
  CLTMatrix_Color_t *p = this->_getWritePixel(x,y);
#if GFX_COLOR_MODE == GFX_COLOR_16BIT
  p->r = (uint8_t)(color >> 8) & 0xF8;
  p->g = (uint8_t)(color >> 3) & 0xFC;
  p->b = (uint8_t)(color << 3);
#elif GFX_COLOR_MODE == GFX_COLOR_RGB24BIT
  p->r = color.r;
  p->g = color.g;
  p->b = color.b;
#endif
}

/**
 * Use the color to fill the screen.
 *
 * @param color: The color value
 */
void CLTMatrix::fillColor(GFX_Color_t color)
{
  CLTMatrix_Color_t *p = this->_getWritePixel(0, 0);
  uint8_t r, g, b;
  uint8_t x, y;
#if GFX_COLOR_MODE == GFX_COLOR_16BIT
  r = (uint8_t)(color >> 8) & 0xF8;
  g = (uint8_t)(color >> 3) & 0xFC;
  b = (uint8_t)(color << 3);
#elif GFX_COLOR_MODE == GFX_COLOR_RGB24BIT
  r = color.r;
  g = color.g;
  b = color.b;
#endif
  for (y = 0; y < CLTMatrixScreenWidth; y++) {
    for (x = 0; x < CLTMatrixScreenHeight; x++) {
      p->r = r;
      p->g = g;
      p->b = b;
      p++;
    }
  }
}

/**
 * Get the color of a pixel from the active framebuffer.
 *
 * @param x: X-coordinate
 * @param y: Y-coordinate
 * @return: The color value
 */
GFX_Color_t CLTMatrix::getActivePixel(GFX_Coord_t x, GFX_Coord_t y)
{
  CLTMatrix_Color_t *c = this->activeBuffer + (y * CLTMatrixScreenWidth) + x;
  return this->color(c->r, c->g, c->b);
}

/**
 * Get the raw color of a pixel from the active framebuffer.
 *
 * @param x: X-coordinate
 * @param y: Y-coordinate
 * @return: Pointer to the pixel
 */
CLTMatrix_Color_t *CLTMatrix::_getActivePixel(GFX_Coord_t x, GFX_Coord_t y)
{
  return this->activeBuffer + (y * CLTMatrixScreenWidth) + x;
}

/**
 * Get the color of a pixel from the write framebuffer.
 *
 * @param x: X-coordinate
 * @param y: Y-coordinate
 * @return: The color value
 */
GFX_Color_t CLTMatrix::getWritePixel(GFX_Coord_t x, GFX_Coord_t y)
{
  CLTMatrix_Color_t *c = this->writeBuffer + (y * CLTMatrixScreenWidth) + x;
  return this->color(c->r, c->g, c->b);
}

/**
 * Get the raw color of a pixel from the write framebuffer.
 *
 * @param x: X-coordinate
 * @param y: Y-coordinate
 * @return: Pointer to the pixel
 */
CLTMatrix_Color_t *CLTMatrix::_getWritePixel(GFX_Coord_t x, GFX_Coord_t y)
{
  return this->writeBuffer + (y * CLTMatrixScreenWidth) + x;
}

/**
 * Initialize
 */
void CLTMatrix::init(void)
{
  this->init_io();
  this->init_tc2();
  this->line = 0;
}

/**
 * Initialize IO
 */
void CLTMatrix::init_io()
{
#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega168__)
  DDRC = 0xff;
  DDRB = 0xff;
  
  PORTC = 0x00;
  PORTB = 0x00;
#else
  uint8_t lines[] = {A1,A2,A3,A4,A5,9,10,11,12,13};
  uint8_t i;

  for (i = 0; i < 10;i++) {
    pinMode(lines[i], OUTPUT);
    digitalWrite(lines[i], LOW);
  }
#endif
}

/**
 * Initialize the time.
 */
void CLTMatrix::init_tc2()
{
  // TCNT2 increments every  = 16MHz / prescaler

  // set prescaler to 128 -> TCNT2 freq = 125KHz
  TCCR2B |= ((1<<CS22)|(1<<CS20));
  TCCR2B &= ~((1<<CS21));   

  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));   // Use normal mode
  ASSR |= (1<<AS2);       // Use internal clock - external clock not used in Arduino
  TIMSK2 |= ((1<<TOIE2) | (0<<OCIE2B));   //Timer2 Overflow Interrupt Enable
  TCNT2 = 0xff;

  sei();
}

/**
 * Load data into the registers.
 */
void CLTMatrix::run(void)
{
  CLTMatrix_Color_t *pixel = this->_getActivePixel(0, this->line);
  uint8_t tmp_line = this->line;
  uint8_t portc;
  uint8_t temp;
  uint8_t i;

  // off
  PORTC &= ~(1<<PC1);

  // shift data into registers
  for (i = 0; i < 8; i++) {
    PORTB &= ~(1<<PB4);
    temp = pixel->b;
    if (temp > this->step)
      PORTB |= (1<<PB2);
    else
      PORTB &= ~(1<<PB2);
      
    temp = pixel->g;
    if (temp > this->step)
      PORTB |= (1<<PB5);
    else
      PORTB &= ~(1<<PB5);

    temp = pixel->r;
    if (temp > this->step)
      PORTB |= (1<<PB1);
    else
      PORTB &= ~(1<<PB1);
    pixel++;
    PORTB |= (1<<PB4);
  }

  // load serial data
  PORTB |= (1 << PB3);
  PORTB &= ~(1 << PB3);

  if (tmp_line > 3)
    tmp_line = 11 - tmp_line;

  portc = PORTC & 0b11000111;

  if (tmp_line & 0b00000100)
    portc = portc | 0b00001000;
  if (tmp_line & 0b00000010)
    portc = portc | 0b00010000;
  if (tmp_line & 0b000000001)
    portc = portc | 0b00100000;
 
  PORTC = portc;
  // load MUX data
  PORTC &= ~(1 << PC2);
  PORTC |= (1 << PC2);

  // on
  PORTC |= (1 << PC1);
}

/**
 * Swap the active and the write buffer.
 *
 * @param copy: Copy the new active buffer into the write buffer.
 */
void CLTMatrix::swapBuffers(boolean copy)
{
  cli();
  // swap frame buffers
  CLTMatrix_Color_t *tmp = this->activeBuffer;
  this->activeBuffer = this->writeBuffer;
  this->writeBuffer = tmp;
  if (copy == true)
    memcpy(this->writeBuffer, this->activeBuffer, CLTMatrixScreenWidth * CLTMatrixScreenHeight * sizeof(CLTMatrix_Color_t));

  sei();
}

/**
 * The timer interrupt.
 */
ISR(TIMER2_OVF_vect)
{ 
  // ISR fires every 256-TCNT2 ticks
  TCNT2 = 230;
  if(activePanel == NULL)
    return;

  activePanel->run();
  if (++activePanel->line > 7) {
    activePanel->line = 0;
    if (activePanel->step < 8)
      activePanel->step = 255;
    else
      activePanel->step /= 2;
  }
}
