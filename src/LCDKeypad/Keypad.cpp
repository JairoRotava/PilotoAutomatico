/*
  LCDKeypad.cpp
*/
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


// include this library's description file

#include "Keypad.h"

void Keypad::setKeyWaitToRepeat(unsigned long value)
{
	waitToRepeat= value;
}

void Keypad::setKeyRepeatPeriod(unsigned long value)
{
	repeatKeyPeriod = value;
}

Keypad::Keypad()
{
  _refreshRate = REFRESH_RATE;
  _keyPin = DEFAULT_KEY_PIN;
  _threshold = DEFAULT_THRESHOLD;
  _curInput = NO_KEY;
  _curKey = NO_KEY;
  _prevKey = NO_KEY;
  _oldTime = 0; 
  waitToRepeat = WAIT_TO_REPEAT;
  repeatKeyPeriod = REPEAT_PERIOD;

}

//Return pressed key
int Keypad::readKey()
{
  return _curKey;
}

//returns pressed key and take care of repetition
int Keypad::getKey()
{
 if (millis() > _oldTime + _refreshRate)
  {
    _oldTime = millis();
	_prevKey = _curKey;
	_curKey = NO_KEY;
	
	/* Rotina para captura de tecla analogica
    _curInput = analogRead(_keyPin);
    //Identifica tecla
    if (_curInput > UPKEY_ARV - _threshold && _curInput < UPKEY_ARV + _threshold ) _curKey = UP_KEY;
    else if (_curInput > DOWNKEY_ARV - _threshold && _curInput < DOWNKEY_ARV + _threshold ) _curKey = DOWN_KEY;
    else if (_curInput > RIGHTKEY_ARV - _threshold && _curInput < RIGHTKEY_ARV + _threshold ) _curKey = RIGHT_KEY;
    else if (_curInput > LEFTKEY_ARV - _threshold && _curInput < LEFTKEY_ARV + _threshold ) _curKey = LEFT_KEY;
    else if (_curInput > SELKEY_ARV - _threshold && _curInput < SELKEY_ARV + _threshold ) _curKey = SELECT_KEY;
    else _curKey = NO_KEY;
	*/
	/* Rotina para leitura de tecla. 
	TODO: Precisa isolar melhor isso aqui*/
	pinMode(4,OUTPUT);
	pinMode(5,OUTPUT);
	pinMode(A0,INPUT_PULLUP);
	pinMode(A1,INPUT_PULLUP);
	pinMode(A2,INPUT_PULLUP);
	digitalWrite(4,LOW);
	digitalWrite(5,HIGH);
	if (digitalRead(A0) == 0) _curKey = DOWN_KEY;
	if (digitalRead(A1) == 0) _curKey = LEFT_KEY;
	digitalWrite(4,HIGH);
	digitalWrite(5,LOW);	
	if (digitalRead(A0) == 0) _curKey = SELECT_KEY;
	if (digitalRead(A1) == 0) _curKey = RIGHT_KEY;
	if (digitalRead(A2) == 0) _curKey = UP_KEY;
	
	
	

    //If it is a new key send the key
    if (_prevKey != _curKey)
    {
      _waitRepeat = _oldTime + waitToRepeat;
      _repeatKey = _oldTime + repeatKeyPeriod;
      return _curKey;
    }
    
   //It is the same key as before. If it is different of nokey, repeat
   if (_curKey != NO_KEY)
    {
      //Repeat key
      if (_oldTime >= _waitRepeat)
      {
        if (_oldTime >= _repeatKey)
        {
          _repeatKey = _oldTime + repeatKeyPeriod;
          return _curKey;
        }
      }
    }      
  }
  // If got so far return no key
  return NO_KEY;
}

