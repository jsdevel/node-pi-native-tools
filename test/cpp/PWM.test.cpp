#include <cstdio>
#include <iostream>
#include "helpers/assert.h"
#include "../../src/cpp/PWM.h"

using namespace std;

namespace test {

  void valid_pins_for_constructor_throw_no_error(){
    int pins [17] = {3, 5, 7, 8, 10, 11, 12, 13, 15, 16, 18, 19, 21, 22, 23, 24, 26};
    for(int i = 0;i<17;i++){
      PWM pwm(pins[i], 0, 1);
    }
  }

  void invalid_pins_for_constructor_throw_error(){
    int pins [5] = {1, 2, 0, 40, 50};
    bool hadException = false;
    for(int i = 0;i<5;i++){
      try {
        PWM pwm(pins[i], 0, 1);
        printf("didn't throw for: %i", pins[i]);
        hadException = true;
      } catch(...){
        continue;
      }
    }
    assert(!hadException);
  }
}

int main(){
  TEST(valid_pins_for_constructor_throw_no_error);
  TEST(invalid_pins_for_constructor_throw_error);
}
