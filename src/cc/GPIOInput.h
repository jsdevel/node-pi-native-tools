#ifndef GPIO_INPUT_HEADER
#define GPIO_INPUT_HEADER
#include "GPIO.h"

class GPIOInput : public GPIO {
public:
  GPIOInput(int pin, int direction);
};
#endif