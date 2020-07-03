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
