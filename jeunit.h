/* -*- C++ -*- compatibility header. */

/**
 *
 * Index of this file:
 *
 *  [SECTION] Header mess
 *  [SECTION] Configurable macros
 *  [SECTION] Platform Defines
 *  [SECTION] Compiler Defines
 *  [SECTION] Compiler Warnings
 *  [SECTION] Imports/Exports
 *  [SECTION] Data Structures
 *  [SECTION] C Only Functions
 *  [SECTION] C++ Only Classes
 *
 * JEUNIT_IMPLEMENTATION
 *
 *  Internal:
 *
 *  [SECTION] Macro Defines
 *  [SECTION] Data Structures
 *  [SECTION] C Only Functions
 *    - [SECTION] Declarations
 *    - [SECTION] Definations
 *  [SECTION] C++ Only Classes
 *    - [SECTION] Declarations
 *    - [SECTION] Definations
 *
 *  Jeunit:
 *
 *  [SECTION] C Only Functions
 *  [SECTION] C++ Only Classes
 *
 *
 * Resources:
 * - Homepage ................... https://github.com/djoezeke/jeunit
 * - Releases & changelog ....... https://github.com/djoezeke/jeunit/releases
 * - Issues & support ........... https://github.com/djoezeke/jeunit/issues
 *
 */

#ifndef JEUNIT_H
#define JEUNIT_H

/**
 * @defgroup version Version Information
 * @brief Macros for library versioning.
 * @{
 */

/**
 * @def JEUNIT_VERSION_MAJOR
 * @brief Major version number of the library.
 */
#define JEUNIT_VERSION_MAJOR 0

/**
 * @def JEUNIT_VERSION_MINOR
 * @brief Minor version number of the library.
 */
#define JEUNIT_VERSION_MINOR 1

/**
 * @def JEUNIT_VERSION_PATCH
 * @brief Patch version number of the library.
 */
#define JEUNIT_VERSION_PATCH 0

/**
 * @def JEUNIT_VERSION
 * @brief Library version string in the format @c "X.Y.Z",
 * where @c X is the major version number, @c Y is a minor version
 * number, and @c Z is the patch version number.
 */
#define JEUNIT_VERSION "0.1.0"

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Header mess
//-----------------------------------------------------------------------------

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>   // for printf
#include <stdlib.h>  // for realloc
#include <string.h>  // for strdup strlen
#include <time.h>
#include <unistd.h>

#ifdef __cplusplus

#include <exception>
#include <iostream>
#include <unordered_map>

#endif  //__cplusplus

#ifdef JEUNIT_TESTS
#endif  // JEUNIT_TESTS

//-----------------------------------------------------------------------------
// [SECTION] Platform
//-----------------------------------------------------------------------------

/**
 * @defgroup platform Platform Definitions
 * @{
 */

/**
 * @brief   Checks if the compiler is of given brand.
 * @param   name Platform, like `APPLE`.
 * @retval  true   It is.
 * @retval  false  It isn't.
 */
#define JEUNIT_PLATFORM_IS(name) JEUNIT_PLATFORM_IS_##name

/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */

#ifdef __APPLE__
/**
 * A preprocessor macro that is only defined if compiling for MacOS.
 */
#define JEUNIT_PLATFORM_IS_APPLE 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define JEUNIT_PLATFORM_NAME_IS "Apple"
#elif defined(linux) || defined(__linux) || defined(__linux__)
/**
 * A preprocessor macro that is only defined if compiling for Linux.
 */
#define JEUNIT_PLATFORM_IS_LINUX 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define JEUNIT_PLATFORM_NAME_IS "Linux"
#elif defined(WIN32) || defined(__WIN32__) || defined(_WIN32) || \
    defined(_MSC_VER) || defined(__MINGW32__)
/**
 * A preprocessor macro that is only defined if compiling for Windows.
 */
#define JEUNIT_PLATFORM_IS_WINDOWS 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define JEUNIT_PLATFORM_NAME_IS "Windows"
#else
/**
 * A preprocessor macro that is only defined if compiling for others.
 */
#define JEUNIT_PLATFORM_IS_OTHERS 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define JEUNIT_PLATFORM_NAME_IS "Others"
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Compiler
//-----------------------------------------------------------------------------

