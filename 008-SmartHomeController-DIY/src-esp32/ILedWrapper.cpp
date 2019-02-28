#include "ILedWrapper.h"

void LedWrapper::turnOnRed()
{
  digitalWrite (R, HIGH);
  digitalWrite (G, LOW);
  digitalWrite (B, LOW); 
}

void LedWrapper::turnOnGreen()
{
  digitalWrite (R, LOW);
  digitalWrite (G, HIGH);
  digitalWrite (B, LOW); 
}

void LedWrapper::turnOnBlue()
{
  digitalWrite (R, LOW);
  digitalWrite (G, LOW);
  digitalWrite (B, HIGH); 
}

void LedWrapper::turnOff()
{
  digitalWrite (R, LOW);
  digitalWrite (G, LOW);
  digitalWrite (B, LOW);
}