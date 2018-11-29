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
myFIFO<int,KEYPAD_BUFFER_SIZE> keypadBuffer;

const char SPI_BUFFER_SIZE = 24;
myFIFO<volatile char,SPI_BUFFER_SIZE> SPIBuffer;  //SPI buffer input. Volatile pq é atualizado da interrupcao
const char SPI_TIMEOUT_MS = 100; //Timeout para recepcao na SPI
                 
void setup() 
{ 
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("LCD Keypad");
  lcd.setCursor(0,1);
  lcd.print("SPI");
  
  keypad.setKeyWaitToRepeat(1000);
  keypad.setKeyRepeatPeriod(50);

  //Clean buffer
  keypadBuffer.flush();

  //Setup SPI
  SPIBuffer.flush();        //Clean buffer
  pinMode(MISO, OUTPUT);   // have to send on master in, *slave out*
  SPCR |= _BV(SPE);         // turn on SPI in slave mode
  SPCR |= _BV(SPIE);          // turn on interrupts
  }

void loop() 
{ 
  cli();
  int c = SPIBuffer.count();  //Verifica se tem algo no buffer. Desliga interrupcoes para evitar possivel race condition
  sei();
  if (c)
  {
    cli();
    char inByte = SPIBuffer.dequeue();
    sei();
    switch (inByte) {
    case LCD_COMMAND: 
      //Recebeu commando. Aguardo proximo byte      
      if (waitSPI(SPI_TIMEOUT_MS))
      {
        cli();
        char command = SPIBuffer.dequeue();
        sei();
        lcd.command(command);
      }
      break;
    case KEYPAD_READ:
    //Recebeu comando de teclado
      for (int i=0; i < KEYPAD_BUFFER_SIZE; i++)
      {
        if (keypadBuffer.count() != 0)
        {
          SPDR = keypadBuffer.dequeue();     
        } else
        {
          SPDR = NO_KEY;
        }
        if (waitSPI(SPI_TIMEOUT_MS))
        {
          SPIBuffer.dequeue();      
        } else
        {
          break;
        }
      }
      break;
    case (char) SPI_DUMMY:
		//Acknolegd dummy
		SPDR = SPI_DUMMY_ACK;
      //lcd.print("DUMMY");
      //DUMMY Character. Ignore
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
      //para adicionar o mais novo
      keypadBuffer.dequeue();
    }
    keypadBuffer.enqueue(localKey);
  }
}


/*Espera resposta da SPI. Retorna true se algum dado esta diponivel dentro
 *   do timeout. Caso nada seja reccebido retorna false depois do periodo de timeout
 */
bool waitSPI(int timeout)
{
  long unsigned endStamp = millis() + timeout;
  do
  {
    cli();
    int c = SPIBuffer.count();
    sei();
    if (c)
    {
      return true;
    }
  } while (millis() <= endStamp);
  return false; 
}

// SPI interrupt routine
// Antende interrupcao SPI
ISR (SPI_STC_vect)
{
  byte c = SPDR;
  //Colocar valor recebido no buffer SPI
  if (SPIBuffer.count() >= SPI_BUFFER_SIZE)
  {
        //Buffer esta cheio, elimina elemento
        SPIBuffer.dequeue();  
  }
  SPIBuffer.enqueue(c);
}

