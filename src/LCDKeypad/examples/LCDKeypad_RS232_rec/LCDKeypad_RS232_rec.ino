/*
 * Exemplo de uso da biblioteca LCD e Keypad. 
 * 
 * Descricao: Exemplo de uso das rotina locais, isto é, o display
 *   eh ligado ao arduino diretamente.
 */
#include <Keypad.h>
#include <LCD.h>
#include <LCDKeypad_FIFO.h>
#include <LCDKeypadInterface.h>

Keypad keypad;
LCD lcd(8, 9, 4, 5, 6, 7);

int localKey = 0;
//const char LCD_COMMAND = 27; //Valor que sinaliza comando para o LCD
//const char KEYPAD_READ = 10; //Valor que sinaliza comando de leitura de buffer do teclado
//const char KEYPAD_BUFFER_SIZE = 4; //Tamanho do buffer do teclado
myFIFO<int,KEYPAD_BUFFER_SIZE> keypadBuffer;
//const char SERIAL_TIMEOUT_MS = 100; //Timeout para recepcao na serial
                 
void setup() 
{ 
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("LCD Keypad");
  lcd.setCursor(0,1);
  lcd.print("Serial receiver");

  // Configura serial
  Serial.begin(9600);
  //Clean buffer
  keypadBuffer.flush();
}

void loop() 
{ 
  //Atende serial
  if (Serial.available())
  {
    char inByte = Serial.read();
    switch (inByte) {
    case LCD_COMMAND: 
      //Recebeu commando. Aguardo proximo byte
      
      if (waitSerial(SERIAL_TIMEOUT_MS))
      {
        char command = Serial.read();
        lcd.command(command);
      }
      break;
    case KEYPAD_READ:
      //Envia todo buffer
      for (int i=0; i < KEYPAD_BUFFER_SIZE; i++)
      {
        if (keypadBuffer.count() != 0)
        {
          Serial.write(keypadBuffer.dequeue());
        } else
        {
          Serial.write(NO_KEY);
        }
      }
      break;
    default:
      lcd.print(inByte);
      break;
    }
  }

  //Atende teclado
  localKey = keypad.getKey();
  if (localKey != 0)
  {
    if (keypadBuffer.count() >= KEYPAD_BUFFER_SIZE)
    {
      //Buffer esta cheio, elimina elemento
      keypadBuffer.dequeue();
    }
    keypadBuffer.enqueue(localKey);
  }
}


/*Espera resposta da serial. Retorna true se algum dado esta diponivel dentro
 *   do timeout. Caso nada seja reccebido retorna false depois do periodo de timeout
 */
bool waitSerial(int timeout)
{
  long unsigned endStamp = millis() + timeout;
  do
  {
    if (Serial.available())
    {
      return true;
    } 
  } while (millis() <= endStamp);
  return false; 
}

