#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "DE1SoChps.h"
using namespace std;

class LEDControl{	

  private:
    unsigned int leds_regValue;
    DE1SoChps de1;
  
  public:
    LEDControl();
    ~LEDControl();
    void Write1Led(int ledNum, int value);
    void WriteAllLeds(int value);
    int Read1Switches(int switchNum);
    int ReadAllSwitches();
    int PushButtonGet();
    int ChangeValue(int pushButtonValue, int value);
    
};

#endif