/**
 * @defgroup compiler Compiler Definitions
 * @{
 */

/**
 * @brief   Checks if the compiler is of given brand.
 * @param   name  Compiler brand, like `MSVC`.
 * @retval  true   It is.
 * @retval  false  It isn't.
 */
#define JEUNIT_COMPILER_IS(name) JEUNIT_COMPILER_IS_##name

/// Compiler is apple
#if !defined(__clang__)
#define JEUNIT_COMPILER_IS_APPLE 0
#elif !defined(__apple_build_version__)
#define JEUNIT_COMPILER_IS_APPLE 0
#else
#define JEUNIT_COMPILER_IS_APPLE 1
#define JEUNIT_COMPILER_VERSION_MAJOR __clang_major__
#define JEUNIT_COMPILER_VERSION_MINOR __clang_minor__
#define JEUNIT_COMPILER_VERSION_PATCH __clang_patchlevel__
#endif

/// Compiler is clang
#if !defined(__clang__)
#define JEUNIT_COMPILER_IS_CLANG 0
#elif JEUNIT_COMPILER_IS(APPLE)
#define JEUNIT_COMPILER_IS_CLANG 0
#else
#define JEUNIT_COMPILER_IS_CLANG 1
#define JEUNIT_COMPILER_VERSION_MAJOR __clang_major__
#define JEUNIT_COMPILER_VERSION_MINOR __clang_minor__
#define JEUNIT_COMPILER_VERSION_PATCH __clang_patchlevel__
#endif

/// Compiler is intel
#if !defined(__INTEL_COMPILER)
#define JEUNIT_COMPILER_IS_INTEL 0
#elif !defined(__INTEL_COMPILER_UPDATE)
#define JEUNIT_COMPILER_IS_INTEL 1
/* __INTEL_COMPILER = XXYZ */
#define JEUNIT_COMPILER_VERSION_MAJOR (__INTEL_COMPILER / 100)
#define JEUNIT_COMPILER_VERSION_MINOR (__INTEL_COMPILER % 100 / 10)
#define JEUNIT_COMPILER_VERSION_PATCH (__INTEL_COMPILER % 10)
#else
#define JEUNIT_COMPILER_IS_INTEL 1
/* __INTEL_COMPILER = XXYZ */
#define JEUNIT_COMPILER_VERSION_MAJOR (__INTEL_COMPILER / 100)
#define JEUNIT_COMPILER_VERSION_MINOR (__INTEL_COMPILER % 100 / 10)
#define JEUNIT_COMPILER_VERSION_PATCH __INTEL_COMPILER_UPDATE
#endif

/// Compiler is msc
#if !defined(_MSC_VER)
#define JEUNIT_COMPILER_IS_MSVC 0
#elif JEUNIT_COMPILER_IS(CLANG)
#define JEUNIT_COMPILER_IS_MSVC 0
#elif JEUNIT_COMPILER_IS(INTEL)
#define JEUNIT_COMPILER_IS_MSVC 0
#elif _MSC_VER >= 1400
#define JEUNIT_COMPILER_IS_MSVC 1
/* _MSC_FULL_VER = XXYYZZZZZ */
#define JEUNIT_COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 10000000)
#define JEUNIT_COMPILER_VERSION_MINOR (_MSC_FULL_VER % 10000000 / 100000)
#define JEUNIT_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 100000)
#elif defined(_MSC_FULL_VER)
#define JEUNIT_COMPILER_IS_MSVC 1
/* _MSC_FULL_VER = XXYYZZZZ */
#define JEUNIT_COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 1000000)
#define JEUNIT_COMPILER_VERSION_MINOR (_MSC_FULL_VER % 1000000 / 10000)
#define JEUNIT_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 10000)
#else
#define JEUNIT_COMPILER_IS_MSVC 1
/* _MSC_VER = XXYY */
#define JEUNIT_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
#define JEUNIT_COMPILER_VERSION_MINOR (_MSC_VER % 100)
#define JEUNIT_COMPILER_VERSION_PATCH 0
#endif

