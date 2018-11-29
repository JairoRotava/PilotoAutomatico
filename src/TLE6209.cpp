#include <Arduino.h>
#include <SPI.h>
#include "TLE6209.h"

//Seta em modo DEBUG
//#define DEBUG 1
#define debugSerial Serial 

//Configuracao SPI TLE6290
SPISettings TLE6209SPISettings(1000000, LSBFIRST, SPI_MODE1);

uint8_t TLE6209_config(uint8_t controlBits)
{
    //Envia SPI e recebe status  
    SPI.beginTransaction(TLE6209SPISettings);
    digitalWrite(TLE6209_SPI_CHIP_SELECT_PIN, LOW);  
    byte status = SPI.transfer(controlBits);
    digitalWrite(TLE6209_SPI_CHIP_SELECT_PIN, HIGH);  
    SPI.endTransaction();

    #ifdef DEBUG
    debugSerial.print(F("DEBUG-TLE6209 STATUS: 0x"));
    debugSerial.print(status,HEX);
    if (status & POWER_SUPPLY_FAIL) {Serial.print(F(" POWER_SUPPLY_FAIL"));}
    if (status & ALWAYS_H) {Serial.print(F(" ALWAYS_H"));}
    if (status & SHORT_VS) {Serial.print(F(" SHORT_VS"));}
    if (status & SHORT_GND) {Serial.print(F(" SHORT_GND"));}
    if (status & OPEN_LOAD) {Serial.print(F(" OPEN_LOAD"));}
    if (status & ERROR_FLAG) {Serial.print(F(" ERROR FLAG"));}
    if (status & TEMP_PRE_WARN) {Serial.print(F(" TEMP_PRE_WARN"));}
    if (status & TEMP_WARNING) {Serial.print(F(" TEMP_WARNING"));}
    Serial.println();
    #endif
    return(status);
}

void TLE6209_reset()
{
  digitalWrite(TLE6209_ENABLE_PIN, LOW);
  delay(10);
  digitalWrite(TLE6209_ENABLE_PIN, HIGH);
}

/*
 * Inicia rotinas da borboleta
 */
void TLE6209_init()
{
  digitalWrite(TLE6209_SPI_CHIP_SELECT_PIN, HIGH);
  pinMode(TLE6209_SPI_CHIP_SELECT_PIN,OUTPUT);
  digitalWrite(TLE6209_DIRECTION_PIN, LOW);		//Pino de controle direcao
  pinMode(TLE6209_DIRECTION_PIN,OUTPUT);
  digitalWrite(TLE6209_ENABLE_PIN, LOW);	    //Pino habilita driver
  pinMode(TLE6209_ENABLE_PIN,OUTPUT);
  analogWrite(TLE6209_PWM_PIN, 0);
  pinMode(TLE6209_PWM_PIN, OUTPUT);           //Sinal PWM
}

void TLE6209_on()
{
    digitalWrite(TLE6209_ENABLE_PIN, HIGH);	    //Pino habilita driver
}

void TLE6209_off()
{
    digitalWrite(TLE6209_ENABLE_PIN, LOW);	    //Pino habilita driver
}

void TLE6209_out(int16_t value)
{
  if (value < 0) {
	  digitalWrite(4, HIGH);
	  value = - value;
	  } else {
	  digitalWrite(4, LOW);
  }  
  analogWrite(TLE6209_PWM_PIN, value);
}
