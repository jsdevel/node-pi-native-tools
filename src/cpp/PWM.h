/* 
 * File:   PWM.h
 * Author: joseph
 *
 * Created on January 16, 2014, 1:15 AM
 */



#include <thread>
#include <mutex>

class PWM {
protected:
  std::mutex mtx;
  bool shouldStop;
  std::thread * t;
  int rpi_pin;
  volatile unsigned int dutyCycle;
  volatile unsigned int interval;

public:

  PWM(
    unsigned int pin,
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
  void start();
  void stop();
};