/// Compiler is gcc
#if !defined(__GNUC__)
#define JEUNIT_COMPILER_IS_GCC 0
#elif JEUNIT_COMPILER_IS(APPLE)
#define JEUNIT_COMPILER_IS_GCC 0
#elif JEUNIT_COMPILER_IS(CLANG)
#define JEUNIT_COMPILER_IS_GCC 0
#elif JEUNIT_COMPILER_IS(INTEL)
#define JEUNIT_COMPILER_IS_GCC 0
#else
#define JEUNIT_COMPILER_IS_GCC 1
#define JEUNIT_COMPILER_VERSION_MAJOR __GNUC__
#define JEUNIT_COMPILER_VERSION_MINOR __GNUC_MINOR__
#define JEUNIT_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Warnings
//-----------------------------------------------------------------------------

/**
 * @defgroup compiler Compiler Warnings
 * @{
 */

#if JEUNIT_COMPILER_IS(CLANG)
#define JEUNIT_PRAGMA_TO_STR(x) _Pragma(#x)
#define JEUNIT_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
#define JEUNIT_CLANG_SUPPRESS_WARNING(w) \
  JEUNIT_PRAGMA_TO_STR(clang diagnostic ignored w)
#define JEUNIT_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
#define JEUNIT_CLANG_SUPPRESS_WARNING_WITH_PUSH(w) \
  JEUNIT_CLANG_SUPPRESS_WARNING_PUSH JEUNIT_CLANG_SUPPRESS_WARNING(w)
#else  // JEUNIT_CLANG
#define JEUNIT_CLANG_SUPPRESS_WARNING_PUSH
#define JEUNIT_CLANG_SUPPRESS_WARNING(w)
#define JEUNIT_CLANG_SUPPRESS_WARNING_POP
#define JEUNIT_CLANG_SUPPRESS_WARNING_WITH_PUSH(w)
#endif  // JEUNIT_CLANG

#if JEUNIT_COMPILER_IS(GCC)
#define JEUNIT_PRAGMA_TO_STR(x) _Pragma(#x)
#define JEUNIT_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
#define JEUNIT_GCC_SUPPRESS_WARNING(w) \
  JEUNIT_PRAGMA_TO_STR(GCC diagnostic ignored w)
#define JEUNIT_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
#define JEUNIT_GCC_SUPPRESS_WARNING_WITH_PUSH(w) \
  JEUNIT_GCC_SUPPRESS_WARNING_PUSH JEUNIT_GCC_SUPPRESS_WARNING(w)
#else  // JEUNIT_GCC
#define JEUNIT_GCC_SUPPRESS_WARNING_PUSH
#define JEUNIT_GCC_SUPPRESS_WARNING(w)
#define JEUNIT_GCC_SUPPRESS_WARNING_POP
#define JEUNIT_GCC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif  // JEUNIT_GCC

#if JEUNIT_COMPILER_IS(MSVC)
#define JEUNIT_MSVC_SUPPRESS_WARNING_PUSH __pragma(warning(push))
#define JEUNIT_MSVC_SUPPRESS_WARNING(w) __pragma(warning(disable : w))
#define JEUNIT_MSVC_SUPPRESS_WARNING_POP __pragma(warning(pop))
#define JEUNIT_MSVC_SUPPRESS_WARNING_WITH_PUSH(w) \
  JEUNIT_MSVC_SUPPRESS_WARNING_PUSH JEUNIT_MSVC_SUPPRESS_WARNING(w)
#else  // JEUNIT_MSVC
#define JEUNIT_MSVC_SUPPRESS_WARNING_PUSH
#define JEUNIT_MSVC_SUPPRESS_WARNING(w)
#define JEUNIT_MSVC_SUPPRESS_WARNING_POP
#define JEUNIT_MSVC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif  // JEUNIT_MSVC

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Import/Export
//-----------------------------------------------------------------------------

/**
 * @defgroup export Export Definitions
 * @{
 */

#if defined(_WIN32)
#define JEUNIT_NO_EXPORT_ATTR
#define JEUNIT_API_EXPORT __declspec(dllexport)
#define JEUNIT_API_IMPORT __declspec(dllimport)
#define JEUNIT_DEPRECATED_ATTR __declspec(deprecated)
#else  // _WIN32
#define JEUNIT_API_EXPORT __attribute__((visibility("default")))
#define JEUNIT_API_IMPORT __attribute__((visibility("default")))
#define JEUNIT_NO_EXPORT_ATTR __attribute__((visibility("hidden")))
#define JEUNIT_DEPRECATED_ATTR __attribute__((__deprecated__))
#endif  // _WIN32

