/* ==================================================================================
 *                           I2C EXTERNAL EEPROM LIBRARY Example
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
 *  In this tutorial, we will show you the erase operation.
 */


#include <AT24C16.h>

AT24C16 rom;          // Initializing AT24C16 Library with the object named rom. Default slave id = 0x50

void setup() 
{
  Serial.begin(9600); //Initializing Serial at 9600 bps.
  Wire.begin();       //Initializing I2C protocol (Master Mode)

  Serial.println("Reading previously stored values from EEPROM chip....");
  delay(1000);
  
  readOperation();  //Reading previously stored values
  
  delay(2000);    //2 seconds delay
  
  Serial.println("Erase operation Started.");
  //-------------------------------------------------------------------------
  rom.Erase();    //EEPROM Erase function. It will erase entire EEPROM chip.
  //-------------------------------------------------------------------------
  
  Serial.println("Erase done.");

  delay(2000);    //2 seconds delay

  Serial.println("Reading new values from EEPROM chip....");

  delay(1000);    //1 second delay
  
  readOperation();//Reading new values. Value = 0xFF or 255 means erased successfully.
  
  Serial.println("All Done");
}

void loop()
{
  //Nothing Here
}


void readOperation() //Reading operation handler
{
  Serial.println("\nAddress \t Value");
  Serial.println("=====================================================");

  for(int i=0; i<EEPROM_SIZE; i++) //Loop for reading data from all possible addresses. Valid addressing range: 0-2047
  {
    //-----------------------------------------------------------------------------------------------------------------
    byte eepromData = rom.Read(i); //Reading 1 byte of data from EEPROM chip. Here (i) represents the location address.
    //-----------------------------------------------------------------------------------------------------------------
    Serial.print (i);              //Printing Location address in serial monitor
    Serial.print("\t\t");
    Serial.println(eepromData,HEX);    //Printing value which we get from eeprom. (Value represents in Hex format).
  }
  Serial.println("Reading done.");
}
