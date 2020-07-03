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
