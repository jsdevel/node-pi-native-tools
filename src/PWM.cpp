/* 
 * File:   PWM.cpp
 * Author: joseph
 * 
 * Created on January 16, 2014, 1:15 AM
 */

extern "C" {
#include <bcm2835.h>
}

#include "PWM.h"
#include "Exceptions.h"


PWM::PWM(int pin) {
  maxDownTime = 35;
  downTime = maxDownTime;
  dutyTime = 10;
  minDownTime = 0;
  upTime = 1;
  shouldStop = false;

  switch(pin){
    case 3: rpi_pin = RPI_V2_GPIO_P1_03;break;
    case 5: rpi_pin = RPI_V2_GPIO_P1_05;break;
    case 7: rpi_pin = RPI_V2_GPIO_P1_07;break;
    case 8: rpi_pin = RPI_V2_GPIO_P1_08;break;
    case 10: rpi_pin = RPI_V2_GPIO_P1_10;break;
    case 11: rpi_pin = RPI_V2_GPIO_P1_11;break;
    case 12: rpi_pin = RPI_V2_GPIO_P1_12;break;
    case 13: rpi_pin = RPI_V2_GPIO_P1_13;break;
    case 15: rpi_pin = RPI_V2_GPIO_P1_15;break;
    case 16: rpi_pin = RPI_V2_GPIO_P1_16;break;
    case 18: rpi_pin = RPI_V2_GPIO_P1_18;break;
    case 19: rpi_pin = RPI_V2_GPIO_P1_19;break;
    case 21: rpi_pin = RPI_V2_GPIO_P1_21;break;
    case 22: rpi_pin = RPI_V2_GPIO_P1_22;break;
    case 23: rpi_pin = RPI_V2_GPIO_P1_23;break;
    case 24: rpi_pin = RPI_V2_GPIO_P1_24;break;
    case 26: rpi_pin = RPI_V2_GPIO_P1_26;break;
    default:
      throw Exceptions::UNKNOWN_GPIO_PORT;
  }

  bcm2835_gpio_fsel(rpi_pin, BCM2835_GPIO_FSEL_OUTP);
}


void PWM::start(){
  std::thread d(&PWM::run, this);    
  d.detach();
  t = &d;
}

void PWM::pause(){
  mtx.lock();
}

void PWM::resume(){
  mtx.unlock();
}

void PWM::stop(){
  shouldStop = true;
}

void PWM::run() {
  while (1) {
    if(shouldStop){
      break;
    }
    mtx.lock();
    // Turn it on
    bcm2835_gpio_write(rpi_pin, 1);

    // wait a bit
    bcm2835_delay(upTime);

    // turn it off
    bcm2835_gpio_write(rpi_pin, 0);

    // wait a bit
    bcm2835_delay(downTime);
    mtx.unlock();
  }
}