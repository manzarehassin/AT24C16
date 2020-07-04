/* ==================================================================================
 *                           I2C EXTERNAL EEPROM LIBRARY (2K)
 * ================================================================================== 
 *  
 *  AT24C16 Library developed by Manzar E Hassin <mnz247@hotmail.com>
 *  
 *  Version 1.0.0 
 *  Release Date: Friday, July 3, 2020
 *  
 *  Library available at https://github.com/kittyboy2005/AT24C16
 
 MIT License

Copyright (c) 2020 Manzar-E-Hassin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 *  
 */
 
#include "AT24C16.h"

AT24C16::AT24C16()
{
  _DeviceID = DEFAULT_ADDRESS;
}

/*
void AT24C16::setID(byte DeviceID)
{
  _DeviceID = DeviceID;
}
*/

void AT24C16::Erase()
{
  for(uint16_t x=0;x<EEPROM_SIZE;x++)
  {
    Write(x,255);
  }
}

byte AT24C16::Read(uint16_t address)
{
  byte rdata=0;
  const byte ctrlByte = _DeviceID | (byte) (address >> 8);
  Wire.beginTransmission(ctrlByte); //MSB
  Wire.write((byte)address); // LSB
  Wire.endTransmission();
  delay(5);
  Wire.requestFrom(ctrlByte,1); //REQUEST
  if (Wire.available()) 
    {
      rdata = Wire.read();
    }
    return rdata;
} 

void AT24C16::Write(uint16_t address, byte data)
{
  byte prev_data = Read(address);
  const byte ctrlByte = _DeviceID | (byte) (address >> 8);
  if(prev_data!=data)
  {
    Wire.beginTransmission(ctrlByte);
    Wire.write((byte)address); // LSB
    delay(5);
    Wire.write(data);
    delay(5);
    Wire.endTransmission();
    delay(5);
  }
}
