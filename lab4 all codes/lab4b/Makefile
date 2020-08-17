
Program: main.o DE1SoChps.o SevenSegment.o LEDControl.o
        g++ main.o DE1SoChps.o SevenSegment.o LEDControl.o -o Program

main.o: main.cpp DE1SoChps.h SevenSegment.h LEDControl.h
        g++ -g -Wall -c main.cpp

SevenSegment.o: SevenSegment.cpp SevenSegment.h
        g++ -g -Wall -c SevenSegment.cpp

LEDControl.o: LEDControl.cpp LEDControl.h
        g++ -g -Wall -c LEDControl.cpp

DE1SoChps.o: DE1SoChps.cpp DE1SoChps.h
        g++ -g -Wall -c DE1SoChps.cpp

clean:
        rm SevenSegment.o DE1SoChps.o LEDControl.o main.o Program

