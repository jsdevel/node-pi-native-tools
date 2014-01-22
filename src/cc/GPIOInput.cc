extern "C" {
#include "./bcm2835.h"
}
#include "GPIO.h"
#include "GPIOInput.h"

GPIOInput::GPIOInput(
  int pin,
  int direction
) : GPIO(pin, 0) {
  if(direction > 0){
    bcm2835_gpio_set_pud(this->rpi_pin, BCM2835_GPIO_PUD_UP);
  } else if(direction < 0) {
    bcm2835_gpio_set_pud(this->rpi_pin, BCM2835_GPIO_PUD_DOWN);
  } else {
    bcm2835_gpio_set_pud(this->rpi_pin, BCM2835_GPIO_PUD_OFF);
  }
}

