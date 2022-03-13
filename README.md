# AT24C16 _ver. 2.0_
Library for Interfacing with AT24C16 EEPROM chip in the Arduino environment.

**_What's new in Version 2.0:._** 
* Byte read/write operation
* Page read/write operation
* Store/retrieve integer, long, float, double, String to/from EEPROM 
* Efficient Erase operation
* Builtin Memorymap function


# _Byte read/write operation_
Reading/writing 1 byte of data at a time.
## Reading: 
### Read(uint16_t address, uint8_t* data);
**Address:** Target EEPROM address. _Valid address location: 0-2047_.

**Data:** Received value storage pointer.

**Returns** nothing.



## Writing: 
### Write(uint16_t address, uint8_t data);
**Address:** Target EEPROM address. _Valid address location: 0-2047_.

**Data:** 1 byte of data which will be written into EEPROM.

**Returns** nothing.









# _Page read/write operation_
Reading/writing 16 bytes of data at a time.
## Reading: 
### readPage(unsigned address, uint8_t* buffer);
**Address:** Target EEPROM address. _Page address interval: 16_.

**Buffer:** Received value storage pointer.  _16 bytes array_.

**Returns** nothing.



## Writing: 
### writePage(unsigned address, uint8_t* data);
**Address:** Target EEPROM address. _Page address interval: 16_.

**Data:** 16 bytes of data which will be written into EEPROM.

**Returns** nothing.





# _Dealing with datatypes_
Read/write integer, long, float, double, string variable in EEPROM.

## Integer: 
### readInt(unsigned address, int* data);
**Address:** Target EEPROM address. _Valid address location: 0-2046_.

**Data:** Received integer value storage pointer.

**Returns** nothing.



### writeInt(unsigned address, int value);
**Address:** Target EEPROM address. _Valid address location: 0-2046_.

**Data:** integer value which will be written into EEPROM.

**Returns** nothing.



## Long: 
### readLong(unsigned address, long* data);
**Address:** Target EEPROM address. _Valid address location: 0-2044_.

**Data:** Received long value storage pointer.

**Returns** nothing.



### writeLong(unsigned address, long value);
**Address:** Target EEPROM address. _Valid address location: 0-2044_.

**value:** long value which will be written into EEPROM.

**Returns** nothing.




## Float: 
### readFloat(unsigned address, long* data);
**Address:** Target EEPROM address. _Valid address location: 0-2044_.

**Data:** Received Float value storage pointer.

**Returns** nothing.



### writeFloat(unsigned address, long value);
**Address:** Target EEPROM address. _Valid address location: 0-2044_.

**value:** Float value which will be written into EEPROM.

**Returns** nothing.




## Double: 
### readDouble(unsigned address, long* data);
**Address:** Target EEPROM address. _Valid address location: 0-2044_.

**Data:** Received Double value storage pointer.

**Returns** nothing.



### writeDouble(unsigned address, long value);
**Address:** Target EEPROM address. _Valid address location: 0-2044_.

**value:** Double value which will be written into EEPROM.

**Returns** nothing.



## String: 
### readStr(unsigned address, String* data, int len);
**Address:** Target EEPROM address. _Valid address location: 0-2047_.

**Data:** Received string data storage pointer.

**len:** String length

**Returns** nothing.



### writeStr(unsigned address, String val);
**Address:** Target EEPROM address. _Valid address location: 0-2047_.

**value:** String type data which will be written into EEPROM.

**Returns** nothing.







# _Erase Opearation:_ 
### Erase(uint16_t *execution_time, uint8_t *erase_count, bool *status);

**execution_time:** Pointer storage for erase operation execution time in ms.

**erase_count:** Pointer storage for erased page count.

**status** Pointer storage for erase status. _TRUE = OK, FALSE = Failed_.

**Returns** nothing.




### Erase();

Simplified Erase function.

**Returns** 1 byte of boolean status value.  _TRUE = OK, FALSE = Failed_.



# _Accessing EEPROM information_

## Get EEPROM info: 
### getInfo(uint16_t* rom_size, uint8_t* page_size, uint8_t* totalPage, String* model);
**rom_size:** Pointer storage. Returns EEPROM size.

**page_size:** Pointer storage. Returns EEPROM page size in bytes.

**totalPage:** Pointer storage. Returns EEPROM total page count.

**model:** Pointer storage. Returns EEPROM model/part number.

**Returns** nothing.




### getInfo();

Simplified getInfo function. Print rom size, page size, total number of pages, model, used/free space info in serial monitor.

**Returns** nothing.




### Memorymap();

Map entire EEPROM memory in serial monitor.

**Returns** nothing.
