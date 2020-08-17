
Program: main.o DE1SoChps.o SevenSegment.o
        g++ main.o DE1SoChps.o SevenSegment.o -o LEDCT

main.o: main.cpp DE1SoChps.h SevenSegment.h
        g++ -g -Wall -c main.cpp

SevenSegment.o: SevenSegment.cpp SevenSegment.h
        g++ -g -Wall -c SevenSegment.cpp

DE1SoChps.o: DE1SoChps.cpp DE1SoChps.h
        g++ -g -Wall -c DE1SoChps.cpp

clean:
        rm SevenSegment.o DE1SoChps.o LEDControl.o main.o Program

