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
 
#include <LCDKeypad_RS485.h>
LCDKeypad_RS485 lcdKeypad;

void setup() {
  // put your setup code here, to run once:
  lcdKeypad.begin(16,2,9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 // lcdKeypad.transmit();
  lcdKeypad.print("LCDKeypad RS485");
  lcdKeypad.setCursor(0,1);
  lcdKeypad.print("Exemplo");
  delay(2000);
  lcdKeypad.clear();
  lcdKeypad.print("Cursor vai");
  lcdKeypad.setCursor(15,1);
  lcdKeypad.rightToLeft();
  lcdKeypad.print("Cursor volta");
  lcdKeypad.leftToRight();
  delay(2000); 
  lcdKeypad.clear();
  lcdKeypad.print("Lendo teclado:");
  lcdKeypad.cursor();
  lcdKeypad.blink();
  lcdKeypad.setCursor(0,1);

  for(;;)
  {
    int key = lcdKeypad.getKey();
    while (key != NO_KEY)
    {
      lcdKeypad.print(key); 
      key = lcdKeypad.getKey();
    } 

    //Simula outros processamentos
    delay(300); 
  }
  
}
