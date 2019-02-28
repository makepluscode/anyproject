#include <Arduino.h>

#define R 21
#define G 22
#define B 23

class LedWrapper
{
  public:
    LedWrapper()
    {
      pinMode (R, OUTPUT); 
      pinMode (G, OUTPUT);
      pinMode (B, OUTPUT); 
    }

    void turnOnRed();
    void turnOnGreen();
    void turnOnBlue();

    void turnOff();
};