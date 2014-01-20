#define assert(cond) \
  if(!(cond)){ \
    printf("Assertion failed for: %s", #cond); \
    throw 1; \
  }

#define fail(msg)   \
  cout << "Fail: " << #msg << '\n';


#define TEST(name)                  \
  cout << " |__ " << #name << '\n'; \
  test::name();

