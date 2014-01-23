#include "../../../src/cc/GPIO.h"
GPIO::GPIO(int pin, int _function) : function(_function){
  this->rpi_pin = pin;
}