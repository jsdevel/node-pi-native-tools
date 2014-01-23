#ifndef GPIO_HEADER
#define GPIO_HEADER
#include "bcm2835.h"
class GPIO {
protected:
  int pin;
  int rpi_pin;

public:
  const int function;

  GPIO(
    int pin,
    int function
  );

  unsigned int value();
};
#endif