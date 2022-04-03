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
 *  Library available at https://github.com/manzarehassin/AT24C16
 
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

#define EEPROM_SIZE   2048
#define ROM_PAGE_SIZE 16

#define AT24CXX_EEPROM_DEFAULT_ADDRESS 0x50

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
    void Read(uint16_t address, uint8_t* data);            // Read one byte from EEPROM
    void Write(uint16_t address, uint8_t data);            // Write (update) one byte from EEPROM
    void readPage(unsigned address, uint8_t* buffer);      // Read page (16 bytes of data)
    void writePage(unsigned address, uint8_t* data);       // Write (update) page (16 bytes of data)
    
    void Memorymap();                                      // Show entire eeprom memory map
    
    // Get EEPROM info
    void getInfo(uint16_t* rom_size, uint8_t* page_size, uint8_t* totalPage, String* model); 
    void getInfo();
    
    // Erase entire EEPROM
    void Erase(uint16_t *execution_time, uint8_t *erase_count, bool *status);
    bool Erase();
    
    void readFloat(unsigned address, float* data);         // Read float type value from EEPROM [4 bytes]
    void readDouble(unsigned address, double* data);       // Read double type value from EEPROM [4 bytes]
    void readLong(unsigned address, long* data);           // Read long type value from EEPROM [4 bytes]
    void readInt(unsigned address, int* data);             // Read integer type value from EEPROM [2 bytes]
    void readStr(unsigned address, String* data, int len); // Read String from EEPROM [30 bytes max]
    
    void writeFloat(unsigned address, float value);        // Store float type value to EEPROM [4 bytes]
    void writeDouble(unsigned address, double value);      // Store double type value to EEPROM [4 bytes]
    void writeLong(unsigned address, long value);          // Store long type value to EEPROM [4 bytes]
    void writeInt(unsigned address, int value);            // Store integer type value to EEPROM [2 bytes]
    void writeStr(unsigned address, String val);           // Store String to EEPROM [30 bytes max]
    
    
  private:
  
    const PROGMEM byte _DeviceID = AT24CXX_EEPROM_DEFAULT_ADDRESS;

    void Write_(uint16_t address, uint8_t data);
    void readBuffer_(unsigned address, uint8_t* buffer, uint8_t length);
    void updateBuffer_(unsigned address, uint8_t* data, uint8_t length);
    void writeBuffer_(unsigned address, uint8_t* data, uint8_t length);
    
    void float_restore(float *value, uint8_t *data);
    void float_split(float *value, uint8_t *data);
    void double_restore(double *value, uint8_t *data);
    void double_split(double *value, uint8_t *data);
    void long_restore(long *value, uint8_t *data);
    void long_split(long *value, uint8_t *data);
    void int_restore(int *value, uint8_t *data);
    void int_split(int *value, uint8_t *data);
    
};
#endif
