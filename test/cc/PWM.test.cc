#include <cstdio>
#include <iostream>
#include "../../src/cc/PWM.h"

using namespace std;

#define USE_BEFORE 1
#define USE_AFTER 1
#include "helpers/assert.h"
namespace test {
  PWM * pwm;

  void before(){
    pwm = new PWM(5, 30, 1000);
  }

  void after(){
    pwm = 0;
  }

  void valid_pins_for_constructor_throw_no_error(){
    int pins [17] = {3, 5, 7, 8, 10, 11, 12, 13, 15, 16, 18, 19, 21, 22, 23, 24, 26};
    for(int i = 0;i<17;i++){
      PWM pwm(pins[i], 0, 1);
    }
  }

  void invalid_pins_for_constructor_throw_error(){
    int pins [5] = {1, 2, 0, 40, 50};
    for(int i = 0;i<5;i++){
      try {
        PWM pwm(pins[i], 0, 1);
        fail("didn't throw for");
      } catch(...){
        continue;
      }
    }
  }

  void get_duty_cycle_returns_duty_cycle(){
    assert(pwm->getDutyCycle() == 30);
  }

  void get_interval_returns_interval(){
    assert(pwm->getInterval() == 1000);
  }

  void set_duty_cycle_to_value_greater_than_100_returns_100(){
    pwm->setDutyCycle(200);
    assert(pwm->getDutyCycle() == 100);
  }

  void set_interval_to_0_results_in_error(){
    try {
      pwm->setInterval(0);
      fail("no error thrown");
    } catch(...){}
  }
}

int main(){
  SUITE();
  TEST(valid_pins_for_constructor_throw_no_error);
  TEST(invalid_pins_for_constructor_throw_error);
  TEST(get_duty_cycle_returns_duty_cycle);
  TEST(get_interval_returns_interval);
  TEST(set_duty_cycle_to_value_greater_than_100_returns_100);
  TEST(set_interval_to_0_results_in_error);
  END();
}
