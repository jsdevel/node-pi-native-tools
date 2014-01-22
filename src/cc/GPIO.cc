extern "C" {
#include "./bcm2835.h"
}
#include "GPIO.h"
#include "Exceptions.h"

GPIO::GPIO(
  int _pin,
  int _function
) : function(_function), pin(_pin) {
  switch(pin){
    case 3: rpi_pin = RPI_V2_GPIO_P1_03;break;
    case 5: rpi_pin = RPI_V2_GPIO_P1_05;break;
    case 7: rpi_pin = RPI_V2_GPIO_P1_07;break;
    case 8: rpi_pin = RPI_V2_GPIO_P1_08;break;
    case 10: rpi_pin = RPI_V2_GPIO_P1_10;break;
    case 11: rpi_pin = RPI_V2_GPIO_P1_11;break;
    case 12: rpi_pin = RPI_V2_GPIO_P1_12;break;
    case 13: rpi_pin = RPI_V2_GPIO_P1_13;break;
    case 15: rpi_pin = RPI_V2_GPIO_P1_15;break;
    case 16: rpi_pin = RPI_V2_GPIO_P1_16;break;
    case 18: rpi_pin = RPI_V2_GPIO_P1_18;break;
    case 19: rpi_pin = RPI_V2_GPIO_P1_19;break;
    case 21: rpi_pin = RPI_V2_GPIO_P1_21;break;
    case 22: rpi_pin = RPI_V2_GPIO_P1_22;break;
    case 23: rpi_pin = RPI_V2_GPIO_P1_23;break;
    case 24: rpi_pin = RPI_V2_GPIO_P1_24;break;
    case 26: rpi_pin = RPI_V2_GPIO_P1_26;break;
    default:
      throw Exceptions::UNKNOWN_GPIO_PORT;
  }

  switch(function){
    case 1:
      bcm2835_gpio_fsel(rpi_pin, BCM2835_GPIO_FSEL_OUTP);
      break;
    case 0:
      bcm2835_gpio_fsel(rpi_pin, BCM2835_GPIO_FSEL_INPT);
      break;
    default:
      throw Exceptions::UNKNOWN_GPIO_FUNCTION;
  }
}

unsigned int GPIO::value(){
  return bcm2835_gpio_lev(rpi_pin);
}