/**
 * @def JEUNIT_API
 * @brief Macro for public API symbol export/import.
 * @details Use this macro to annotate all public API functions for correct
 * symbol visibility on all platforms.
 */

#if defined(JEUNIT_BUILD_STATIC)
#define JEUNIT_API
#elif defined(JEUNIT_BUILD_SHARED)
/* We are building this library */
#define JEUNIT_API JEUNIT_API_EXPORT
#elif defined(JEUNIT_IMPORT)
/* We are using this library */
#define JEUNIT_API JEUNIT_API_IMPORT
#else  // JEUNIT_BUILD_STATIC
#define JEUNIT_API
#endif  // JEUNIT_BUILD_STATIC

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Macros
//-----------------------------------------------------------------------------

#define _DECLARE_TEST(test_name)     \
  JEUNIT_CLANG_SUPPRESS_WARNING_PUSH \
  JEUNIT_MSVC_SUPPRESS_WARNING_PUSH  \
  JEUNIT_GCC_SUPPRESS_WARNING_PUSH   \
  int test_name(void);               \
  JEUNIT_GCC_SUPPRESS_WARNING_POP    \
  JEUNIT_MSVC_SUPPRESS_WARNING_POP   \
  JEUNIT_CLANG_SUPPRESS_WARNING_POP

#define _REGISTER_TEST(test_name, skip_flag, xfail_flag)                  \
  do {                                                                    \
    JeunitTestCase_t tc = {test_name, #test_name, skip_flag, xfail_flag}; \
    if (test_count < MAX_TESTS) {                                         \
      test_cases[test_count] = tc;                                        \
      test_count++;                                                       \
    }                                                                     \
  } while (0)

#define _CONSTRUCT_TEST(test_name, skip_flag, xfail_flag)      \
  __attribute__((constructor)) static void reg_##test_name() { \
    _REGISTER_TEST(test_name, skip_flag, xfail_flag);          \
  };

#define _DEFINE_TEST(test_name) int test_name(void)

#define _MAKE_TEST(test_name, skip_flag, xfail_flag) \
  _DECLARE_TEST(test_name)                           \
  _CONSTRUCT_TEST(test_name, skip_flag, xfail_flag)  \
  _DEFINE_TEST(test_name)

#define _NEW_TEST(test_name, skip_flag, xfail_flag) \
  _MAKE_TEST(test_name, skip_flag, xfail_flag)

#define _TEST(name) _NEW_TEST(name, 0, 0)
#define TEST(name) _TEST(name)

#define _TEST_SKIP(name) _NEW_TEST(name, 1, 0)
#define TEST_SKIP(name) _TEST_SKIP(name)

#define _TEST_XFAIL(name) _NEW_TEST(name, 0, 1)
#define TEST_XFAIL(name) _TEST_XFAIL(name)

#define FAIL()                                                               \
  do {                                                                       \
    printf("    \033[31mFAIL called\033[0m at %s:%d\n", __FILE__, __LINE__); \
    return 1;                                                                \
  } while (0)

#define SKIP()                                                               \
  do {                                                                       \
    printf("    \033[33mSKIP called\033[0m at %s:%d\n", __FILE__, __LINE__); \
    return 99;                                                               \
  } while (0)

#define ASSERT_EQ(expected, actual)                                       \
  if ((expected) != (actual)) {                                           \
    printf(                                                               \
        "    \033[31mASSERT_EQ failed\033[0m at %s:%d: Expected %d, got " \
        "%d\n",                                                           \
        __FILE__, __LINE__, (expected), (actual));                        \
    return 1;                                                             \
  }

#define CHECK(expr)
#define REQUIRE(expr)
#define SECTION(name)

#define JeunitRunTestCase(name) _JeunitRunTestFunc(#name, name);
#define JeunitRunTestSuite(name) _JeunitRunTestSuite(#name, test_suite_##name);

