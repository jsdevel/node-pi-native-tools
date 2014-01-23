#ifndef GPIO_OUTPUT_HEADER
#define GPIO_OUTPUT_HEADER
#include "GPIO.h"

class GPIOOutput : public GPIO {
public:
  GPIOOutput(int pin);
  void erase();
  void write();
};
#endif