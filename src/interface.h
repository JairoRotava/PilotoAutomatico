#ifndef interface_h
#define interface_h

const int RODA_SENSOR_PIN = 1;
const int ALINHA_POT_PIN = 2;

//Prototipos de funcoes de interface
void motor_velocidade(int velocidade);  //seta velocidade do motor. Negativo inverte sentido
void motor_on(void);        //Liga motor
void motor_off(void);       //Desliga motor
uint8_t motor_le_status(void);  //Le status do motor

int gps_le(void);           //Le etrada do gps
void gps_on(void);          //Liga entrada gps
void gps_off(void);         //Desliga entrada gps

int roda_le_posicao(void);  //Le posicacao da roda
int roda_filtro(int);       //Filtro do sensor da roda

int alinha_le_pot(void);    //Le potenciomentro que alinha maquina
int alinha_filtro(int);     //filtro utilizado no potenciomentro de alinha

int controle_pid(int);      //Faz controle PID
void hardware_inicia(void); //Inicializa todo hardware

//Telas LCD
void LCDMostraVariaveis(void);

//Serial
void envia_status_serial(void);

// Wrap printf para lcd
void lcd_p(const char *fmt, ... );
void lcd_p(const __FlashStringHelper *fmt, ... );


#endif