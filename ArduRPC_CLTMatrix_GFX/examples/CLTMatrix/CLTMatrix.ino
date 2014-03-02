/**
 * Dependencies:
 * - DHT - https://github.com/adafruit/DHT-sensor-library
 * - Adafruit_GFX - https://github.com/adafruit/Adafruit-GFX-Library
 * - CLTMatrix_GFX - https://github.com/DinoTools/CLTMatrix
 * - ArduRPC - https://github.com/DinoTools/ArduRPC
 * - ArduRPC_CLTMatrix_GFX - https://github.com/DinoTools/CLTMatrix
 * - ArduRPC_Adafruit_DHT - https://github.com/DinoTools/ArduRPC-handlers
 */

// Load libraries for the DHT11 sensor
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Load libraries for the CLTMatrix
#include <Adafruit_GFX.h>
#include <CLTMatrix_GFX.h>

CLTMatrix Matrix;

// Load libraries and wrappers for ArduRPC
#include <ArduRPC.h>
#include <ArduRPC_CLTMatrix_GFX.h>
#include <ArduRPC_Adafruit_DHT.h>

#define RPC_NUM_HANDLERS 3
#define RPC_NUM_FUNCTIONS 0

// the serial port, it's also possible to use software serial
#define RPC_SERIAL_PORT Serial
#define RPC_SERIAL_BAUD 19200

ArduRPC rpc = ArduRPC(RPC_NUM_HANDLERS, RPC_NUM_FUNCTIONS);
ArduRPCSerial rpc_serial = ArduRPCSerial(RPC_SERIAL_PORT, rpc);

void setup() {
  uint8_t handler_id;

  // Initialize the serial port
  RPC_SERIAL_PORT.begin(RPC_SERIAL_BAUD);

  /* Matrix */
  
  // Initialize and active the Matrix
  Matrix.init();
  Matrix.begin();

  // Register the ArduRPC wrapper
  handler_id = rpc.connectHandler(get_ArduRPC_CLTMatrix_GFX_Wrapper(Matrix));

  // Set handler name for the Matrix
  rpc.setHandlerName(handler_id, "matrix");
  
  /* Sensor */
  
  // Activate the sensor
  dht.begin();
  
  // Register the ArduRPC wrapper
  handler_id = rpc.connectHandler(get_ArduRPC_Adafruit_DHT_Wrapper(dht, DHTTYPE));

  // Set handler name for the Sensor
  rpc.setHandlerName(handler_id, "sensor");
}

void loop() {
  rpc_serial.loop();
}
