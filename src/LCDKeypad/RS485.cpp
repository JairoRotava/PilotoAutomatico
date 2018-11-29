#include "RS485.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

RS485::RS485()
{
	
}

void RS485::begin(int baudrate, int txenpin , int rxenpin)
{
	_txenpin = txenpin;
	_rxenpin = rxenpin;
	
  Serial.begin(baudrate);
  off();
  pinMode(rxenpin,OUTPUT);
  pinMode(txenpin,OUTPUT);
}




size_t RS485::write(uint8_t value)
{
	Serial.write(value);
	return 1;
}

void RS485::receive()
{
  //Aguarda buffer de transmissao esvaziar, caso contrario 
  //vai cortar transmissao
  Serial.flush();
  digitalWrite(_txenpin, RS485_DE_OFF);  
  digitalWrite(_rxenpin, RS485_RE_ON);
}

void RS485::transmit()
{
  digitalWrite(_rxenpin, RS485_RE_OFF);
  digitalWrite(_txenpin, RS485_DE_ON);    
}


void RS485::off()
{
  digitalWrite(_rxenpin, RS485_RE_OFF);
  digitalWrite(_txenpin, RS485_DE_OFF);    
}

int RS485::read()
{
	return Serial.read();
}

int RS485::available()
{
	return Serial.available();
}
