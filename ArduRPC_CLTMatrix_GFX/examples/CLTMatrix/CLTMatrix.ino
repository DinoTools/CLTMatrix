/**
 * Dependencies:
 * - DHT - https://github.com/adafruit/DHT-sensor-library
 * - Adafruit_GFX - https://github.com/adafruit/Adafruit-GFX-Library
 * - CLTMatrix_GFX - https://github.com/DinoTools/CLTMatrix
 * - ArduRPC - https://github.com/DinoTools/ArduRPC
 * - ArduRPC_CLTMatrix_GFX - https://github.com/DinoTools/CLTMatrix
 * - ArduRPC_Adafruit_DHT - https://github.com/DinoTools/ArduRPC-handlers
 */

/* Load libraries for the DHT11 sensor */
#include <DHT.h>

/* Load libraries for the CLTMatrix */
#include <Adafruit_GFX.h>
#include <CLTMatrix_GFX.h>


/* Load libraries and wrappers for ArduRPC */
#include <ArduRPC.h>
#include <ArduRPC_CLTMatrix_GFX.h>
#include <ArduRPC_Adafruit_DHT.h>


/* Initialize AruRPC interface */

/* the serial port, it's also possible to use software serial */
#define RPC_SERIAL_PORT Serial
#define RPC_SERIAL_BAUD 19200

#define RPC_NUM_HANDLERS 3
#define RPC_NUM_FUNCTIONS 0

ArduRPC rpc = ArduRPC(RPC_NUM_HANDLERS, RPC_NUM_FUNCTIONS);
ArduRPC_Serial rpc_serial = ArduRPC_Serial(RPC_SERIAL_PORT, rpc);


/* Configure the Sensor */
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

ArduRPC_Adafruit_DHT Adafruit_DHT_Wrapper(rpc, "sensor", dht, DHTTYPE);


/* Configurate the matrix */
CLTMatrix Matrix;

ArduRPC_CLTMatrix_GFX CLTMatrix_GFX_Wrapper(rpc, "matrix", Matrix);

void setup() {
  /* Initialize the serial port */
  RPC_SERIAL_PORT.begin(RPC_SERIAL_BAUD);
  
  /* Activate the sensor */
  dht.begin();
  
  /* Initialize and activate the Matrix */
  Matrix.init();
  Matrix.begin();
}

void loop() {
  rpc_serial.readData();
}
