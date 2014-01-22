#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "../../src/cc/GPIO.h"
#include "helpers/test-ns.h"

using namespace std;

#define USE_BEFORE 1
#define USE_AFTER 1
#include "helpers/assert.h"
namespace test {
  int __output_erasures;
  int __output_writes;

  GPIO * gpio;

  void before(){
    gpio = new GPIO(5, 1); 
  }

  void after(){
    delete gpio;
  }

  void valid_pins_for_constructor_throw_no_error(){
    int pins [17] = {3, 5, 7, 8, 10, 11, 12, 13, 15, 16, 18, 19, 21, 22, 23, 24, 26};
    for(int i = 0;i<17;i++){
      new GPIO(pins[i], 1);
    }
  }

  void invalid_pins_for_constructor_throw_error(){
    int pins [5] = {1, 2, 0, 40, 50};
    for(int i = 0;i<5;i++){
      try {
        new GPIO(pins[i], 1);
        fail("didn't throw for");
      } catch(...){
        continue;
      }
    }
  }

  void value_returns_the_pin_value(){
    bcm2835_gpio_write(1, 1);
    assert(gpio->value() == 1);
  }

  void exception_thrown_on_invalid_constructor(){
    try {
      new GPIO(5, 15);
      fail("should have thrown");
    } catch(...){}
  }
}

int main(){
  SUITE();
  TEST(valid_pins_for_constructor_throw_no_error);
  TEST(invalid_pins_for_constructor_throw_error);
  TEST(value_returns_the_pin_value);
  TEST(exception_thrown_on_invalid_constructor);
  END();
}
