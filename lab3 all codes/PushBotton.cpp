#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <bitset>
#include <string>
#include <cerrno>

using namespace std;

// Physical base address of FPGA Devices
const unsigned int LW_BRIDGE_BASE = 0xFF200000; // Base offset

// Length of memory-mapped IO window
const unsigned int LW_BRIDGE_SPAN = 0x00005000; // Address map size

// Cyclone V FPGA device addresses
const unsigned int LEDR_BASE = 0x00000000; // Leds offset
const unsigned int SW_BASE = 0x00000040; // Switches offset
const unsigned int KEY_BASE = 0x00000050; // Push buttons offset


class DE1SoCfpga
{	
  char *pBase;
  int fd;
  
public:
  DE1SoCfpga()
  {
    // Open /dev/mem to give access to physical addresses
    fd = open( "/dev/mem", (O_RDWR | O_SYNC));
    if (fd == -1) // check for errors in openning /dev/mem
    {
      cout << "ERROR: could not open /dev/mem..." << endl;
      exit(1); 
    }
    // Get a mapping from physical addresses to virtual addresses
    pBase = (char *)mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
    if (pBase == MAP_FAILED) // check for errors
    {
      cout << "ERROR: mmap() failed..." << endl;
      close (fd); // close memory before exiting
      exit(1); // Returns 1 to the operating system;
    } 
  }
 
  ~DE1SoCfpga()
  {
    if (munmap (pBase, LW_BRIDGE_SPAN) != 0){
      cout << "ERROR: munmap() failed..." << endl;
      exit(1);
    }
    close (fd); // close memory
  }		
  
  void RegisterWrite(unsigned int reg_offset, int value)
  {
    * (volatile unsigned int *)(pBase + reg_offset) = value;
  }

  int RegisterRead(unsigned int reg_offset)
  {
    return * (volatile unsigned int *)(pBase + reg_offset);
  }

  /** Changes the state of an LED (ON or OFF)
  * @param pBase  Base address returned by 'mmap'
  * @param ledNum  LED number (0 to 9)
  * @param state  State to change to (ON or OFF)
  */

  void Write1Led(int ledNum, int state) {
    if(0 <= ledNum <= 9) {
      int value = 1;
      int count = ledNum;
      if(state == 1) {
        while(count > 0) {
          value = 2 * value;
          count --;
        }
        RegisterWrite(LEDR_BASE, value);
      }
      else if(state == 0){
        RegisterWrite(LEDR_BASE, 0);
      }
      else{
        cout << "ERROR: state should only be 0 and 1 means off and on" << endl;
      }
    }
    else {
      cout << "ERROR: ledNum should be in 0-9" << endl;
    }
  }

  /** Reads the value of a switch
  * - Uses base address of I/O
  * @param pBase  Base address returned by 'mmap'
  * @param switchNum Switch number (0 to 9)
  * @return  Switch value read
  */

  int Read1Switch(int switchNum) {
    if(0 <= switchNum <= 9) {
      int value = RegisterRead(SW_BASE);
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

  /** Set the state of the LEDs with the given value.
   * *
   * * @param pBase Base address for general-purpose I/O
   * * @param value Value between 0 and 1023 written to the LEDs
   * */
  void WriteAllLeds(int value){
  //  1111111111 is 1023 means all turn on
    if(0 <= value <= 1023){
      RegisterWrite(LEDR_BASE, value);
    }
    else{
      cout << "out rage" << endl;
    } 
  }


  /** Reads all the switches and returns their value in a single integer.
   * *
   * * @param pBase Base address for general-purpose I/O
   * * @return A value that represents the value of the switches
   * */
  int ReadAllSwitches(){
  //bitset<10> bits;
  //for (int i = 0; i < 10; i++) {
  //  bits.set(i, Read1Switch(pBase, i));
  //}  
  //int result = (int)(bits.to_ulong());
  //return result;
    return RegisterRead(SW_BASE);
  }


  int PushButtonGet() {
    if(RegisterRead(KEY_BASE) == 0){
      return -1;
    }   
    if(RegisterRead(KEY_BASE) == 1) {
      return 0;
    }
    else if(RegisterRead(KEY_BASE) == 2) {
           return 1;
    }
    else if(RegisterRead(KEY_BASE) == 4) {
           return 2;
    } 
    else if(RegisterRead(KEY_BASE) == 8) {	
           return 3;
    }
    //push more than one key buttons
    else {
      return 4;
    }
  }

  int ChangeValue(int pushButtonValue, int value){
    bitset<10> buttons(value);
    if(pushButtonValue == 0){
       sleep(1);
       value = value + 1;
       bitset<10> newB(value);
       cout << "New buttons: " << newB  << endl;
       cout << "New value: " << value << endl;
       return value;
    }
    else if(pushButtonValue == 1){
       sleep(1);
       value = value - 1;
       bitset<10> newB(value);
       cout << "New buttons: " << newB  << endl;
       cout << "New value: " << value << endl;
       return value;

    }
    else if(pushButtonValue == 2){
        sleep(1);
        buttons >>= 1;
        cout << "New buttons: " << buttons  << endl;
        int temp = (int)(buttons.to_ulong());
        cout << "New value: " << temp << endl;
        return temp;
    }
    else if(pushButtonValue == 3){
        sleep(1);
        buttons <<= 1;
        cout << "New buttons: " << buttons << endl;
        int temp = (int)(buttons.to_ulong());
        cout << "New value: " << temp << endl;
        return temp;
    }
    else if(pushButtonValue == 4){
        sleep(1);
        return value;
    }
  }
  
};

int main()
{
  DE1SoCfpga de1;  

// ************** Put your code here **********************
  
  int option;
  cout << "Tpying 1 if you are switch well the value with the button: ";
  cin >> option;
  if(option == 1){
    int value = de1.ReadAllSwitches();
    de1.WriteAllLeds(value);
    int temp = value;
    while(true){
      int pushButtonValue = de1.PushButtonGet();
      if(pushButtonValue != -1) {
         temp = de1.ChangeValue(pushButtonValue, temp);
      }
      de1.WriteAllLeds(temp);
    }
  }
  else{
    cout << "fail to continue" << endl;
  }


// Done
return 0;
}

