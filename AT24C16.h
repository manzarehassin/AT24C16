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
 
#include <Wire.h>

#define EEPROM_SIZE 2048

#define DEFAULT_ADDRESS 0x50

#ifndef AT24C16_h
#define AT24C16_h

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class AT24C16
{
  public:
    // Constructor 
   AT24C16();

    // Methods
    void Erase();                             //Erase entire eeprom. Erase default value=255
    byte Read(uint16_t address);              //For reading single byte data from a specific location 
    void Write(uint16_t address, byte data);  //For writing single byte into a specific location
    
  private:
    byte _DeviceID;
};
#endif
