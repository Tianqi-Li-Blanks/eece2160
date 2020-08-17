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

using namespace std;

SevenSegment::SevenSegment()
{
  reg0_hexValue = 0;
  reg1_hexValue = 0;
}

void SevenSegment::Hex_ClearAll()
{
  reg0_hexValue = 0;
  reg1_hexValue = 0;
  de1.RegisterWrite(HEX3_HEX0_BASE, reg0_hexValue);
  de1.RegisterWrite(HEX5_HEX4_BASE, reg1_hexValue);  
}

SevenSegment::~SevenSegment()
{
  Hex_ClearAll();
}

void SevenSegment::Hex_ClearSpecific(int index)
{
  bitset<32> reg0Bits(reg0_hexValue);
  bitset<16> reg1Bits(reg1_hexValue);
  if(0<= index <= 3){
     for(int i=0; i < 7; i++){
       reg0Bits[i + index * 8] = 0;
     }
     reg0_hexValue = (int)(reg0Bits.to_ulong());
     de1.RegisterWrite(HEX3_HEX0_BASE, reg0_hexValue);
  }
  else if(4<= index <= 5){
     for(int i=0; i < 7; i++){
       reg1Bits[i + (index - 4) * 8] = 0;
     }
     reg1_hexValue = (int)(reg1Bits.to_ulong());
     de1.RegisterWrite(HEX5_HEX4_BASE, reg1_hexValue); 
  }
  else {
    cout << "out rage" << endl;
  }
}

int SevenSegment::WriteHelp(int index, int value, int hex_value){
   bitset<32> regBits(hex_value);
   if(value == -1){
     for(int i= 0; i < 7; i++){
       if(i == 6){
         regBits[i + index * 8] = 1;
       }
       else {     
         regBits[i + index * 8] = 0;
       }
     }
     hex_value = (int)(regBits.to_ulong());
     return hex_value;
   }
   else if(value == 0){
     for(int i= 0; i < 7; i++){
       if(i == 6){
         regBits[i + index * 8] = 0;
       }
       else {     
         regBits[i + index * 8] = 1;
       }
     }
     hex_value = (int)(regBits.to_ulong());
     return hex_value;
   }
   else if (value == 1) {
     for(int i= 0; i < 7; i++){
       if(i == 1){
         regBits[i + index * 8] = 1;  
       }
       else if(i == 2){
         regBits[i + index * 8] = 1;
       }
       else {
         regBits[i + index * 8] = 0;
       }
     }
     hex_value = (int)(regBits.to_ulong());
     return hex_value;
   }
   else if(value == 2){
     for(int i= 0; i < 7; i++){
       if(i == 2){
         regBits[i + index * 8] = 0;
       }
       else if(i == 5){
         regBits[i + index * 8] = 0;
       }
       else {
         regBits[i + index * 8] = 1;
       }
     }
     hex_value = (int)(regBits.to_ulong());
     return hex_value;
   }    
   else if(value == 3){
       for(int i= 0; i < 7; i++){
         if(i == 4){
           regBits[i + index * 8] = 0;
         }
         else if(i == 5){
           regBits[i + index * 8] = 0;
         }
         else {
           regBits[i + index * 8] = 1;
         }
       }
       hex_value = (int)(regBits.to_ulong());
       return hex_value;
   }
   else if(value == 4){
       for(int i= 0; i < 7; i++){
         if(i == 0){
           regBits[i + index * 8] = 0;
         }
         else if(i == 3){
           regBits[i + index * 8] = 0;
         }
         else if(i == 4){
           regBits[i + index * 8] = 0;
         }
         else {
           regBits[i + index * 8] = 1;
         }
       }
       hex_value = (int)(regBits.to_ulong());
       return hex_value;
   }
   else if(value == 5){
       for(int i= 0; i < 7; i++){
         if(i == 1){
           regBits[i + index * 8] = 0;
         }
         else if(i == 4){
           regBits[i + index * 8] = 0;
         }
         else {
           regBits[i + index * 8] = 1;
         }
       }
       hex_value = (int)(regBits.to_ulong());
       return hex_value;
   } 
   else if(value == 6){
       for(int i= 0; i < 7; i++){
         if(i == 1){
           regBits[i + index * 8] = 0;
         }
         else {
           regBits[i + index * 8] = 1;
         }
       }
       hex_value = (int)(regBits.to_ulong());
       return hex_value;
   }
   else if(value == 7){
     for(int i= 0; i < 7; i++){
       if(i == 0){
         regBits[i + index * 8] = 1;
       }
       else if(i == 1){
         regBits[i + index * 8] = 1;
       }
       else if(i == 2){
         regBits[i + index * 8] = 1;
       }
       else {
         regBits[i + index * 8] = 0;
       }
     }
     hex_value = (int)(regBits.to_ulong());
     return hex_value;
   } 
   else if(value == 8){
     for(int i= 0; i < 7; i++){
       regBits[i + index * 8] = 1;
     }
     hex_value = (int)(regBits.to_ulong());
     return hex_value;
   }
   else if(value == 9){
     for(int i= 0; i < 7; i++){
       if(i == 4){
           regBits[i + index * 8] = 0;
         }
         else {
           regBits[i + index * 8] = 1;
         }
     }
     hex_value = (int)(regBits.to_ulong());
     return hex_value;
   }
   
   else if(value == 10){
     for(int i= 0; i < 7; i++){
       if(i == 3){
           regBits[i + index * 8] = 0;
         }
         else {
           regBits[i + index * 8] = 1;
         }
     }
     hex_value = (int)(regBits.to_ulong());
     return hex_value;
   }
   else if(value == 11){
     for(int i= 0; i < 7; i++){
       if(i == 0){
         regBits[i + index * 8] = 0;
       }
       else if(i == 1){
         regBits[i + index * 8] = 0;
       }
       else {
         regBits[i + index * 8] = 1;
       }
     }
     hex_value = (int)(regBits.to_ulong());
     return hex_value;
   }
   else if(value == 12){
     for(int i= 0; i < 7; i++){
       if(i == 1){
         regBits[i + index * 8] = 0;
       }
       else if(i == 2){
         regBits[i + index * 8] = 0;
       }
       else if(i == 6){
         regBits[i + index * 8] = 0;
       }
       else {
         regBits[i + index * 8] = 1;
       }
     }
     hex_value = (int)(regBits.to_ulong());
     return hex_value;
   }
   else if(value == 13){
     for(int i= 0; i < 7; i++){
       if(i == 0){
         regBits[i + index * 8] = 0;
       }
       else if(i == 5){
         regBits[i + index * 8] = 0;
       }
       else {
         regBits[i + index * 8] = 1;
       }
     }
     hex_value = (int)(regBits.to_ulong());
     return hex_value;
   }
   else if(value == 14){
     for(int i= 0; i < 7; i++){
       if(i == 1){
         regBits[i + index * 8] = 0;
       }
       else if(i == 2){
         regBits[i + index * 8] = 0;
       }
       else {
         regBits[i + index * 8] = 1;
       }
     }
     hex_value = (int)(regBits.to_ulong());
     return hex_value;
   }
   else if(value == 15){
     for(int i= 0; i < 7; i++){
       if(i == 1){
         regBits[i + index * 8] = 0;
       }
       else if(i == 2){
         regBits[i + index * 8] = 0;
       }
       else if(i == 3){
         regBits[i + index * 8] = 0;
       }
       else {
         regBits[i + index * 8] = 1;
       }
     }
     hex_value = (int)(regBits.to_ulong());
     return hex_value;
   }
}

