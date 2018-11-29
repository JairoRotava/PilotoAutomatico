#ifndef RS485_h
#define RS485_h

#include <inttypes.h>
#include "Print.h"

//#define RS485_DE 8
//#define RS485_RE 9
//#define rxenpin RS485_RE
//#define txenpin RS485_DE
//recompila


#define RS485_DE_OFF 0
#define RS485_DE_ON 1
#define RS485_RE_OFF 1
#define RS485_RE_ON 0



class RS485 : public Print {
public:
	RS485();
    void begin(int baudrate, int txenpin , int rxenpin);
	void receive();
	void transmit();
	void off();
	int read();
	int available();
	virtual size_t write(uint8_t);
private:
	int _txenpin;
	int _rxenpin;
};

#endif
