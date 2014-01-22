/* 
 * File:   PWM.h
 * Author: joseph
 *
 * Created on January 16, 2014, 1:15 AM
 */



#include <thread>
#include <mutex>
#include "GPIOOutput.h"

class PWM {
protected:
  std::mutex mtx;
  bool shouldStop;
  std::thread * t;
  GPIOOutput * gpio;
  volatile unsigned int dutyCycle;
  volatile unsigned int interval;

public:
  PWM(
    GPIOOutput * gpio,
    unsigned int dutyCycle,
    unsigned int interval
  );

  unsigned int getDutyCycle();
  unsigned int getInterval();
  void setDutyCycle(unsigned int dutyCycle);
  void setInterval(unsigned int interval);
  void pause();
  void resume();
  void run();
  int start();
  void stop();
};