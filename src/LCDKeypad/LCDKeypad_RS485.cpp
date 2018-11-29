/*
 LCDKeypad_RS485.cpp - Library for controlling a SparkFun LCDKeypad_RS485
              module.
	      Code written for firmware version 2.5

 Created by Cody B. Null, September 9, 2011
 Modified by Jordan Hochenbaum, Dec 5, 2011. (Version 1.5)
 Modified by Johan Korten, March 23, 2013. (Version 1.6)
 Modified by Florentin Salomez, June 18, 2016 (Version 1.7)


 Version 1.4 - This version wrote specifically for 16x2
               Display.
               More display support coming in later version.

 Version 1.5 - Since mid 2011 the Arduino IDE has implemented the NewSoftSerial 
                library updates in the standard SoftwareSerial library and so 
                using NewSoftSerial is no longer needed. LCDKeypad_RS485 has been updated 
                to use the Standard SoftwareSerial library. Also, Arduino 1.0
                support has been added. Backwards compatible with previous versions.

 Version 1.6 - Added support for the setType special command.
				This will help using different LCD's (2x16, 2x20, 4x16, 4x20).  
		      Added support for scrollLeft and scrollRight commands.

Version 1.7 - Completed the setType special command. 
 				Now the setCursor function works correctly.
 				Added keywords.txt and library.properties file.

 Note -	This library requires NewSoftSerial library
 The latest version of NewSoftSerial library can 
 always be found at http://arduiniana.org. -> NO LONGER NECESSARY. See V1.5 notes above
*/

#include "LCDKeypad_RS485.h"
#include "RS485.h"

LCDKeypad_RS485::LCDKeypad_RS485()
{
	
}


void LCDKeypad_RS485::begin(uint8_t cols, uint8_t rows,uint16_t baudrate)
{
	//Serial.begin(baudrate);
	rs485.begin(baudrate,RS485_DE_PIN,RS485_RE_PIN);
	rs485.receive();
	LCD::begin(cols,rows);
	keypadBuffer.flush();
}

void LCDKeypad_RS485::command(uint8_t value) {
	//Serial.write(LCD_COMMAND);
	rs485.transmit();
	rs485.write(LCD_COMMAND);
	//Serial.write(value);
	rs485.write(value);
	//Makes sure command in sent out of buffer to avoid timing issues
	//Serial.flush();
	rs485.receive();
}

size_t LCDKeypad_RS485::write(uint8_t value) {
	rs485.transmit();
	rs485.write(value);
  return 1; // assume sucess
}

uint8_t LCDKeypad_RS485::getKey()
{
  //Se buffer estiver vazio pede novo
  if (keypadBuffer.count() == 0)
  {
    //Buffer esta vazio, pede dados
	rs485.transmit();
    rs485.write(KEYPAD_READ);
	rs485.receive();
    //Recebe buffer
          //Clean local buffer
    keypadBuffer.flush();
    for (int i=0; i < KEYPAD_BUFFER_SIZE; i++)
    {
      /*
      while (!Serial.available());
      int val = Serial.read();
      if (val != NO_KEY)
      {
        keypadBuffer.enqueue(val);
      } 
      */
      if (waitSerial(SERIAL_TIMEOUT_MS))
      {
        int val = rs485.read();
        if (val != NO_KEY)
        {
          keypadBuffer.enqueue(val);
        }         
      }
    }
  }
  if (keypadBuffer.count() != 0)
  {
    int key = keypadBuffer.dequeue();
    return key;    
  }
  return 0;
}

uint8_t LCDKeypad_RS485::waitSerial(int timeout)
{
  long unsigned endStamp = millis() + timeout;
  do
  {
    if (rs485.available())
    {
      return true;
    } 
  } while (millis() <= endStamp);
  return false; 
}
