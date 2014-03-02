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

#include "ArduRPC_CLTMatrix_GFX.h"

uint8_t ArduRPC_CLTMatrix_GFX_Wrapper(uint8_t cmd_id, ArduRPC *rpc, void *args)
{
  struct ArduRPC_CLTMatrix_GFX_options *options = (struct ArduRPC_CLTMatrix_GFX_options *)args;
  CLTMatrix *panel = (CLTMatrix*)options->panel;

  if (cmd_id == 0x01) {
    rpc->writeResult_uint8(3);
    return RPC_RETURN_SUCCESS;
  } else if (cmd_id == 0x02) {
    rpc->writeResult_uint16(panel->width());
    return RPC_RETURN_SUCCESS;
  } else if (cmd_id == 0x03) {
    rpc->writeResult_uint16(panel->height());
    return RPC_RETURN_SUCCESS;
  } else if(cmd_id == 0x11) {
    panel->drawPixel(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x20) {
    panel->drawLine(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x21) {
    panel->drawFastVLine(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x22) {
    panel->drawFastHLine(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x23) {
    panel->drawRect(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x24) {
    panel->fillRect(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x25) {
    panel->fillScreen(
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x26) {
    // ToDo
  } else if(cmd_id == 0x30) {
    panel->drawCircle(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x31) {
    panel->fillCircle(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x32) {
    panel->drawTriangle(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x33) {
    panel->fillTriangle(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x34) {
    panel->drawRoundRect(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x35) {
    panel->fillRoundRect(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x40) {
    panel->drawChar(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      rpc->getParam_uint8(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      ),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      ),
      rpc->getParam_uint8()
    );
  } else if(cmd_id == 0x41) {
    panel->setCursor(
      rpc->getParam_int16(),
      rpc->getParam_int16()
    );
  } else if(cmd_id == 0x42) {
    panel->setTextColor(
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x43) {
    panel->setTextColor(
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      ),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );
  } else if(cmd_id == 0x44) {
    panel->setTextSize(
      rpc->getParam_uint8()
    );
  } else if(cmd_id == 0x45) {
    panel->setTextWrap(
      rpc->getParam_uint8()
    );
  } else if(cmd_id == 0x46) {
    panel->write(
      rpc->getParam_uint8()
    );
  } else if(cmd_id == 0x50) {
    panel->setRotation(
      rpc->getParam_uint8()
    );
  } else if(cmd_id == 0x51) {
    // ToDo
    /*
    panel->drawBitmap(
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      //(uint8_t *)data[0],
      rpc->getParam_int16(),
      rpc->getParam_int16(),
      panel->color(
        rpc->getParam_uint8(),
        rpc->getParam_uint8(),
        rpc->getParam_uint8()
      )
    );*/
  } else if(cmd_id == 0xA0) {
    if(rpc->getParam_uint8() == 1) {
      panel->swapBuffers(true);
    } else {
      panel->swapBuffers(false);
    }
    return RPC_RETURN_SUCCESS;
  } else if(cmd_id == 0xA1) {
    options->auto_swap = rpc->getParam_uint8();
    return RPC_RETURN_SUCCESS;
  } else {
    return RPC_RETURN_COMMAND_NOT_FOUND;
  }
  if(options->auto_swap == 1)
    panel->swapBuffers(true);

  return RPC_RETURN_SUCCESS;
}

rpc_handler_t get_ArduRPC_CLTMatrix_GFX_Wrapper(CLTMatrix &panel)
{
  struct ArduRPC_CLTMatrix_GFX_options *options = (struct ArduRPC_CLTMatrix_GFX_options *)malloc(sizeof(struct ArduRPC_CLTMatrix_GFX_options));
  options->auto_swap = 1;
  options->panel = &panel;
  rpc_handler_t h = {0x0281, (void *)ArduRPC_CLTMatrix_GFX_Wrapper, (void *)options};
  return h;
}