#define JEUNIT_RUN_MAIN(argc, argv) JeunitRunMain(argc, argv)

#define safe_repr(x) #x

#define expectedFailure
#define expectedSuccess

#define unexpectedFailure
#define unexpectedSuccess

#define JEUNIT_MESSAGE_LENGHT 50

#define skip_(format, ...)        \
  do {                            \
    _JeunitSkipTest(__VA_ARGS__); \
    return;                       \
  } while (0)

#define skipIf_(condition, format, ...) \
  do {                                  \
    if ((condition)) {                  \
      skip_(format, __VA_ARGS__);       \
    }                                   \
  } while (0)

#define skipUnless_(condition, format, ...) \
  do {                                      \
    if (!(condition)) {                     \
      skip_(format, __VA_ARGS__);           \
    }                                       \
  } while (0)

#define fail_(format, ...)                                                 \
  do {                                                                     \
    char _jeunit_message[JEUNIT_MESSAGE_LENGHT];                           \
    snprintf(_jeunit_message, JEUNIT_MESSAGE_LENGHT, format, __VA_ARGS__); \
    _JeunitFailureAssertion(__FILE__, __LINE__, _jeunit_message);          \
    return;                                                                \
  } while (0)

#define xfail_(format, ...)                                                \
  do {                                                                     \
    char _jeunit_message[JEUNIT_MESSAGE_LENGHT];                           \
    snprintf(_jeunit_message, JEUNIT_MESSAGE_LENGHT, format, __VA_ARGS__); \
    _JeunitFailureAssertion(__FILE__, __LINE__, _jeunit_message);          \
    return;                                                                \
  } while (0)

#define assertTrue_(expr, format, ...)                                       \
  do {                                                                       \
    if (!(expr)) {                                                           \
      char _jeunit_message[JEUNIT_MESSAGE_LENGHT];                           \
      snprintf(_jeunit_message, JEUNIT_MESSAGE_LENGHT, format, __VA_ARGS__); \
      _JeunitFailureAssertion(__FILE__, __LINE__, _jeunit_message);          \
    }                                                                        \
  } while (0)

#define assertFalse_(expr, format, ...)                                      \
  do {                                                                       \
    if ((expr)) {                                                            \
      char _jeunit_message[JEUNIT_MESSAGE_LENGHT];                           \
      snprintf(_jeunit_message, JEUNIT_MESSAGE_LENGHT, format, __VA_ARGS__); \
      _JeunitFailureAssertion(__FILE__, __LINE__, _jeunit_message);          \
    }                                                                        \
  } while (0)

#define assertIsNull_(expr, format, ...)                                     \
  do {                                                                       \
    if (!((expr) == NULL)) {                                                 \
      char _jeunit_message[JEUNIT_MESSAGE_LENGHT];                           \
      snprintf(_jeunit_message, JEUNIT_MESSAGE_LENGHT, format, __VA_ARGS__); \
      _JeunitFailureAssertion(__FILE__, __LINE__, _jeunit_message);          \
    }                                                                        \
  } while (0)

#define assertIsNotNull_(expr, format, ...)                                  \
  do {                                                                       \
    if (((expr) == NULL)) {                                                  \
      char _jeunit_message[JEUNIT_MESSAGE_LENGHT];                           \
      snprintf(_jeunit_message, JEUNIT_MESSAGE_LENGHT, format, __VA_ARGS__); \
      _JeunitFailureAssertion(__FILE__, __LINE__, _jeunit_message);          \
    }                                                                        \
  } while (0)

#define assertEqual_(first, second, format, ...)                             \
  do {                                                                       \
    if (!((first) == (second))) {                                            \
      char _jeunit_message[JEUNIT_MESSAGE_LENGHT];                           \
      snprintf(_jeunit_message, JEUNIT_MESSAGE_LENGHT, format, __VA_ARGS__); \
      _JeunitFailureAssertion(__FILE__, __LINE__, _jeunit_message);          \
    }                                                                        \
  } while (0)

#define assertNotEqual_(first, second, format, ...)                          \
  do {                                                                       \
    if (((first) == (second))) {                                             \
      char _jeunit_message[JEUNIT_MESSAGE_LENGHT];                           \
      snprintf(_jeunit_message, JEUNIT_MESSAGE_LENGHT, format, __VA_ARGS__); \
      _JeunitFailureAssertion(__FILE__, __LINE__, _jeunit_message);          \
    } else {                                                                 \
    }                                                                        \
  } while (0)

