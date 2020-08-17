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
#include "LEDControl.h"

using namespace std;

LEDControl::LEDControl()
{
  leds_regValue = 0;
}

LEDControl::~LEDControl()
{
  //WriteAllLeds(0);
}

void LEDControl::Write1Led(int ledNum, int state) {
    if(0 <= ledNum <= 9) {
      int value = 1;
      int count = ledNum;
      if(state == 1) {
        while(count > 0) {
          value = 2 * value;
          count --;
        }
        de1.RegisterWrite(LEDR_BASE, value);
        leds_regValue = value;
      }
      else if(state == 0){
        de1.RegisterWrite(LEDR_BASE, 0);
        leds_regValue = 0;
      }
      else{
        cout << "ERROR: state should only be 0 and 1 means off and on" << endl;
      }
    }
    else {
      cout << "ERROR: ledNum should be in 0-9" << endl;
    }
}

void LEDControl::WriteAllLeds(int value){
    //  1111111111 is 1023 means all turn on
      if(0 <= value <= 1023){
        de1.RegisterWrite(LEDR_BASE, value);
        leds_regValue = value;
      }
      else{
        cout << "out rage" << endl;
      } 
}



int LEDControl::Read1Switch(int switchNum) {
    if(0 <= switchNum <= 9) {
      int value = de1.RegisterRead(SW_BASE);
      int state;
      while (switchNum >= 0){
        state = value % 2;
        value = (value - state) / 2;
        switchNum--;
      }
      return state;
    }
    else{
      cout << "ERROR: switchNum should be in 0-9" << endl;
    } 
}


int LEDControl::ReadAllSwitches(){
    return de1.RegisterRead(SW_BASE);
}

int LEDControl::PushButtonGet() {
    if(de1.RegisterRead(KEY_BASE) == 0){
      return -1;
    }   
    if(de1.RegisterRead(KEY_BASE) == 1) {
      return 0;
    }
    else if(de1.RegisterRead(KEY_BASE) == 2) {
           return 1;
    }
    else if(de1.RegisterRead(KEY_BASE) == 4) {
           return 2;
    } 
    else if(de1.RegisterRead(KEY_BASE) == 8) {	
           return 3;
    }
    //push more than one key buttons
    else {
      return 4;
    }
}
  
int LEDControl::ChangeValue(int pushButtonValue, int value){
    bitset<10> buttons(value);
    if(pushButtonValue == 0){
       sleep(1);
       value = value + 1;
       bitset<10> newB(value);
       cout << "New buttons: " << newB  << endl;
       cout << "New value: " << value << endl;
       leds_regValue = value;
       return value;
    }
    else if(pushButtonValue == 1){
       sleep(1);
       value = value - 1;
       bitset<10> newB(value);
       cout << "New buttons: " << newB  << endl;
       cout << "New value: " << value << endl;
       leds_regValue = value;
       return value;

    }
    else if(pushButtonValue == 2){
        sleep(1);
        buttons >>= 1;
        cout << "New buttons: " << buttons  << endl;
        int temp = (int)(buttons.to_ulong());
        cout << "New value: " << temp << endl;
        leds_regValue = value;
        return temp;
    }
    else if(pushButtonValue == 3){
        sleep(1);
        buttons <<= 1;
        cout << "New buttons: " << buttons << endl;
        int temp = (int)(buttons.to_ulong());
        cout << "New value: " << temp << endl;
        leds_regValue = value;
        return temp;
    }
    else if(pushButtonValue == 4){
        sleep(1);
        leds_regValue = value;
        return value;
    }
}



