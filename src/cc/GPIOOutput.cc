extern "C" {
#include "./bcm2835.h"
}
#include "GPIO.h"
#include "GPIOOutput.h"

GPIOOutput::GPIOOutput(int pin) : GPIO(pin, 1) {}

void GPIOOutput::erase(){
  bcm2835_gpio_write(this->rpi_pin, 0);
}

void GPIOOutput::write(){
  bcm2835_gpio_write(this->rpi_pin, 1);
}