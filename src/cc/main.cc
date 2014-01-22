/* 
 * File:   main.cpp
 * Author: joseph
 *
 * Created on January 9, 2014, 11:43 PM
 */

#include <iostream>
#include <stdio.h>
#include <signal.h>
#include "GPIOOutput.h"
#include "PWM.h"

using namespace std;

extern "C" {
#include <bcm2835.h>
}

void cleanup(int signal) {
  bcm2835_close();
  //printf("Closing the application on signal '%i'", signal);
}

/*
 * 
 */
int main(int argc, char** argv) {
  int i = 0;
  struct sigaction terminationHandler;
  terminationHandler.sa_handler = cleanup;

  sigaction(SIGABRT, &terminationHandler, 0);
  sigaction(SIGBUS, &terminationHandler, 0);
  sigaction(SIGINT, &terminationHandler, 0);
  sigaction(SIGQUIT, &terminationHandler, 0);
  sigaction(SIGTERM, &terminationHandler, 0);

  // If you call this, it will not actually access the GPIO
  // Use for testing
  //    bcm2835_set_debug(1);
  if (!bcm2835_init())return 1;


  int direction = 1;

  GPIOOutput gpio(12);
  PWM pwm(gpio, 0, 15);

  pwm.start();

  while (1) {
    if (direction == 1) {
      pwm.setDutyCycle(pwm.getDutyCycle() + 1);
    } else {
      pwm.setDutyCycle(pwm.getDutyCycle() - 1);
    }

    if (pwm.getDutyCycle() == 100) {
      direction = 0;
    } else if (pwm.getDutyCycle() == 0) {
      direction = 1;
    }

    bcm2835_delay(10);
  }

  pwm.stop();

  bcm2835_close();
  return 0;
}