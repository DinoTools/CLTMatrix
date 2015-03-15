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

#ifndef _ARDURPC_CLTMATRIX_GFX_H
#define _ARDURPC_CLTMATRIX_GFX_H

#include <avr/pgmspace.h>

#include "ArduRPC.h"
#include <CLTMatrix_GFX.h>

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class ArduRPC_CLTMatrix_GFX : public ArduRPCHandler
{
  public:
    ArduRPC_CLTMatrix_GFX(ArduRPC &rpc, char *name, CLTMatrix &panel);
    uint8_t
      call(uint8_t);
  private:
    CLTMatrix *panel;
    uint8_t auto_swap;
};

#endif
