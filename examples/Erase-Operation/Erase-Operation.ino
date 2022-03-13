/* ==================================================================================
 *                     I2C EXTERNAL EEPROM LIBRARY v2.0 Example
 * ================================================================================== 
 * 
 *  ---------------------------------------------------------------------------------
 *  AT24C16 External EEPROM Library developed by Manzar E Hassin <mnz247@hotmail.com>
 *  ---------------------------------------------------------------------------------
 *  
 *  Connect a AT24C16 EEPROM chip and connect it to arduino board by following this diagram.
 *  https://github.com/kittyboy2005/AT24C16/blob/master/Pinout/AT24C16_pinout_screen.png
 *  ------------------------------------------------------------------------
 *  
 *  AT24C16 Library available at https://github.com/kittyboy2005/AT24C16
 *  
 *  ------------------------------------------------------------------------
 *  
 *  In this tutorial, we will show you Erase operation.
 *  
 */

#include <AT24C16.h>

AT24C16 rom;          // Initializing AT24C16 Library with the object named rom. Default slave id = 0x50

void setup() 
{
  Serial.begin(115200); // Initializing Serial at 2000000 bps.
  Wire.begin();       // Initializing I2C protocol (Master Mode)
 
  // READING OPERATION----------------------------------------------------------------------------
  Serial.println(F("Reading previously stored values from EEPROM chip...."));
  delay(2000);              // 2 seconds delay
  Serial.println();
  rom.Memorymap(); // EXECUTING READING SUB-ROUTINE 
  delay(2000);              // 2 seconds delay
  
  // ERASE OPERATION-----------------------------------------------------------------------------
  Serial.print(F("Erasing Process Started... "));
  uint16_t exec_time;
  uint8_t count;
  bool stat;
  
  //====================================================
  rom.Erase(&exec_time,&count, &stat); // Erase function
  //====================================================
  
  if(stat) { Serial.println(F("\t[Done]"));}
  else { Serial.println(F("\t[Failed]"));}
  Serial.print(F("Erased ")); Serial.print(count); Serial.println(F(" page(s)."));
  Serial.print(F("Process time: "));
  Serial.print(exec_time);
  Serial.println(F("ms"));
  delay(2000);              // 2 seconds delay
  
  //Verify--------------------------------------------------------------------------------------
  Serial.println(F("Present condition of EEPROM chip...."));
  rom.Memorymap(); // EXECUTING READING SUB-ROUTINE 
  rom.getInfo();   // Getting EEPROM info.
  Serial.println(F("All Done"));
}

void loop()
{
  // Nothing Here
}
