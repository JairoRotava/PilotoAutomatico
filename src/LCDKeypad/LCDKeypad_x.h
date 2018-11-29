/*
 serLCD.h - Library for controlling a SparkFun serLCD module
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
               using NewSoftSerial is no longer needed. serLCD has been updated 
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
        always be found at http://arduiniana.org. -> NO LONGER NECESSARY. See 1.5 notes above.-Jordan Hochenbaum
*/
#ifndef serLCD_h
#define serLCD_h

#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds,digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif
//#include "SoftwareSerial.h"
#include "LCD.h"
#include "LCDKeypad_FIFO.h"



//Code for LCD_COMMAND
#define LCD_COMMAND     0x1B     

//Comando para ler buffer do teclado
const char KEYPAD_READ = 10;
const char KEYPAD_BUFFER_SIZE = 4;
const char SERIAL_TIMEOUT_MS = 100;

enum keypad {NO_KEY = 0,SELECT_KEY, LEFT_KEY,  UP_KEY, DOWN_KEY, RIGHT_KEY };



class serLCD : public LCD {
	public:
	serLCD();
	void begin(uint8_t cols, uint8_t rows,uint16_t baudrate);
	virtual size_t write(uint8_t);
	void command(uint8_t);
	myFIFO<int,KEYPAD_BUFFER_SIZE> keypadBuffer;
	uint8_t getKey();
	private:
	uint8_t waitSerial(int timeout);
};

#endif
