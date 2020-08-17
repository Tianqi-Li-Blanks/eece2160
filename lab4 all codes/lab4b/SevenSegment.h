#ifndef DE1SOCHPS_H
#define DE1SOCHPS_H

#include "DE1SoChps.h"
using namespace std;


class SevenSegment {	

  private:
    unsigned int reg0_hexValue;
    unsigned int reg1_hexValue;
    DE1SoChps de1;
  
  public:
    SevenSegment();
    ~SevenSegment();
    void Hex_ClearAll();
    void Hex_ClearSpecific(int index);
    void Hex_WriteSpecific(int index, int value);
    void Hex_WriteNumber(int number);
    
    int WriteHelp(int index, int value, int hex_value);
};

#endif
