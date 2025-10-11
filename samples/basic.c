#define JEUNIT_IMPLEMENTATION
#include "jeunit.h"

TEST(test_addition) {
  int a = 2 + 2;
  ASSERT_EQ(4, a);
  return 0;
}

TEST_SKIP(test_subtraction) {
  int a = 5 - 3;
  ASSERT_EQ(2, a);
  return 0;
}

TEST(test_multiply) {
  int a = 3 * 3;
  ASSERT_EQ(9, a);
  return 0;
}

TEST_XFAIL(test_divide_by_zero) {
  int a = 1;
  int b = 0;
  if (b == 0) FAIL();
  ASSERT_EQ(0, a / b);
  return 0;
}

TEST_XFAIL(test_equals_zero) {
  int a = 1;
  int b = 0;
  ASSERT_EQ(0, a - 1);
  return 0;
}

int main(int argc, char const* argv[]) {
  JEUNIT_RUN_MAIN(argc, argv);
  return 0;
};
