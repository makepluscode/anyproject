#include "IRremote.h"

class IRsendWrapper : public IRsend
{
  public:
    IRsendWrapper() : IRsend(5) {
      DBG_PRINTLN("IRsendWrapper called!");
    }
    
    void sendTurnOffTv();
};