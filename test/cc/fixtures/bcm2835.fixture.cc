#include "../../../src/cc/bcm2835.h"
#include "../helpers/TestVars.h"

extern TestVars TEST_VARS;

void bcm2835_gpio_fsel(uint8_t pin, uint8_t mode){}
void bcm2835_gpio_write(uint8_t pin, uint8_t on){
  TEST_VARS.currentPin = pin;
  TEST_VARS.currentValue = on;
  if(on == 0){
    TEST_VARS.erase_write += 1;
  } else {
    TEST_VARS.output_write += 1;
  }
}
void bcm2835_delay(unsigned int millis){}
void bcm2835_gpio_set_pud(uint8_t pin, uint8_t pud){}
uint8_t bcm2835_gpio_lev(uint8_t pin){
  return TEST_VARS.currentValue;
}