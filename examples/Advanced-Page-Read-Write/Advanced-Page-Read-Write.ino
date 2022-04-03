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
 *  In this tutorial, we will show you advanced Page read write operation.
 *  
 */

#include <AT24C16.h>

AT24C16 rom;          // Initializing AT24C16 Library with the object named rom. Default slave id = 0x50

void setup() 
{
  Serial.begin(2000000); // Initializing Serial at 2000000 bps.
  Wire.begin();       // Initializing I2C protocol (Master Mode)
 
  // READING PAGE OPERATION-----------------------------------------------------------------------------------------------------------
  Serial.println(F("Reading previously stored values from EEPROM chip from address 0 to 15 ...."));
  delay(2000);              // 2 seconds delay
  Serial.println();
  Reading_page_operation(); // EXECUTING READING SUB-ROUTINE 
  delay(2000);              // 2 seconds delay
  
  // WRITING PAGE OPERATION-----------------------------------------------------------------------------------------------------------
  Serial.println(F("Writing 0xA1-0xB0 into EEPROM chip from address 0 to 15 ...."));
  delay(2000);              // 2 seconds delay
  Serial.println();
  
  byte buffer_old[ROM_PAGE_SIZE];     // Storage for previously stored values. Page size is 16 bytes each.
  byte buffer_new[ROM_PAGE_SIZE];     // Storage for new values
  byte buffer_verify[ROM_PAGE_SIZE];  // Storage for verification purpose

  // Generating values (0xA1-0xB0) for buffer_new array
  for(int i=0;i<ROM_PAGE_SIZE;i++)
  {
    buffer_new[i]= i + 0xA1;
  }
  
  rom.readPage(0, buffer_old);    // Reading saved values
  rom.writePage(0,buffer_new);    // Writing new values
  rom.readPage(0, buffer_verify); // Reading again for verification
  print_result(0,ROM_PAGE_SIZE, buffer_old, buffer_verify, 1); // Printing result
  
  // VERIFICATION (READING PAGE OPERATION) -------------------------------------------------------------------------------------------
  Serial.println(F("Verifying...."));
  delay(2000);              // 2 seconds delay
  Serial.println();
  Reading_page_operation(); // EXECUTING READING SUB-ROUTINE 
  Serial.println();
  Serial.println(F("All Done"));
}

void loop()
{
  // Nothing Here
}

void print_result(int address, byte length, byte *data0, byte *data1, bool type) // Result print subroutine
{
  switch(type)
  {
    case 0: Serial.println(F("Address \t Value"));
            Serial.println(F("====================================================="));
            for(int i=0; i<length; i++)
            {
              Serial.print(i+address);
              Serial.print(F("\t\t"));
              Serial.println(data0[i],HEX);
            }
            break;
            
    case 1: Serial.println(F("Address \t Old Value \t New Value"));
            Serial.println(F("====================================================="));
            for(int i=0; i<length; i++)
            {
              Serial.print(i+address);
              Serial.print(F("\t\t"));
              Serial.print(data0[i],HEX);
              Serial.print(F("\t\t"));
              Serial.println(data1[i],HEX);
            }
            break;       
  }
  Serial.println(F("Done"));
}

void Reading_page_operation() // READING SUB-ROUTINE
{
  byte buffer[ROM_PAGE_SIZE]; // Buffer for storing values
  rom.readPage(0, buffer);    // Reading page. Address 0 to 15 [16 bytes].
  print_result(0,ROM_PAGE_SIZE, buffer, buffer, 0); // Printing result
}
