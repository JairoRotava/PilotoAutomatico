
// ensure this library description is only included once
#ifndef Keypad_h
#define Keypad_h

// library interface description
#define NO_KEY  0
#define LEFT_KEY  1
#define DOWN_KEY  2
#define UP_KEY  3
#define RIGHT_KEY  4
#define SELECT_KEY  5


//AD for keyboard
const int DEFAULT_KEY_PIN  = 0 ;
//Value range for AD reading accepting key
const int DEFAULT_THRESHOLD = 50;

const unsigned long WAIT_TO_REPEAT = 1000;
const unsigned long REPEAT_PERIOD = 50;

//Sample rate of keyboard
const int REFRESH_RATE = 10;

//that's read "analogue read value"
const int RIGHTKEY_ARV = 0;
const int UPKEY_ARV = 99; 
const int DOWNKEY_ARV = 257;
const int LEFTKEY_ARV = 410;
const int SELKEY_ARV = 640;
const int NOKEY_ARV = 1023;

class Keypad
{
  public:
    Keypad();
    int getKey();
    int readKey();
    void setRate(int);
	void setKeyWaitToRepeat(unsigned long);
	void setKeyRepeatPeriod(unsigned long);
  private:
    int _refreshRate;
    int _keyPin;
    int _threshold;
    int _curInput;
    int _curKey;
    int _prevKey;
    unsigned long _oldTime;
    unsigned long _waitRepeat;
    unsigned long _repeatKey;
	unsigned long waitToRepeat;
	unsigned long repeatKeyPeriod;

	};

#endif

