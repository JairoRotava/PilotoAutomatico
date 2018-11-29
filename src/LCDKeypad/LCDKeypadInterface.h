#ifndef LCDKeypadInterface_h
#define LCDKeypadInterface_h

//Code for LCD_COMMAND
#define LCD_COMMAND     ((byte)0x1B)

//Comando para ler buffer do teclado
#define KEYPAD_READ  ((byte)0x0A)

//Valor dummy, ignorado pelo display. Necessario para uso no SPI
#define SPI_DUMMY	((byte) 250)
#define SPI_DUMMY_ACK ((byte) 251)

#define KEYPAD_BUFFER_SIZE  4
#define SERIAL_TIMEOUT_MS  100


// library interface description
#define NO_KEY  	((byte) 0)
#define SELECT_KEY  ((byte) 5)
#define LEFT_KEY  	((byte) 1)
#define UP_KEY  	((byte) 3)
#define DOWN_KEY  	((byte) 2)
#define RIGHT_KEY  	((byte) 4)

//enum keypad {NO_KEY = 0,SELECT_KEY, LEFT_KEY,  UP_KEY, DOWN_KEY, RIGHT_KEY };

#endif