/*
Basic example of read data from QMC6310
*/

#include "QMC6310.h"

#define QMC6310_ADDRESS 0x1C

QMC6310 hallSensor;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting ...");

  if (!hallSensor.begin()) {
    Serial.println("Failed to ini alize QMC6310 sensor!");
    while (1);
   }
}

void loop() {
  int16_t x, y, z;
  if (hallSensor.readData(x, y, z)) {
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(" Y: ");
    Serial.print(y);
    Serial.print(" Z: ");
    Serial.println(z);
   } else {
    Serial.println("Failed to read data from QMC6310 sensor!");
 }
 delay(2000);
}
