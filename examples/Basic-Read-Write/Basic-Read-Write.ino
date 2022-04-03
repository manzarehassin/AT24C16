/* ==================================================================================
 *                     I2C EXTERNAL EEPROM LIBRARY v2.0 Example
 * ================================================================================== 
 * 
 *  ---------------------------------------------------------------------------------
 *  AT24C16 External EEPROM Library developed by Manzar E Hassin <mnz247@hotmail.com>
 *  ---------------------------------------------------------------------------------
 *  
 *  Connect a AT24C16 EEPROM chip and connect it to arduino board by following this diagram.
 *  https://github.com/manzarehassin/AT24C16/blob/master/Pinout/AT24C16_pinout_screen.png
 *  ------------------------------------------------------------------------
 *  
 *  AT24C16 Library available at https://github.com/manzarehassin/AT24C16
 *  
 *  ------------------------------------------------------------------------
 *  
 *  In this tutorial, we will show you the basic read write operation.
 */

#include <AT24C16.h>

AT24C16 rom;          // Initializing AT24C16 Library with the object named rom. Default slave id = 0x50

void setup() 
{
  Serial.begin(2000000); // Initializing Serial at 2000000 bps.
  Wire.begin();       // Initializing I2C protocol (Master Mode)
 
  // READING OPERATION-----------------------------------------------------------------------------------------------------------
  Serial.println(F("Reading previously stored values from EEPROM chip...."));
  delay(2000);         // 2 seconds delay
  Serial.println();
  Reading_operation(); // EXECUTING READING SUB-ROUTINE 
  delay(2000);         // 2 seconds delay
  
  // WRITING OPERATION-----------------------------------------------------------------------------------------------------------
  Serial.println(F("Writing 0xAA into EEPROM chip address from 2040-2047 ...."));
  delay(2000);         // 2 seconds delay
  Serial.println();
  Writing_operation(); // EXECUTING WRITING SUB-ROUTINE 
  
  // VERIFICATION (READING OPERATION) -------------------------------------------------------------------------------------------
  Serial.println(F("Verifying...."));
  delay(2000);         // 2 seconds delay
  Serial.println();
  Reading_operation(); // EXECUTING READING SUB-ROUTINE 
  Serial.println();
  Serial.println(F("All Done"));
}

void loop()
{
  //Nothing Here
}

void Reading_operation() // READING SUB-ROUTINE
{
  Serial.println(F("Address \t Value"));
  Serial.println(F("====================================================="));
  
  // Loop for reading data from all possible addresses. Valid addressing range: 0-2047
  for(int i=0; i<EEPROM_SIZE; i++) 
  {
    //-----------------------------------------------------------------------------------------------------------------
    byte eepromData;      //1 byte data storage
    
    //Reading 1 byte of data from EEPROM chip and store that value in eepromData. Here (i) represents the location address.
    rom.Read(i, &eepromData); 
    
    //-----------------------------------------------------------------------------------------------------------------
    Serial.print (i);                  //Printing Location address
    Serial.print(F("\t\t"));
    Serial.println(eepromData,HEX);    //Printing value (in HEX format) which we get from eeprom.
  }
  Serial.println(F("Reading Done."));
}

void Writing_operation() // WRITING SUB-ROUTINE 
{
  Serial.println(F("Address \t Old Value \t New Value"));
  Serial.println(F("====================================================="));
  
  for(int i=2040; i<EEPROM_SIZE; i++) // Loop for reading/writing data from/to 2040-2047 possible addresses. Valid addressing range: 0-2047
  {
    byte old_value, new_value, verified_value; // storage variables
    
    rom.Read(i,&old_value);       // Reading previously stored value from (i) address.
    new_value = 0xAA;             // New value.
    rom.Write(i,new_value);       // Writing 1 byte of data into EEPROM chip. Here (i) represents target location address.
    rom.Read(i,&verified_value);  // Reading (verifying) newly written value from (i) address.
    
    Serial.print (i);             // Printing Location address
    Serial.print(F("\t\t"));
    Serial.print(old_value,HEX);  // Printing old value (in HEX format) which we get from eeprom.
    Serial.print(F("\t\t"));
    Serial.println(verified_value,HEX); // Printing (verifying) newly written value from (i) address.
  }
  Serial.println(F("Writing Done"));
}
