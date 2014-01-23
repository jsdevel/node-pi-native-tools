#include "../../../src/cc/GPIO.h"
#include "../../../src/cc/GPIOOutput.h"
#include "../helpers/TestVars.h"

extern TestVars TEST_VARS;

GPIOOutput::GPIOOutput(int pin):GPIO(pin, 1){};

void GPIOOutput::erase(){
  TEST_VARS.erase_write += 1;
};

void GPIOOutput::write(){
  TEST_VARS.output_write += 1;
};