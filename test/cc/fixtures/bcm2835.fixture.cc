#include <stdint.h>
#include <iostream>
#include "../../../src/cc/bcm2835.h"
#include "../helpers/test-ns.h"

using namespace std;
void bcm2835_gpio_fsel(uint8_t pin, uint8_t mode){}
void bcm2835_gpio_write(uint8_t pin, uint8_t on){
  if(on == 0){
    test::__output_writes += 0;
  } else {
    test::__output_writes += 1;
  }
}
void bcm2835_delay(unsigned int millis){}
void bcm2835_gpio_set_pud(uint8_t pin, uint8_t pud){}
uint8_t bcm2835_gpio_lev(uint8_t pin){
  return test::__output_writes;
}