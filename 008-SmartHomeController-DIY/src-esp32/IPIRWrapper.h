#include <Arduino.h>

#define PIR 12

class PIRWrapper
{
  public:
    PIRWrapper()
    {
      pinMode (PIR, INPUT);
    }

    bool isAnybody();
};