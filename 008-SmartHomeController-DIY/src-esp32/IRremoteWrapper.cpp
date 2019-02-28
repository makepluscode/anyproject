#include "IRremoteWrapper.h"

void IRsendWrapper::sendTurnOffTv()
{
  //0x20df10ef
  sendNEC(0x20df10ef, 32);
}