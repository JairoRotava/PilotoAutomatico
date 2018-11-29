#include <Arduino.h>
#include <SPI.h>
#include "TLE6209.h"
#include "./LCDKeypad/LCDKeypad_SPI.h"
#include "interface.h"
#include "adc.h"
#include "serial_printf_wrap.h"


//Objeto para LCD e teclado
LCDKeypad_SPI lcdKeypad;

//Variaveis importantes
//volatile int alinha_potenciometro;
//volatile int roda_posicao;
//Pega variavel do AD.
#define alinha_potenciometro adc_valores[1]
#define roda_posicao adc_valores[2]

volatile int motor_vel=0;
volatile int gps_entrada=0;
volatile int motor_status=0;

//Motor - seta velocidade
void motor_velocidade(int velocidade)
{
    TLE6209_out(velocidade);
    motor_vel = velocidade;
}
//Liga motor
void motor_on(void)
{
    TLE6209_on();
}
//Desliga motor
void motor_off(void)
{
    TLE6209_off();
}
//Le status motor
uint8_t motor_le_status(void)
{
    return(TLE6209_config(STATUS_RESET| OVLO_OFF | PWM_MODE_SLOW | CURRENT_LIMIT_4A | CHOPPER_OFF_80_US));
}


int gps_le(void);           //Le etrada do gps
void gps_on(void);          //Liga entrada gps
void gps_off(void);         //Desliga entrada gps

//Le posicacao da roda
int roda_le_posicao(void)
{
    //return(analogRead(RODA_SENSOR_PIN));
    return(roda_posicao);
}

//Filtro do sensor da roda
int roda_filtro(int input)
{
    return(input);
};       

//Le potenciomentro que alinha maquina
int alinha_le_pot(void)
{
    //return(analogRead(ALINHA_POT_PIN));
    return(alinha_potenciometro);
}

//filtro utilizado no potenciomentro de alinha
int alinha_filtro(int input)
{
    return(input);
}     

//Faz controle PID
int controle_pid(int input)
{
    return(input);
};      

//Inicializa hardware
void hardware_inicia()
{
  Serial.begin(9600);
  SPI.begin(); 
  TLE6209_init();

  //Inicia AD
//  analogReference(INTERNAL);
//  analogRead(RODA_SENSOR_PIN);
 // analogRead(ALINHA_POT_PIN);
  ADConfigura();

  //Inicia LCD_KEYPAD
  delay(500); //espera inicializacao do LCD e teclado
  lcdKeypad.begin(16,2);
  lcdKeypad.print(F("Teste Linux"));
  delay(1000);
}

void LCDMostraVariaveis(void)
{
    lcdKeypad.clear();
    lcd_p(F("A:%4d  R:%4d"),alinha_potenciometro,roda_posicao);
}

void envia_status_serial(void)
{
    p(F("G:%d A:%d R:%d V:%d S:%d\n"),
        gps_entrada,alinha_potenciometro,roda_posicao,motor_vel,motor_status);
}


/* Wrap para ter printf para lcd 
 *
 * Assim eh melhor pois nao precisa alterar a biblioteca original
 * e fica compativel com outros sistemas default
 */
void lcd_p(const char *fmt, ... ){
        char buf[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 128, fmt, args);
        va_end (args);
        lcdKeypad.print(buf);
}

/* Wrap para ter printf para lcd 
 *
 * Assim eh melhor pois nao precisa alterar a biblioteca original
 * e fica compativel com outros sistemas default
 */
void lcd_p(const __FlashStringHelper *fmt, ... ){
  char buf[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt);
#ifdef __AVR__
  vsnprintf_P(buf, sizeof(buf), (const char *)fmt, args); // progmem for AVR
#else
  vsnprintf(buf, sizeof(buf), (const char *)fmt, args); // for the rest of the world
#endif
  va_end(args);
  lcdKeypad.print(buf);
}

