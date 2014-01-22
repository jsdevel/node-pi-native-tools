#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "../../src/cc/GPIOOutput.h"

using namespace std;

#define USE_BEFORE 1
#define USE_AFTER 1
#include "helpers/assert.h"
namespace test {
  int __output_writes;
  GPIOOutput * gpio;

  void before(){
    __output_writes = 0;
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
    assert(test::__output_writes == 1);
    gpio->write();
    assert(test::__output_writes == 2);
  }

  void erase_calls_bcm_write(){
    gpio->erase();
    assert(test::__output_writes == 0);
    gpio->write();
    assert(test::__output_writes == 1);
    gpio->erase();
    assert(test::__output_writes == 1);
  }

}

int main(){
  SUITE();
  /*TEST(valid_pins_for_constructor_throw_no_error);
  TEST(invalid_pins_for_constructor_throw_error);*/
  TEST(write_calls_bcm_write);
  TEST(erase_calls_bcm_write);
  END();
}
