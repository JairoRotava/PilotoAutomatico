/*
 * TODO: fazer arquivo .h com as constantes utilizadas nos dois pedacoes de software
 * 
 * isolar parte de hardware para por utilizar rs232, rs485, i2c e spi alterando somente
 * as funçoes de hardware
 * 
 * Organizar  codigo
 * 
 * TEntar usar mesmos nomes de funcoes de controle local e remoto
 * 
 */
 
#include <LCDKeypad_RS232.h>

LCDKeypad_RS232 lcd;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2,9600);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.print("LCDKeypad Serial");
  lcd.setCursor(0,1);
  lcd.print("Exemplo");
  delay(2000);
  lcd.clear();
  lcd.print("Cursor vai");
  lcd.setCursor(15,1);
  lcd.rightToLeft();
  lcd.print("Cursor volta");
  lcd.leftToRight();
  delay(2000); 
  lcd.clear();
  lcd.print("Lendo teclado:");
  lcd.cursor();
  lcd.blink();
  lcd.setCursor(0,1);

  for(;;)
  {
    int key = lcd.getKey();
    while (key != NO_KEY)
    {
      lcd.print(key); 
      key = lcd.getKey();
    } 

    //Simula outros processamentos
    delay(300); 
  }
}
