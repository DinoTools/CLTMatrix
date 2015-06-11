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

#include "ArduRPC_CLTMatrix_GFX.h"

ArduRPC_CLTMatrix_GFX::ArduRPC_CLTMatrix_GFX(ArduRPC &rpc, char *name, CLTMatrix &panel) : ArduRPCHandler()
{
  this->type = 0x0280;
  this->registerSelf(rpc, name, (void *)this);

  this->panel = &panel;
  this->auto_swap = 1;
}

uint8_t ArduRPC_CLTMatrix_GFX::call(uint8_t cmd_id)
{
  uint16_t x1, y1, x2, y2;
  uint8_t r, g, b;

  uint16_t tmp_u16_1, tmp_u16_2;
  uint8_t tmp_u8;
  uint8_t height;
  uint8_t width;
  uint8_t c, i, j, k;

  if (cmd_id == 0x01) {
    this->_rpc->writeResult_uint8(3);
    return RPC_RETURN_SUCCESS;
  } else if (cmd_id == 0x02) {
    this->_rpc->writeResult_uint16(this->panel->width());
    return RPC_RETURN_SUCCESS;
  } else if (cmd_id == 0x03) {
    this->_rpc->writeResult_uint16(this->panel->height());
    return RPC_RETURN_SUCCESS;
  } else if(cmd_id == 0x11) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();

    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->drawPixel(x1, y1, this->panel->color(r,g,b));
  } else if(cmd_id == 0x21) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();
    x2 = this->_rpc->getParam_int16();
    y2 = this->_rpc->getParam_int16();

    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->drawLine(x1, y1, x2, y2, this->panel->color(r,g,b));
  } else if(cmd_id == 0x22) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();

    /* Height */
    tmp_u16_1 = this->_rpc->getParam_int16();

    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->drawFastVLine(
      x1, y1,
      tmp_u16_1,
      this->panel->color(r, g, b)
    );
  } else if(cmd_id == 0x23) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();

    /* width */
    tmp_u16_1 = this->_rpc->getParam_int16();

    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->drawFastHLine(
      x1, y1,
      tmp_u16_1,
      this->panel->color(r, g, b)
    );
  } else if(cmd_id == 0x24) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();
    x2 = this->_rpc->getParam_int16();
    y2 = this->_rpc->getParam_int16();

    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->drawRect(x1, y1, x2, y2, this->panel->color(r, g, b));
  } else if(cmd_id == 0x25) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();
    x2 = this->_rpc->getParam_int16();
    y2 = this->_rpc->getParam_int16();

    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->fillRect(x1, y1, x2, y2, this->panel->color(r, g, b));
  } else if(cmd_id == 0x26) {
    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->fillScreen(this->panel->color(r, g, b));
  } else if(cmd_id == 0x27) {
    // ToDo
  } else if(cmd_id == 0x31) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();

    /* Radius */
    tmp_u16_1 = this->_rpc->getParam_int16();

    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->drawCircle(x1, y1, tmp_u16_1, this->panel->color(r, g, b));
  } else if(cmd_id == 0x32) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();

    /* Radius */
    tmp_u16_1 = this->_rpc->getParam_int16();

    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->fillCircle(x1, y1, tmp_u16_1, this->panel->color(r, g, b));
  } else if(cmd_id == 0x33) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();
    x2 = this->_rpc->getParam_int16();
    y2 = this->_rpc->getParam_int16();
    tmp_u16_1 = this->_rpc->getParam_int16();
    tmp_u16_2 = this->_rpc->getParam_int16();

    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->drawTriangle(
      x1, y1,
      x2, y2,
      tmp_u16_1, tmp_u16_2,
      this->panel->color(r, g, b)
    );
  } else if(cmd_id == 0x34) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();
    x2 = this->_rpc->getParam_int16();
    y2 = this->_rpc->getParam_int16();
    tmp_u16_1 = this->_rpc->getParam_int16();
    tmp_u16_2 = this->_rpc->getParam_int16();

    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->fillTriangle(
      x1, y1,
      x2, y2,
      tmp_u16_1, tmp_u16_2,
      this->panel->color(r, g, b)
    );
  } else if(cmd_id == 0x35) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();
    x2 = this->_rpc->getParam_int16();
    y2 = this->_rpc->getParam_int16();

    /* Radius */
    tmp_u16_1 = this->_rpc->getParam_int16();

    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->drawRoundRect(x1, y1, x2, y2, tmp_u16_1, this->panel->color(r, g, b));
  } else if(cmd_id == 0x36) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();
    x2 = this->_rpc->getParam_int16();
    y2 = this->_rpc->getParam_int16();

    /* Radius */
    tmp_u16_1 = this->_rpc->getParam_int16();

    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->fillRoundRect(x1, y1, x2, y2, tmp_u16_1, this->panel->color(r, g, b));
  } else if(cmd_id == 0x41) {
    /* Position */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();

    /* Character */
    c = this->_rpc->getParam_uint8();

    /* Color: foreground */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    /* Color: background */
    i = this->_rpc->getParam_uint8();
    j = this->_rpc->getParam_uint8();
    k = this->_rpc->getParam_uint8();

    /* Size */
    tmp_u8 = this->_rpc->getParam_uint8();

    this->panel->drawChar(
      x1, y1,
      c,
      this->panel->color(r, g, b),
      this->panel->color(i, j, k),
      tmp_u8
    );
  } else if(cmd_id == 0x42) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();

    this->panel->setCursor(x1, y1);
  } else if(cmd_id == 0x43) {
    /* Color */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    this->panel->setTextColor(this->panel->color(r, g, b));
  } else if(cmd_id == 0x44) {
    /* Color: foreground */
    r = this->_rpc->getParam_uint8();
    g = this->_rpc->getParam_uint8();
    b = this->_rpc->getParam_uint8();

    /* Color: background */
    i = this->_rpc->getParam_uint8();
    j = this->_rpc->getParam_uint8();
    k = this->_rpc->getParam_uint8();

    this->panel->setTextColor(
      this->panel->color(r, g, b),
      this->panel->color(i, j, k)
    );
  } else if(cmd_id == 0x45) {
    /* Size */
    i = this->_rpc->getParam_uint8();

    this->panel->setTextSize(i);
  } else if(cmd_id == 0x46) {
    /* Textwrap */
    i = this->_rpc->getParam_uint8();

    this->panel->setTextWrap(i);
  } else if(cmd_id == 0x47) {
    /* Char */
    i = this->_rpc->getParam_uint8();

    this->panel->write(i);
  } else if(cmd_id == 0x51) {
    /* Rotation */
    i = this->_rpc->getParam_uint8();

    this->panel->setRotation(i);
  } else if(cmd_id == 0x52) {
    /* Copy buffer */
    i = this->_rpc->getParam_uint8();
    if(i == 1) {
      this->panel->swapBuffers(true);
    } else {
      this->panel->swapBuffers(false);
    }
    return RPC_RETURN_SUCCESS;
  } else if(cmd_id == 0x53) {
    /* Auto swap */
    i = this->_rpc->getParam_uint8();

    this->auto_swap = i;
    return RPC_RETURN_SUCCESS;
  } else if(cmd_id == 0x61) {
    /* Coordinates */
    x1 = this->_rpc->getParam_int16();
    y1 = this->_rpc->getParam_int16();

    /* Width and height of the image */
    width = this->_rpc->getParam_uint8();
    height = this->_rpc->getParam_uint8();

    /* Encoding: color */
    tmp_u8 = this->_rpc->getParam_uint8();

    if (tmp_u8 == 0) {
      for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
          tmp_u8 = this->_rpc->getParam_uint8();
          this->panel->drawPixel(
            x1 + j,
            y1 + i,
            this->panel->color(
              ((tmp_u8 & 0b11000000) >> 6) * 85,
              ((tmp_u8 & 0b00111000) >> 3) * 36,
              (tmp_u8 & 0b00000111) * 36
            )
          );
        }
      }
    } else if (tmp_u8 == 1) {
      for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
          tmp_u16_1 = this->_rpc->getParam_uint16();
          this->panel->drawPixel(
            x1 + j,
            y1 + i,
            this->panel->color(
              ((tmp_u16_1 & 0b1111100000000000) >> 11) * 8,
              ((tmp_u16_1 & 0b0000011111100000) >> 5) * 4,
              ((tmp_u16_1 & 0b0000000000011111)) * 8
            )
          );
        }
      }
    } else if (tmp_u8 == 2) {
      for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
          r = this->_rpc->getParam_uint8();
          g = this->_rpc->getParam_uint8();
          b = this->_rpc->getParam_uint8();
          this->panel->drawPixel(
            x1 + j,
            y1 + i,
            this->panel->color(r, g, b)
          );
        }
      }
    }
  } else {
    return RPC_RETURN_COMMAND_NOT_FOUND;
  }

  if(this->auto_swap == 1) {
    this->panel->swapBuffers(true);
  }

  return RPC_RETURN_SUCCESS;
}
