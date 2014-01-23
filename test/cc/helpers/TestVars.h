class TestVars {
public:
  static TestVars& getInstance(){
    static TestVars instance;
    return instance;
  }
  int currentPin;
  int currentValue;
  int erase_write;
  int output_write;
  void reset();
protected:
  TestVars(){};
};