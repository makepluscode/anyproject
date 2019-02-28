#include "IPIRWrapper.h"

bool PIRWrapper::isAnybody()
{
  int val = digitalRead(PIR);

  Serial.print("gpio val : ");
  Serial.print(val);
  Serial.println("");
  
  return digitalRead(PIR);
}