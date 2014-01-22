#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "../../src/cc/GPIOOutput.h"
#include "../../src/cc/PWM.h"
#include "helpers/test-ns.h"

using namespace std;

#define USE_BEFORE 1
#define USE_AFTER 1
#include "helpers/assert.h"
namespace test {
  int __output_erasures;
  int __output_writes;

  GPIOOutput * gpio;
  PWM * pwm;

  void before(){
    __output_erasures = 0;
    __output_writes = 0;
    gpio = new GPIOOutput(5);
    pwm = new PWM(gpio, 90, 4000);
  }

  void after(){
    pwm->stop();
    delete pwm;
    delete gpio;
  }

  void constructor_sets_duty_cycle_to_100_if_over_100(){
    pwm = new PWM(new GPIOOutput(12), 150, 10);
    assert(pwm->getDutyCycle() == 100);
  }

  void constructor_throws_if_interval_is_0(){
    try {
      pwm = new PWM(new GPIOOutput(12), 50, 0);
      fail("no error thrown");
    } catch(...){}
  }

  void get_duty_cycle_returns_duty_cycle(){
    assert(pwm->getDutyCycle() == 90);
  }

  void get_interval_returns_interval(){
    assert(pwm->getInterval() == 4000);
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

  void starting_returns_success(){
    assert(pwm->start());
  }

  void stopping(){
    assert(pwm->start());
    pwm->stop();
  }

  void starting_multiple_times(){
    assert(pwm->start());
    assert(!pwm->start());
  }

  void starting_stopping_starting_returns_success(){
    assert(pwm->start());
    pwm->stop();
    assert(pwm->start());
  }

  void a_running_pwm_writes_to_the_pin(){
    pwm->start();
    sleep(2);
    assert(test::__output_writes > 0);
  }
 
  void no_write_to_pin_when_pwm_not_running(){
    assert(test::__output_writes == 0);
  }
}

int main(){
  SUITE();
  TEST(constructor_sets_duty_cycle_to_100_if_over_100);
  TEST(constructor_throws_if_interval_is_0);
  TEST(get_duty_cycle_returns_duty_cycle);
  TEST(get_interval_returns_interval);
  TEST(set_duty_cycle_to_value_greater_than_100_returns_100);
  TEST(set_interval_to_0_results_in_error);
  TEST(starting_returns_success);
  TEST(stopping);
  TEST(starting_multiple_times);
  TEST(starting_stopping_starting_returns_success);
  TEST(a_running_pwm_writes_to_the_pin);
  TEST(no_write_to_pin_when_pwm_not_running);
  END();
}
