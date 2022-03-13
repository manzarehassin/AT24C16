/* ==================================================================================
 *                           I2C EXTERNAL EEPROM LIBRARY (2K)
 * ================================================================================== 
 *  
 *  AT24C16 Library developed by Manzar E Hassin <mnz247@hotmail.com>
 *  
 *  Version 2.0.0 
 *  
 *  Release Date: Sunday, March 13, 2022
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

}

void AT24C16::Read(uint16_t address, uint8_t* data) // read 1 byte [Public Function]
{
  const uint8_t ctrlByte = _DeviceID | ((address >> 8) & 0x07);
  const uint8_t addr_ = address;
  Wire.beginTransmission(ctrlByte);
  Wire.write(int(addr_));
  Wire.endTransmission();
  Wire.requestFrom(ctrlByte,1);
  if(Wire.available()) 
  {
    *data = Wire.read();
  }
}

void AT24C16::Write(uint16_t address, uint8_t data) // update 1 byte [Public Function]
{
  byte prevdata;
  Read(address, &prevdata);
  if(data != prevdata)
  {
    Write_(address,data);
  }
}

void AT24C16::Write_(uint16_t address, uint8_t data) // write 1 byte (no verify) [Internal Function]
{
    const uint8_t devaddr = _DeviceID | ((address >> 8) & 0x07);
    const uint8_t addr    = address;
    Wire.beginTransmission(devaddr);
    Wire.write(int(addr));
    Wire.write(int(data));
    Wire.endTransmission();
    delay(5);
}

void AT24C16::readBuffer_(unsigned address, uint8_t* buffer, uint8_t length) // read buffer [Internal Function]
{
  const uint8_t devaddr = _DeviceID | ((address >> 8) & 0x07);
  const uint8_t addr    = address;
  Wire.beginTransmission(devaddr);
  Wire.write(int(addr));
  Wire.endTransmission();
  delay(5);
  Wire.requestFrom(devaddr, length);
  for (uint8_t i = 0; i < length && Wire.available(); i++)
  {
    buffer[i] = Wire.read();
  }
}

void AT24C16::writeBuffer_(unsigned address, uint8_t* data, uint8_t length) // write buffer (no verify). [Internal Function]
{
    const byte devaddr = _DeviceID | ((address >> 8) & 0x07);
    const byte addr    = address;
    Wire.beginTransmission(devaddr);
    Wire.write(int(addr));
    for (uint8_t i = 0; i < length; i++)
    {
      Wire.write(data[i]);
    }
    Wire.endTransmission();
    delay(10);
}

void AT24C16::updateBuffer_(unsigned address, uint8_t* data, uint8_t length) // update buffer [Internal Function]
{
  uint8_t prev_data[length];
  readBuffer_(address,prev_data,length);
  for(uint8_t i=0;i<length;i++)
  {
    if(prev_data[i] != data[i])
    {
      Write_(address + i, data[i]);
    }
  }
}

void AT24C16::readPage(unsigned address, uint8_t* buffer) // read page [Public Function]
{
  readBuffer_(address,buffer,ROM_PAGE_SIZE);
}

void AT24C16::writePage(unsigned address, uint8_t* data) // update page [Public Function]
{
  updateBuffer_(address,data,ROM_PAGE_SIZE);
}

void AT24C16::Erase(uint16_t *execution_time, uint8_t *erase_count, bool *status) // Erase entire EEPROM [Public Function]
{
  const unsigned long prev = millis();
  uint8_t count=0;
  for(unsigned int i=0; i<EEPROM_SIZE;i+=ROM_PAGE_SIZE)
  {
    uint8_t buffer[ROM_PAGE_SIZE];
    readPage(i, buffer);
    bool x=0;
    for(uint8_t b=0;b<ROM_PAGE_SIZE;b++)
    {
      if(buffer[b] < 0xff)
      {
        x=1;
      }
    }
    if(x)
    {
      const PROGMEM uint8_t Empty_buffer[ROM_PAGE_SIZE]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
      writeBuffer_(i, Empty_buffer, ROM_PAGE_SIZE);
      count++;
    }
  }
  *execution_time = millis() - prev;
  *erase_count = count;
  //verify -----------------------------------------------
  bool res=0;
  for(unsigned int j=0; j<EEPROM_SIZE;j+=ROM_PAGE_SIZE)
  {
    uint8_t buffer1[ROM_PAGE_SIZE];
    readPage(j, buffer1);
    for(uint8_t c=0;c<ROM_PAGE_SIZE;c++)
    {
      if(buffer1[c] <0xff)
      {
        res=1;
      }
    }
  }
  *status = !(res);
}

bool AT24C16::Erase() // Erase entire EEPROM [Public Function]
{
  for(unsigned int i=0; i<EEPROM_SIZE;i+=ROM_PAGE_SIZE)
  {
    uint8_t buffer[ROM_PAGE_SIZE];
    readPage(i, buffer);
    bool x=0;
    for(uint8_t b=0;b<ROM_PAGE_SIZE;b++)
    {
      if(buffer[b] <0xff)
      {
        x=1;
      }
    }
    if(x)
    {
      const PROGMEM byte Empty_buffer[ROM_PAGE_SIZE]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
      writeBuffer_(i, Empty_buffer, ROM_PAGE_SIZE);
    }
  }

  //verify -----------------------------------------------
  bool res=0;
  for(unsigned int j=0; j<EEPROM_SIZE;j+=ROM_PAGE_SIZE)
  {
    uint8_t buffer1[ROM_PAGE_SIZE];
    readPage(j, buffer1);
    for(uint8_t c=0;c<ROM_PAGE_SIZE;c++)
    {
      if(buffer1[c] <0xff)
      {
        res=1;
      }
    }
  }
  return !(res);
}

void AT24C16::float_restore(float *value, uint8_t *data) // [Internal Function]
{
  for(uint8_t i=0;i<4;i++)
  {
    ((uint8_t*)value)[i] = *data;
    data++;
  }
}

void AT24C16::float_split(float *value, uint8_t *data) // [Internal Function]
{
  for(uint8_t i=0;i<4;i++)
  {
    *data = ((uint8_t*)value)[i];
    data++; //index
  }
}

void AT24C16::double_restore(double *value, uint8_t *data) // [Internal Function]
{
  for(uint8_t i=0;i<4;i++)
  {
    ((uint8_t*)value)[i] = *data; //restoring
    data++; //index
  }
}

void AT24C16::double_split(double *value, uint8_t *data) // [Internal Function]
{
  for(uint8_t i=0;i<4;i++)
  {
    *data = ((uint8_t*)value)[i]; //splitting
    data++; //index
  }
}

void AT24C16::long_restore(long *value, uint8_t *data) // [Internal Function]
{
  for(uint8_t i=0;i<4;i++)
  {
    ((uint8_t*)value)[i] = *data; //restoring
    data++; //index
  }
}

void AT24C16::long_split(long *value, uint8_t *data) // [Internal Function]
{
  for(uint8_t i=0;i<4;i++)
  {
    *data = ((uint8_t*)value)[i]; //splitting
    data++; //index
  }
}

void AT24C16::int_restore(int *value, uint8_t *data) // [Internal Function]
{
  for(uint8_t i=0;i<2;i++)
  {
    ((uint8_t*)value)[i] = *data; //restoring
    data++; //index
  }
}

void AT24C16::int_split(int *value, uint8_t *data) // [Internal Function]
{
  for(uint8_t i=0;i<2;i++)
  {
    *data = ((uint8_t*)value)[i]; //splitting
    data++; //index
  }
}

void AT24C16::readFloat(unsigned address, float* data) // [Public Function]
{
  uint8_t buffer[4];
  readBuffer_(address, buffer, 4);
  float_restore(data, &buffer[0]);
}

void AT24C16::readDouble(unsigned address, double* data) // [Public Function]
{
  uint8_t buffer[4];
  readBuffer_(address, buffer, 4);
  double_restore(data, &buffer[0]);
}

void AT24C16::readLong(unsigned address, long* data) // [Public Function]
{
  uint8_t buffer[4];
  readBuffer_(address, buffer, 4);
  long_restore(data, &buffer[0]);
}

void AT24C16::readInt(unsigned address, int* data) // [Public Function]
{
  uint8_t buffer[2];
  readBuffer_(address, buffer, 2);
  int_restore(data, &buffer[0]);
}

void AT24C16::readStr(unsigned address, String* data, int len) // [Public Function]
{
  uint8_t buffer[len+1];
  readBuffer_(address, buffer, len+1);
  *data = "";
  for(uint8_t i=0;i<len+1;i++)
  {
    *data = *data + (char)buffer[i]; 
  }
}

void AT24C16::writeFloat(unsigned address, float value) // [Public Function]
{
  uint8_t buffer[4];
  float_split(&value, &buffer[0]);
  updateBuffer_(address, buffer, 4);
}

void AT24C16::writeDouble(unsigned address, double value) // [Public Function]
{
  uint8_t buffer[4];
  double_split(&value, &buffer[0]);
  updateBuffer_(address, buffer, 4);
}

void AT24C16::writeLong(unsigned address, long value) // [Public Function]
{
  uint8_t buffer[4];
  long_split(&value, &buffer[0]);
  updateBuffer_(address, buffer, 4);
}

void AT24C16::writeInt(unsigned address, int value) // [Public Function]
{
  uint8_t buffer[2];
  int_split(&value, &buffer[0]);
  updateBuffer_(address, buffer, 2);
}

void AT24C16::writeStr(unsigned address, String val) // [Public Function]
{
  const uint8_t len = val.length()+1;
  char buffer[len];
  val.toCharArray(buffer, len);
  updateBuffer_(address, buffer, len);
}

void AT24C16::getInfo(uint16_t* rom_size, uint8_t* page_size, uint8_t* totalPage, String* model)
{
  *rom_size   = EEPROM_SIZE;
  *page_size  = ROM_PAGE_SIZE;
  *totalPage  = EEPROM_SIZE / ROM_PAGE_SIZE;
  *model      = F("AT24C16");
}

void AT24C16::getInfo()
{
  Serial.println(F("\nEEPROM info\n==============="));
  Serial.print(F("EEPROM Model\t: "));Serial.println(F("AT24C16"));
  Serial.print(F("EEPROM I2C ID\t: "));Serial.print(F("0x"));Serial.println(_DeviceID,HEX);
  Serial.print(F("EEPROM Size\t: "));Serial.print (EEPROM_SIZE); Serial.println(F(" bytes"));
  Serial.print(F("Page Size\t: "));Serial.print(ROM_PAGE_SIZE); Serial.println(F(" bytes"));
  Serial.print(F("Page Count\t: "));Serial.print(EEPROM_SIZE / ROM_PAGE_SIZE); Serial.println(F(" pages"));
  unsigned int free_space=0;
  for(unsigned int i=0; i<EEPROM_SIZE;i++)
  {
    uint8_t buffer;
    Read(i, &buffer);
    if(buffer== 0xff)
    {
      free_space++;
    }
  }
  Serial.print(F("Total used\t: "));Serial.print(EEPROM_SIZE - free_space);Serial.println(F(" bytes"));
  Serial.print(F("Total free\t: "));Serial.print(free_space);Serial.println(F(" bytes"));
}

void AT24C16::Memorymap()
{
  const PROGMEM byte cycle= EEPROM_SIZE / ROM_PAGE_SIZE;
  Serial.println(F("\nEEPROM Memory map"));
  Serial.println(F("================================================================="));
  for(uint8_t p=0;p<cycle;p++)
  {
    uint8_t buffer[ROM_PAGE_SIZE];
    readPage(p*ROM_PAGE_SIZE,buffer);
    Serial.print(F("Page# ")); Serial.print(p); Serial.print(F(" : \t"));
    for(uint8_t i=0; i<ROM_PAGE_SIZE;i++)
    {
      String v=String(buffer[i],HEX);
      v.toUpperCase();
      if(v.length()==1)
      {
        v="0" + v;
      }
      Serial.print(v);Serial.print(F("  "));
    }
    Serial.println();
  }
  Serial.println();
  Serial.println(F("(i) Value = 'FF' means empty space.\n"));
}
