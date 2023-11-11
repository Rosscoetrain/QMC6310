#include "QMC6310.h"

bool QMC6310::begin() {
  Wire.begin();
  Wire.beginTransmission(this->_ADDR);
//  Wire.write(QMC6310_CONTROL_2);
//  Wire.write(0b00001111); // Set mode to no reset, no self test, Range 8Gauss, set and reset off
  Wire.write(QMC6310_CONTROL_1);
//  Wire.write(0x1D); // Set mode to continuous, ODR to 200Hz, OSR to 512
  Wire.write(0b00011101); // Set mode to continuous, ODR to 200Hz, OSR to 512
  return (Wire.endTransmission() == 0); // Return true if transmission was successful
}

bool QMC6310::readData(int16_t &x, int16_t &y, int16_t &z) {
  // Check if data is ready
  Wire.beginTransmission(this->_ADDR);
  Wire.write(QMC6310_STATUS);
  if (Wire.endTransmission() != 0 || Wire.requestFrom(this->_ADDR, 1) != 1) {
    return false; // I2C transmission error
  }
  if ((Wire.read() & QMC6310_STATUS_DRDY) == 0) {
    return false; // Data not ready
  }

  // Read data
  Wire.beginTransmission(this->_ADDR);
  Wire.write(QMC6310_X_LSB);
  if (Wire.endTransmission() != 0 || Wire.requestFrom(this->_ADDR, 6) != 6) {
    return false; // I2C transmission error
  }
  x = Wire.read() | Wire.read() << 8;
  y = Wire.read() | Wire.read() << 8;
  z = Wire.read() | Wire.read() << 8;

  // Check if data is within expected range
  if (x < -32768 || x > 32767 || y < -32768 || y > 32767 || z < -32768 || z > 32767) {
    return false; // Data out of range
  }

  return true; // Data read successfully
}

/*
  set I2C address
*/

void QMC6310::setADDR(uint8_t b) {
  this->_ADDR = b;
}


uint8_t QMC6310::getMode1() {

}

void QMC6310::setMode1(uint8_t m) {

  Wire.write(QMC6310_CONTROL_1);
  Wire.write(m);

}

uint8_t QMC6310::getMode2() {

}

void QMC6310::setMode2(uint8_t m) {

  Wire.write(QMC6310_CONTROL_2);
  Wire.write(m);

}

// Reset the chip
void QMC6310::setReset(){
	_writeReg(QMC6310_CONTROL_1,0x80);
}


// Write register values to chip
void QMC6310::_writeReg(byte r, byte v){
	Wire.beginTransmission(_ADDR);
	Wire.write(r);
	Wire.write(v);
	Wire.endTransmission();
}