void SevenSegment::Hex_WriteSpecific(int index, int value)
{
   if(index <= 3 && index >=0){
    reg0_hexValue = WriteHelp(index, value, reg0_hexValue);
    de1.RegisterWrite(HEX3_HEX0_BASE, reg0_hexValue);
   }
   else if(index <= 5 && index >=4){
     index = index -4;
     reg1_hexValue = WriteHelp(index, value, reg1_hexValue);
     de1.RegisterWrite(HEX5_HEX4_BASE, reg1_hexValue);
   }
}

int lengthfunction(int number)
{    
      int counter=0;
      while(number)
     {        
            number=number/10;
            counter++;
      }
      return (counter);
}

int findDigit(int index, int value) 
{ 
    if(index == 0){
       return value % 10;
    }
    else if(index == 1){
       return (value / 10) % 10;
    }
    else if(index == 2){
       return (value / 100) % 10;
    }
    else if(index == 3){
       return (value / 1000) % 10;
    }
    else if(index == 4){
       return (value / 10000) % 10;
    }
    else if(index == 5){
       return (value / 100000) % 10;
    }
} 
 
void SevenSegment::Hex_WriteNumber(int number)
{
  if(number >= 0){
    int length = lengthfunction(number);
    int count = length - 1;
    if(length <= 6){
      for(int i= 0; i< length; i++){
        int v = findDigit(i, number);
        Hex_WriteSpecific(i, v); 
        count --;
      }
    }
    else {
      cout << "out range" << endl;
    }
  }
  else if(number < 0){
    int length = lengthfunction(-number);
    int count = length - 1;
    if(length <= 5){
      for(int i= 0; i< length; i++){
        int v = findDigit(i, -number);
        Hex_WriteSpecific(i, v); 
        count --;
      }
      Hex_WriteSpecific(length, -1); 
    }
    else {
      cout << "out range" << endl;
    }
  }
}
