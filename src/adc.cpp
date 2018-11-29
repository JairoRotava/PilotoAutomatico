/*
 * As funcoes encontradas aqui fazem aquisicao automatica do AD numa taxa de aquisicao
 * especifica. O timer 1 eh a base de tempo. Apos cada conversao o proximo canal e adquirido
 * Os ultimos valores lidos pela ad estao nas variaveis adc_x onde x eh o canal
 * 
 * 
 * A ideia e facilitar o uso do ad e deixar a leitura mais rapida. Com essa rotina 
 * nao precisa mais chamar a leitura do ad e aguardar ela ficar pronta. Ele fica
 * lendo automaticamente as portas e atualizando as variaveis
 * 
 * 
 */
#include <Arduino.h>

//Primeiro e ultimo canal a ser lido. Precisa ser sequencial
const byte ADC_first_channel = 1;
const byte ADC_last_channel = 2;

//Canal atual do MUX
byte ADC_channel=ADC_first_channel;  //Canal 

//Array com resultados da leitura. Ainda esta fixo em 8 pq estou com preguica de melhorar
//Canal 0 fica na posi 0. Canal 1 na posicao 1...e assim por diante
volatile int adc_valores[8];

void ADConfigura(void)
{
   // Configura Timer 1. A taxa de aquisicao depende da velocidade do timer
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  TCCR1B = bit (CS12) |bit (CS10) | bit (WGM12);  // CTC, prescaler of 1024
  TIMSK1 = bit (OCIE1B);  // WTF?
  OCR1A = 15;   //~100 Hz    
  //OCR1B = 39;   // 20 uS - sampling frequency 50 kHz para prescale = 8
  //T = 1/16Mhz * prescaler * (OCR1A+1)

  //Configura AD para trigger automatico e referenca
  ADCSRA =  bit (ADEN) | bit (ADIE) | bit (ADIF);   // turn ADC on, want interrupt on completion
  ADCSRA |= bit (ADPS2);  // Prescaler of 16
  ADMUX = bit (REFS0) | bit (REFS1) | (ADC_channel & 7);
  ADCSRB = bit (ADTS0) | bit (ADTS2);  // Timer/Counter1 Compare Match B
  ADCSRA |= bit (ADATE);   // turn on automatic triggering
}

// ADC complete ISR
ISR (ADC_vect)
  {
    adc_valores[ADC_channel] = ADC;

    //Seleciona proximo canal
    ADC_channel++;
    //Volta ao primeiro canal se ja fez todos
    if (ADC_channel > ADC_last_channel)
    {
        ADC_channel = ADC_first_channel;
    }
    //Configura mux do AD para proximo canal
    ADMUX = bit (REFS0) | bit (REFS1) | (ADC_channel & 7);
  }  // end of ADC_vect
  
EMPTY_INTERRUPT (TIMER1_COMPB_vect);