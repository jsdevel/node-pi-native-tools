#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "../../src/cc/bcm2835.h"
#include "../../src/cc/GPIOOutput.h"
#include "helpers/TestVars.h"

using namespace std;

extern TestVars TEST_VARS;

#define USE_BEFORE 1
#define USE_AFTER 1
#include "helpers/assert.h"
namespace test {
  GPIOOutput * gpio;

  void before(){
    TEST_VARS.reset();
    gpio = new GPIOOutput(5);
  }

  void after(){
    delete gpio;
  }

  /*void valid_pins_for_constructor_throw_no_error(){
    int pins [17] = {3, 5, 7, 8, 10, 11, 12, 13, 15, 16, 18, 19, 21, 22, 23, 24, 26};
    for(int i = 0;i<17;i++){
      new GPIOOutput(pins[i]);
    }
  }*/

  /*void invalid_pins_for_constructor_throw_error(){
    int pins [5] = {1, 2, 0, 40, 50};
    for(int i = 0;i<5;i++){
      try {
        new GPIOOutput(pins[i]);
        fail("didn't throw for");
      } catch(...){
        continue;
      }
    }
  }*/

  void write_calls_bcm_write(){
    gpio->write();
    assert(TEST_VARS.output_write == 1);
    gpio->write();
    assert(TEST_VARS.output_write == 2);
  }

  void write_uses_given_pin(){
    gpio->write();
    //note that the GPIO class should convert this
    assert(TEST_VARS.currentPin == 5);
  }

  void erase_calls_bcm_write(){
    gpio->erase();
    assert(TEST_VARS.currentValue == 0);
    gpio->write();
    assert(TEST_VARS.currentValue == 1);
    gpio->erase();
    assert(TEST_VARS.currentValue == 0);
  }

  void erase_uses_given_pin(){
    gpio->erase();
    //note that the GPIO class should convert this
    assert(TEST_VARS.currentPin == 5);
  }
}

int main(){
  SUITE();
  /*TEST(valid_pins_for_constructor_throw_no_error);
  TEST(invalid_pins_for_constructor_throw_error);*/
  TEST(write_calls_bcm_write);
  TEST(write_uses_given_pin);
  TEST(erase_calls_bcm_write);
  TEST(erase_uses_given_pin);
  END();
}
