/* 
 * File:   main.cpp
 * Author: joseph
 *
 * Created on January 9, 2014, 11:43 PM
 */

#include <stdio.h>
#include <signal.h>
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


  int direction = 0;

  PWM testThread(11);

  testThread.start();

  while (1) {
    if (direction == 1) {
      testThread.downTime = testThread.downTime + 1;
    } else {
      testThread.downTime = testThread.downTime - 1;
    }

    if (testThread.downTime == testThread.maxDownTime) {
      direction = 0;
      testThread.pause();
      bcm2835_delay(testThread.dutyTime + 1000);
      testThread.resume();
    } else if (testThread.downTime == testThread.minDownTime) {
      direction = 1;
      bcm2835_delay(testThread.dutyTime + 1000);
    } else {
      bcm2835_delay(testThread.dutyTime);
    }
  }

  testThread.stop();

  bcm2835_close();
  return 0;
}