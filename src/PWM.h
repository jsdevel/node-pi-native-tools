/* 
 * File:   PWM.h
 * Author: joseph
 *
 * Created on January 16, 2014, 1:15 AM
 */



#include <thread>
#include <mutex>

#ifndef PWM_H
#define	PWM_H

class PWM {
protected:
  std::mutex mtx;
  bool shouldStop;
  std::thread * t;
  int rpi_pin;

public:
  volatile int downTime;
  volatile int dutyTime;
  volatile int maxDownTime;
  volatile int minDownTime;
  volatile int upTime;

  PWM(int pin);

  void pause();
  void resume();
  void run();
  void start();
  void stop();
};

#endif	/* PWM_H */

