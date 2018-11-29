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

#include "LCDKeypad_SPI.h"


//#define DUMMY 254	//Caracter Dummy para utilizar com SPI e ignorado pelo display

/*
#define SPI_DELAY_MICRO_SECONDS 300
#define SPI_CLOCK 1000000
#define SPI_BIT_ORDER	MSBFIRST
#define SPI_MODE		SPI_MODE0*/
SPISettings settingsLCDKeypad(SPI_CLOCK, SPI_BIT_ORDER, SPI_MODE);


LCDKeypad_SPI::LCDKeypad_SPI()
{
}


void LCDKeypad_SPI::begin(uint8_t cols, uint8_t rows)
{
	pinMode(SS, OUTPUT);
	//pinMode(MISO, INPUT);
	SPI.begin ();
	LCD::begin(cols,rows);
	keypadBuffer.flush();
}

void LCDKeypad_SPI::command(uint8_t value) {
    SPI.beginTransaction(settingsLCDKeypad);
	digitalWrite(SS, LOW);    // SS is pin 10
    SPI.transfer (LCD_COMMAND);
	delayMicroseconds(SPI_DELAY_MICRO_SECONDS);	  
	SPI.transfer(value);
	delayMicroseconds(SPI_DELAY_MICRO_SECONDS);	  
    digitalWrite(SS, HIGH);    // SS is pin 10
	SPI.endTransaction();
}

size_t LCDKeypad_SPI::write(uint8_t value) {
    SPI.beginTransaction(settingsLCDKeypad);
	digitalWrite(SS, LOW);      // SS is pin 10
	SPI.transfer(value);
	delayMicroseconds(SPI_DELAY_MICRO_SECONDS);	  
    digitalWrite(SS, HIGH);    // SS is pin 10	
	SPI.endTransaction();

  return 1; // assume sucess
}

uint8_t LCDKeypad_SPI::getKey()
{
   SPI.beginTransaction(settingsLCDKeypad);

  //Se buffer estiver vazio pede novo
  if (keypadBuffer.count() == 0)
  {
    //Buffer esta vazio, pede dados
	digitalWrite(SS, LOW);    // SS is pin 10

	//Sincroniza com teclado. Se ele nao responder ACK ele esta ocupado fazendo outra coisa.
	byte val = SPI.transfer(SPI_DUMMY);
	while (val != SPI_DUMMY_ACK)
	{
		delay(GET_KEY_SYNC_DELAY);
		val = SPI.transfer(SPI_DUMMY);
	} 
	
	
	SPI.transfer(KEYPAD_READ);
    //Clean local buffer
    keypadBuffer.flush();
	
    //Recebe buffer	
    for (int i=0; i < KEYPAD_BUFFER_SIZE; i++)
    {
		//Delay para teclado preencher buffer. 
		//delay(1);	
		delayMicroseconds(SPI_DELAY_MICRO_SECONDS);
		byte val = SPI.transfer(SPI_DUMMY);
		if (val == KEYPAD_READ )
		{
			//Se resposta for mesmo que comando significa que painel pode estar ocupado.
			//Aguarda um tempo e tenta novamente
			delay(GET_KEY_SYNC_DELAY);
			val = SPI.transfer(SPI_DUMMY);
		}
		if ((val != NO_KEY) && (val != SPI_DUMMY) && (val != KEYPAD_READ))
		{
		  keypadBuffer.enqueue(val);
		}       
    }	
  }

  digitalWrite(SS, HIGH);    // SS is pin 10	
  SPI.endTransaction();

  if (keypadBuffer.count() != 0)
  {
    int key = keypadBuffer.dequeue();
    return key;    
  }
  return 0;
}
