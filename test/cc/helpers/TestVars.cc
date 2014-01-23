#include "../helpers/TestVars.h"

void TestVars::reset(){
  currentPin = 0;
  currentValue = 0;
  erase_write = 0;
  output_write = 0;
}

TestVars TEST_VARS = TestVars::getInstance();