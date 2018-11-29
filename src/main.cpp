#include <Arduino.h>
#include "interface.h"
#include "command.h"
#include "./PID/FastPID.h"
#include "serial_printf_wrap.h"


float Kp=0.1, Ki=50.5, Kd=0, Hz=10;
int output_bits = 16;
bool output_signed = true;

FastPID myPID(Kp, Ki, Kd, Hz, output_bits, output_signed);

void setup() {
  // put your setup code here, to run once:
  hardware_inicia();
  motor_on();
  addSerialCommands();

  myPID.setOutputRange(-255,+255);
  myPID.setBangBang(150,10);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.printf("Teste %d",122);
  motor_le_status();
  //delay(200);
  
  motor_velocidade(myPID.step(alinha_le_pot(), roda_le_posicao()));
  delay(100);
  

  //LCDMostraVariaveis();
  

  //motor_velocidade(alinha_le_pot());

  envia_status_serial();
  //handlerSerialCommands();

}