#define assertLess_(first, second, format, ...)                              \
  do {                                                                       \
    if (!((first) < (second))) {                                             \
      char _jeunit_message[JEUNIT_MESSAGE_LENGHT];                           \
      snprintf(_jeunit_message, JEUNIT_MESSAGE_LENGHT, format, __VA_ARGS__); \
      _JeunitFailureAssertion(__FILE__, __LINE__, _jeunit_message);          \
    }                                                                        \
  } while (0)

#define assertLessEqual_(first, second, format, ...)                         \
  do {                                                                       \
    if (!((first) <= (second))) {                                            \
      char _jeunit_message[JEUNIT_MESSAGE_LENGHT];                           \
      snprintf(_jeunit_message, JEUNIT_MESSAGE_LENGHT, format, __VA_ARGS__); \
      _JeunitFailureAssertion(__FILE__, __LINE__, _jeunit_message);          \
    }                                                                        \
  } while (0)

#define assertGreater_(first, second, format, ...)                           \
  do {                                                                       \
    if (!((first) > (second))) {                                             \
      char _jeunit_message[JEUNIT_MESSAGE_LENGHT];                           \
      snprintf(_jeunit_message, JEUNIT_MESSAGE_LENGHT, format, __VA_ARGS__); \
      _JeunitFailureAssertion(__FILE__, __LINE__, _jeunit_message);          \
    }                                                                        \
  } while (0)

#define assertGreaterEqual_(first, second, format, ...)                      \
  do {                                                                       \
    if (!((first) >= (second))) {                                            \
      char _jeunit_message[JEUNIT_MESSAGE_LENGHT];                           \
      snprintf(_jeunit_message, JEUNIT_MESSAGE_LENGHT, format, __VA_ARGS__); \
      _JeunitFailureAssertion(__FILE__, __LINE__, _jeunit_message);          \
    }                                                                        \
  } while (0)

#define fail(message) fail_("%s", message)

#define xfail(message) xfail_("%s", message)

// Unconditionally skip a test.
#define skip(reason) skip_("%s", reason)

// Skip a test if the condition is true.
#define skipIf(condition, reason) skipIf_(condition, "%s", reason)

// Skip a test unless the condition is true.
#define skipUnless(condition, reason) skipUnless_(condition, "%s", reason)

// Check that the expression is true.
#define assertTrue(expr) assertTrue_(expr, "%s is not true", safe_repr(expr))

// Check that the expression is false.
#define assertFalse(expr) assertFalse_(expr, "%s is not false", safe_repr(expr))

// Check that the expression is NULL.
#define assertIsNull(expr) \
  assertIsNull_(expr, "%s is not NULL", safe_repr(expr))

// Check that the expression is not NULL.
#define assertIsNotNull(expr) \
  assertIsNotNull_(expr, "%s is NULL", safe_repr(expr))

/**
 * Fail if the two objects are not equal as determined by the '==' operator.
 */
#define assertEqual(first, second) \
  assertEqual_(first, second, "%s != %s", safe_repr(first), safe_repr(second))

/**
 * Fail if the two objects are equal as determined by the '!=' operator.
 */
#define assertNotEqual(first, second)                          \
  assertNotEqual_(first, second, "%s == %s", safe_repr(first), \
                  safe_repr(second))

#define assertLess(first, second)                                     \
  assertLess_(first, second, "%s not less than %s", safe_repr(first), \
              safe_repr(second))

#define assertLessEqual(first, second)                               \
  assertLessEqual_(first, second, "%s not less than or equal to %s", \
                   safe_repr(first), safe_repr(second))

#define assertGreater(first, second)                                        \
  assertGreater_(first, second, "%s not greater than %s", safe_repr(first), \
                 safe_repr(second))

#define assertGreaterEqual(first, second)                                  \
  assertGreaterEqual_(first, second, "%s not greater than or equal to %s", \
                      safe_repr(first), safe_repr(second))

//-----------------------------------------------------------------------------
// [SECTION] Data Structures
//-----------------------------------------------------------------------------

