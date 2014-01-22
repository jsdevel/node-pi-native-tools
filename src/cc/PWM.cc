/* 
 * File:   PWM.cpp
 * Author: joseph
 * 
 * Created on January 16, 2014, 1:15 AM
 */

extern "C" {
#include "./bcm2835.h"
}

#include <iostream>
#include "GPIOOutput.h"
#include "PWM.h"
#include "Exceptions.h"

using namespace std;

PWM::PWM (
  GPIOOutput * _gpio,
  unsigned int dutyCycle,
  unsigned int interval
) {
  gpio = _gpio;
  t = 0;

  setDutyCycle(dutyCycle);
  setInterval(interval);
}

unsigned int PWM::getDutyCycle(){
  return dutyCycle;
}

unsigned int PWM::getInterval(){
  return interval;
}

void PWM::setDutyCycle(unsigned int dutyCycle){
  if(dutyCycle > 100){
    dutyCycle = 100;
  }

  this->dutyCycle = dutyCycle;
}

void PWM::setInterval(unsigned int interval){
  if(interval == 0){
    throw Exceptions::BAD_PWM_INTERVAL;
  }
  this->interval = interval;
}

int PWM::start(){
  shouldStop = false;
  if(t)return 0;
  std::thread d(&PWM::run, this);    
  d.detach();
  t = &d;
  return 1;
}

void PWM::pause(){
  mtx.lock();
}

void PWM::resume(){
  mtx.unlock();
}

void PWM::stop(){
  shouldStop = true;
  this->pause();
  this->resume();
  t = 0;
}

void PWM::run() {
  while (1) {
    if(shouldStop){
      break;
    }
    mtx.lock();

    int onTime = interval * dutyCycle / 100;
    int offTime = interval - onTime;

    gpio->write();

    // wait a bit
    bcm2835_delay(onTime);

    // turn it off
    gpio->erase();

    // wait a bit
    bcm2835_delay(offTime);
    mtx.unlock();
  }
}