#ifndef TLE6209_h
#define TLE6209_h

//Prototipos funcoes
void TLE6209_init(void);
uint8_t TLE6209_config(uint8_t);
void TLE6209_out(int16_t value);
void TLE6209_reset(void);
void TLE6209_on(void);
void TLE6209_off(void);

// Pinos de IO
const int TLE6209_PWM_PIN = 3;     //Pino de  PWM de controle do motor da borboleta
const int TLE6209_ENABLE_PIN = 6;
const int TLE6209_DIRECTION_PIN = 4;
const int TLE6209_SPI_CHIP_SELECT_PIN = 2;

/*
 * Status bits
 */
const uint8_t POWER_SUPPLY_FAIL = 0b10000000;            //7 Power supply fail
const uint8_t ALWAYS_H =          0b01000000;            //6 not used, always H
const uint8_t SHORT_VS =          0b00100000;            //5 Short to VS or acros
const uint8_t SHORT_GND =         0b00010000;            //4 Short to GND
const uint8_t OPEN_LOAD =         0b00001000;            //3 Open load
const uint8_t TEMP_WARNING  =     0b00000100;            //Warning
const uint8_t TEMP_PRE_WARN  =    0b00000010;            //Pre Warning
const uint8_t ERROR_FLAG =        0b00000001;            //0 Error-Flag

const uint8_t TEMP_MON =          0b00000110;            //1 LSB of Temperature
const uint8_t TEMP_OK  =          0b00000000;            //Below prewarning
const uint8_t TEMP_SHUTDOWN  =    0b00000110;            //Over temperature

/*
 * Control bits
 * Exemplo de uso: STATUS_RESET | OVLO_OFF | PWM_MODE_SLOW | CURRENT_LIMIT_4A | CHOPPER_OFF_24US
 */
const uint8_t STATUS_RESET =      0b10000000;   //7 Power supply fail
const uint8_t OVLO_ON =           0b01000000;            //6 not used, always H
const uint8_t OVLO_OFF =          0b00000000;            //6 not used, always H

const uint8_t PWM_MODE_FAST =     0b00000100;            //1 LSB of Temperature
const uint8_t PWM_MODE_SLOW =     0b00000000;            //1 LSB of Temperature

const uint8_t CURRENT_LIMIT_4A =  0b00000000;            //Current IL_00
const uint8_t CURRENT_LIMIT_5A =  0b00000001;            //Current IL_01
const uint8_t CURRENT_LIMIT_6A =  0b00000010;            //Current IL_10
const uint8_t CURRENT_LIMIT_7A =  0b00000011;            //Current IL_11

const uint8_t CHOPPER_OFF_24_US = 0b00000000;            //toff_00
const uint8_t CHOPPER_OFF_43_US = 0b00001000;            //toff_01
const uint8_t CHOPPER_OFF_62_US = 0b00010000;            //toff_10
const uint8_t CHOPPER_OFF_80_US = 0b00011000;            //toff_11

#endif //TLE6209