/**
 * @defgroup basic Basic Types
 * @brief Core types and data structures for jeunit.
 * @{
 */

typedef int (*_JeunitTestFunc_t)(void);

typedef struct _JeunitTestCase_t {
  _JeunitTestFunc_t func;
  const char *name;
  int skip;
  int xfail;
} JeunitTestCase_t;

typedef struct _JeunitTestSuites_t {
  JeunitTestCase_t *cases;
  const char *name;
  int count;

} JeunitTestSuites_t;

#define MAX_TESTS 128

static JeunitTestCase_t test_cases[MAX_TESTS];
static int test_count = 0;

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

int JeunitRunMain(int argc, char *argv[]);

#ifdef __cplusplus
};
#endif  //__cplusplus

#ifdef __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

namespace jeunit {};  // namespace jeunit

#endif  //__cplusplus

#endif  // JEUNIT_H

#ifdef JEUNIT_IMPLEMENTATION

#pragma region Internal

//-----------------------------------------------------------------------------
// [SECTION] Defines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Data Structures
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] Declarations
//-----------------------------------------------------------------------------

void _JeunitAddMessage(const char *format, ...);
void _JeunitSuccessAssertion(const char *file, int line, const char *message);
void _JeunitFailureAssertion(const char *file, int line, const char *message);

static void _JeunitRunTestFunc(_JeunitTestFunc_t *test_func);
static void _JeunitRunTestCase(JeunitTestCase_t *test_case);
static void _JeunitRunTestSuite(JeunitTestSuites_t *test_suite);

static void _JeunitOutputResult(void);

//-----------------------------------------------------------------------------
// [SECTION] Definations
//-----------------------------------------------------------------------------

void _JeunitAddMessage(const char *format, ...) {};

void _JeunitSuccessAssertion(const char *file, int line, const char *message) {
};

void _JeunitFailureAssertion(const char *file, int line, const char *message) {
};

static void _JeunitRunTestFunc(_JeunitTestFunc_t *test_func) {};
static void _JeunitRunTestCase(JeunitTestCase_t *test_case) {};
static void _JeunitRunTestSuite(JeunitTestSuites_t *test_suite) {};

static void _JeunitOutputResult(void) {};

#ifdef __cplusplus
}
#endif  // __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#ifdef __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] Declarations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// [SECTION] Definations
//-----------------------------------------------------------------------------

#endif  //__cplusplus

#pragma endregion

#pragma region Jeunit

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

int JeunitRunMain(int argc, char *argv[]) {
  int total = 0, failures = 0, skipped = 0, xfailed = 0, xpassed = 0;

  printf("\n\033[1mRunning %d tests...\033[0m\n\n", test_count);

  for (int i = 0; i < test_count; ++i) {
    printf("[TEST] %s\n", test_cases[i].name);
    if (test_cases[i].skip) {
      printf("  \033[33mSKIPPED\033[0m\n");
      skipped++;
      total++;
      continue;
    }
    int result = test_cases[i].func();
    if (test_cases[i].xfail) {
      if (result != 0) {
        printf("  \033[36mXFAIL\033[0m\n");
        xfailed++;
      } else {
        printf("  \033[35mXPASS\033[0m\n");
        xpassed++;
      }
    } else if (result == 0) {
      printf("  \033[32mPASSED\033[0m\n");
    } else if (result == 99) {
      printf("  \033[33mSKIPPED\033[0m\n");
      skipped++;
    } else {
      printf("  \033[31mFAILED\033[0m\n");
      failures++;
    }
    total++;
  }
  printf(
      "\nSummary: \033[1m%d/%d passed\033[0m, \033[33m%d skipped\033[0m, "
      "\033[36m%d xfail\033[0m, \033[35m%d xpass\033[0m, \033[31m%d "
      "failed\033[0m\n",
      total - failures - xpassed - skipped, total, skipped, xfailed, xpassed,
      failures);
  return failures + xpassed;
};

#ifdef __cplusplus
};
#endif  // __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#ifdef __cplusplus

namespace jeunit {};  // namespace jeunit

#endif  //__cplusplus

#pragma endregion

#endif  // JEUNIT_IMPLEMENTATION
