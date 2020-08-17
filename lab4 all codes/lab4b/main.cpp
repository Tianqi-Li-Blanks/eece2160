#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <bitset>
#include <string>
#include <cerrno>
#include "DE1SoChps.h"
#include "SevenSegment.h"
#include "LEDControl.h"

using namespace std;

/**
* Main operates the DE1-SoC 7-Segment Displays
* This program writes an integer number on the 7-Segment Displays
*/

int main(void)
{
  SevenSegment *display = new SevenSegment;
  LEDControl ledc;

  int option;
  cout << "Tpying 1 if you are switch well the value with the button: ";
  cin >> option;
  if(option == 1){
    int value = ledc.ReadAllSwitches();
    cout << value << endl;
    ledc.WriteAllLeds(value);
    display->Hex_WriteNumber(value);
    int temp = value;
    while(true){
      int pushButtonValue = ledc.PushButtonGet();
      if(pushButtonValue != -1) {
         temp = ledc.ChangeValue(pushButtonValue, temp);
      }
      ledc.WriteAllLeds(temp);
      display->Hex_ClearAll();
      display->Hex_WriteNumber(temp);
    }
  }
  else{
    cout << "fail to continue" << endl;
  }

}


