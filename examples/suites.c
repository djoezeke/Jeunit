#define JEUNIT_IMPLEMENTATION
#include "../jeunit.h"

/**
 * Define a test function.
 */
TEST(testFunction1){
    // skip("Test is empty");
};

TEST(testFunction2)
{
    assertEqual(23, 23);
    assertNotEqual(23, 23);
};

TEST(testFunction3)
{
    printf("Hello World\n");
    assertGreater(24, 19);
};

/**
 * Define a test suite.
 */
TEST_SUITE(testSuite1){

    /**< Add test to testsuite */
    AddTest(testFunction1),
    AddTest(testFunction2),

    /**< End The Suite List */
    END_SUITE /**< End Suite */
};

/**
 * Another test suite.
 */
TEST_SUITE(testSuite2){

    /**< Add test to testsuite */
    AddTest(testFunction3),

    /**< End The Suite List */
    END_SUITE /**< End Suite */
};

/**
 * Add suites to test.
 */
JEUNIT_SUITES{

    AddSuite(testSuite1),
    AddSuite(testSuite2),

    /**< End The Suite List */
    SUITES_END /**< End Suites */
};

int main(int argc, char *argv[])
{
    JEUNIT_RUN_MAIN(argc, argv);

    JeunitRunTest(testFunction2);
    JeunitRunTest(testFunction3);
    JeunitRunSuite(testSuite2);
};
