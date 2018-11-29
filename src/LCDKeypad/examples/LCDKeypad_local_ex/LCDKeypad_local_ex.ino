/*
 * Exemplo de uso da biblioteca LCD e Keypad. 
 * 
 * Descricao: Exemplo de uso das rotina locais, isto é, o display
 *   eh ligado ao arduino diretamente.
 */
#include <Keypad.h>
#include <LCD.h>

Keypad keypad;
LCD lcd(8, 9, 4, 5, 6, 7);


int localKey = 0;
                 
void setup() 
{ 
  lcd.begin(16, 2);
  keypad.setKeyWaitToRepeat(1000);
  keypad.setKeyRepeatPeriod(100);
  lcd.clear();
  lcd.print("LCD Keypad");
  delay(2500);
  lcd.clear();
  lcd.print("Press keys:");
  lcd.setCursor(0,1);
}

void loop() 
{ 
  
  localKey = keypad.getKey();
  if (localKey != 0)
  {
    lcd.print(localKey);
  }
}
