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
 *  In this tutorial, we will show you the method of storing integer, float, String values in EEPROM.
 */


#include <AT24C16.h>

AT24C16 rom;          // Initializing AT24C16 Library with the object named rom. Default slave id = 0x50

unsigned int address;

void setup() 
{
  Serial.begin(115200); //Initializing Serial at 115200 bps.
  Wire.begin();       //Initializing I2C protocol (Master Mode)
  demo();
}

void loop()
{
  //Nothing Here
}

void demo() //The Demo subrouting
{
  Serial.println(F("\nPresent EEPROM status:"));
  rom.getInfo();
  delay(2000);
  Serial.println(F("\nTest starting....\n"));
  delay(1000);
  
  demo_int();     //Integer operation Demo
  delay(1000);
  demo_long();    //Long operation Demo
  delay(1000);
  demo_float();   //Float operation Demo
  delay(1000);
  demo_double();  //Double operation Demo
  delay(1000);
  demo_string();  //String operation Demo
  delay(1000);
  
  Serial.println(F("\nPresent EEPROM status:"));
  rom.getInfo();
  Serial.println(F("\nAll done\n=================================================="));
}

void demo_int()
{
  int x,y,z;
  address = 10;
  Serial.print(F("\n\nInteger test from address "));
  Serial.print(address);
  Serial.println(F(" .......\n"));
  partial_mapping(0);
  rom.readInt(address, &x); // Reading an integer value from target address
  y=5000;
  rom.writeInt(address, y); // Writing 5000 as integer totarget address
  rom.readInt(address, &z);  // Reading again target address for verification.

  print_result(String(x),String(y),String(z)); // Printing result
}

void demo_long()
{
  long x,y,z;
  address = 20;
  Serial.print(F("\n\nLong test from address "));
  Serial.print(address);
  Serial.println(F(" .......\n"));
  partial_mapping(0);
  rom.readLong(address, &x);  // Reading a long value from target address
  y=90000;
  rom.writeLong(address, y);  // Writing 90000 as long to target address
  rom.readLong(address, &z);  // Reading again target address for verification.
  
  print_result(String(x),String(y),String(z)); // Printing result
}

void demo_float()
{
  float x,y,z;
  address = 30;
  Serial.print(F("\n\nFloat test from address "));
  Serial.print(address);
  Serial.println(F(" .......\n"));
  partial_mapping(0);
  rom.readFloat(address, &x); // Reading a float value from target address
  y=PI;
  rom.writeFloat(address, y); // Writing the value of PI as float to target address
  rom.readFloat(address, &z); // Reading again target address for verification.
  
  print_result(String(x,7),String(y,7),String(z,7)); // Printing result
}

void demo_double()
{
  double x,y,z;
  address = 40;
  Serial.print(F("\n\nDouble test from address "));
  Serial.print(address);
  Serial.println(F(" .......\n"));
  partial_mapping(0);
  rom.readDouble(address, &x);  // Reading a double value from target address
  y=PI*PI;
  rom.writeDouble(address, y);  // Writing the value of PI * PI as double to target address
  rom.readDouble(address, &z);  // Reading again target address for verification.
  
  print_result(String(x,7),String(y,7),String(z,7)); // Printing result
}

void demo_string()
{
  String x,y,z;
  address = 50;
  const int length = 10;
  Serial.print(F("\n\nString test from address "));
  Serial.print(address);
  Serial.println(F(" .......\n"));
  partial_mapping(0);
  rom.readStr(address, &x,length); // Reading previous value as string.
  y="I Love You";
  rom.writeStr(address, y);        // Writing new value as string.
  rom.readStr(address, &z,length); // Read again for verification.
  
  print_result(String(x),String(y),String(z)); // Printing result
}

void print_result(String x, String y, String z) //Result printing subroutine
{
  partial_mapping(1);
  Serial.print(F("\nRead\t: "));
  Serial.println(x);
  Serial.print(F("Write\t: "));
  Serial.println(y);
  Serial.print(F("Verify\t: "));
  Serial.println(z);
  Serial.println(F("Done\n--------------------------------------------"));
}

void partial_mapping(bool type) // Memory map subroutine
{
  switch(type)
  {
    case 0: Serial.print(F("Showing address (Old): "));break;
    case 1: Serial.print(F("Showing address (New): "));break;
  }
  Serial.print(address);
  Serial.print(F("-"));
  Serial.print(address+15);
  Serial.print(F(" --> "));
  byte buffer[16];
  rom.readPage(address-2,buffer);
  for(int i=address; i<address+16;i++)
  {
    String a= String(buffer[i],HEX);
    a.toUpperCase();
    if(a.length()==1)
    {
      a= "0" + a;
    }
    Serial.print(a);
    Serial.print(F(" "));
  }
  Serial.println();
}
