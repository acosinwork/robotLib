
#include <Arduino.h>
#include <Wire.h>

#include "lis3mdl.h"


#define CTRL_REG1       0x20

#define OUT_X           0x28
#define OUT_Y           0x2A
#define OUT_Z           0x2C


LIS3MDL_TWI::LIS3MDL_TWI(uint8_t addr)
{
    _addr = addr;

    _ctrlReg1 = 0x0;
}

void LIS3MDL_TWI::begin()
{
    Wire.begin();

    Wire.beginTransmission(_addr);
    Wire.write(0x22);
    Wire.write(0);
    Wire.endTransmission();
}


int16_t LIS3MDL_TWI::readX()
{
    return readAxis(OUT_X);
}

int16_t LIS3MDL_TWI::readY()
{
    return readAxis(OUT_Y);
}

int16_t LIS3MDL_TWI::readZ()
{
    return readAxis(OUT_Z);
}

int16_t LIS3MDL_TWI::readAxis(uint8_t reg)
{
    Wire.beginTransmission(_addr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_addr, 1);
    while (Wire.available() < 1)
        ;
    uint8_t lowByte = Wire.read();

    ++reg;

    Wire.beginTransmission(_addr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(_addr, 1);
    while (Wire.available() < 1)
        ;
    uint8_t highByte = Wire.read();

    return ((int16_t)highByte << 8) | lowByte;

}

void LIS3MDL_TWI::writeCtrlReg1()
{
    Wire.beginTransmission(_addr);
    Wire.write(CTRL_REG1);
    Wire.write(_ctrlReg1);
    Wire.endTransmission();
}
