#include "../../../src/cc/GPIO.h"
#include "../../../src/cc/GPIOOutput.h"
#include "../helpers/test-ns.h"

GPIOOutput::GPIOOutput(int pin):GPIO(pin, 1){};

void GPIOOutput::erase(){
  test::__output_erasures += 1;
};

void GPIOOutput::write(){
  test::__output_writes += 1;
};