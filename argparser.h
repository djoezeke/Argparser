/* -*- C++ -*- compatibility header. */

/**
 * @file argparser.h
 * @brief Argument Parser Library header for C/C++.
 * @details This header provides all public API, types, macros, and configuration
 * for parsing command line argument and supports both C and C++ usage.
 * @author Sackey Ezekiel Etrue (djoezeke)
 * @date Wed 01 12:52:15 Oct GMT 2025
 * @version 0.1.0
 * @see https://www.github.com/djoezeke/argparser
 * @copyright Copyright (c) 2025 Sackey Ezekiel Etrue
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Do this:
 *  #define ARGPARSER_IMPLEMENTATION
 * before you include this file in *one* C or C++ file to create the implementation.
 *
 * i.e. it should look like this:
 *
 * #include ...
 * #include ...
 * #define ARGPARSER_IMPLEMENTATION
 * #include "argparser.h"
 *
 * Example usage:
 * @code
 * int main(int argc, char *argv[]) {
 *     Argparser *parser = new_parser("my_program", "Usage: my_program
 * [options]", "This is a sample program.", "Epilog message", 1);
 *     ArgumentParserAddArg(parser, 'o', "output", 1, 1, "default_output.txt", "Output
 * file"); ArgumentParserAddKwarg(parser, 'v', "verbose", 0, "false", "Enable verbose mode");
 *     ArgumentParserAddFlag(parser, 'h', "help", "Show help message");
 *
 *     ArgumentParserParseArgs(parser, argc, argv);
 *
 *     const char *output = ArgumentParserGetArg(parser, "output");
 *     const char *verbose = ArgumentParserGetKwarg(parser, "verbose");
 *     int help = ArgumentParserGetFlag(parser, "help");
 *
 *     if (help) {
 *         ArgumentParserPrintHelp(parser);
 *         ArgumentParserFree(parser);
 *         return 0;
 *     }
 *
 *     printf("Output: %s\n", output);
 *     printf("Verbose: %s\n", verbose);
 *
 *     ArgumentParserFree(parser);
 *     return 0;
 * }
 * @endcode
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
 * ARGPARSER_IMPLEMENTATION
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
 *  Argparser:
 *
 *  [SECTION] C Only Functions
 *  [SECTION] C++ Only Classes
 *
 *
 * Resources:
 * - Homepage ................... https://github.com/djoezeke/argparser
 * - Releases & changelog ....... https://github.com/djoezeke/argparser/releases
 * - Issues & support ........... https://github.com/djoezeke/argparser/issues
 *
 */

#ifndef ARGPARSER_H
#define ARGPARSER_H

/**
 * @defgroup version Version Information
 * @brief Macros for library versioning.
 * @{
 */

/**
 * @def ARGPARSER_VERSION_MAJOR
 * @brief Major version number of the library.
 */
#define ARGPARSER_VERSION_MAJOR 0

/**
 * @def ARGPARSER_VERSION_MINOR
 * @brief Minor version number of the library.
 */
#define ARGPARSER_VERSION_MINOR 1

/**
 * @def ARGPARSER_VERSION_PATCH
 * @brief Patch version number of the library.
 */
#define ARGPARSER_VERSION_PATCH 0

/**
 * @def ARGPARSER_VERSION
 * @brief Library version string in the format @c "X.Y.Z",
 * where @c X is the major version number, @c Y is a minor version
 * number, and @c Z is the patch version number.
 */
#define ARGPARSER_VERSION "0.1.0"

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Header mess
//-----------------------------------------------------------------------------

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>  // for printf
#include <stdlib.h> // for realloc
#include <string.h> // for strdup strlen

#ifdef __cplusplus

#include <exception>
#include <iostream>
#include <unordered_map>

#endif //__cplusplus

#ifdef ARGPARSER_TESTS
#endif // ARGPARSER_TESTS

//-----------------------------------------------------------------------------
// [SECTION] Configurable Macros
//-----------------------------------------------------------------------------

#ifndef ARGPARSER_THEMED_PRINT

#define ST "\e[0;30m" // symbol
#define NT "\e[0;30m" // name
#define RT "\e[0;30m" // required
#define DT "\e[0;30m" // default
#define FT "\e[0;30m" // allowed
#define FT "\e[0;30m" // implicit
#define CC "\e[0;30m" // colon
#define NC "\e[0;30m" // none
#define HT "\e[0;30m" //

#endif // ARGPARSER_THEMED_PRINT

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
#define ARGPARSER_PLATFORM_IS(name) ARGPARSER_PLATFORM_IS_##name

/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */

#ifdef __APPLE__
/**
 * A preprocessor macro that is only defined if compiling for MacOS.
 */
#define ARGPARSER_PLATFORM_IS_APPLE 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define ARGPARSER_PLATFORM_NAME_IS "Apple"
#elif defined(linux) || defined(__linux) || defined(__linux__)
/**
 * A preprocessor macro that is only defined if compiling for Linux.
 */
#define ARGPARSER_PLATFORM_IS_LINUX 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define ARGPARSER_PLATFORM_NAME_IS "Linux"
#elif defined(WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(_MSC_VER) || defined(__MINGW32__)
/**
 * A preprocessor macro that is only defined if compiling for Windows.
 */
#define ARGPARSER_PLATFORM_IS_WINDOWS 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define ARGPARSER_PLATFORM_NAME_IS "Windows"
#else
/**
 * A preprocessor macro that is only defined if compiling for others.
 */
#define ARGPARSER_PLATFORM_IS_OTHERS 1
/**
 * @brief  Returns the current platform name.
 * @return  platform name.
 */
#define ARGPARSER_PLATFORM_NAME_IS "Others"
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
#define ARGPARSER_COMPILER_IS(name) ARGPARSER_COMPILER_IS_##name

/// Compiler is apple
#if !defined(__clang__)
#define ARGPARSER_COMPILER_IS_APPLE 0
#elif !defined(__apple_build_version__)
#define ARGPARSER_COMPILER_IS_APPLE 0
#else
#define ARGPARSER_COMPILER_IS_APPLE 1
#define ARGPARSER_COMPILER_VERSION_MAJOR __clang_major__
#define ARGPARSER_COMPILER_VERSION_MINOR __clang_minor__
#define ARGPARSER_COMPILER_VERSION_PATCH __clang_patchlevel__
#endif

/// Compiler is clang
#if !defined(__clang__)
#define ARGPARSER_COMPILER_IS_CLANG 0
#elif ARGPARSER_COMPILER_IS(APPLE)
#define ARGPARSER_COMPILER_IS_CLANG 0
#else
#define ARGPARSER_COMPILER_IS_CLANG 1
#define ARGPARSER_COMPILER_VERSION_MAJOR __clang_major__
#define ARGPARSER_COMPILER_VERSION_MINOR __clang_minor__
#define ARGPARSER_COMPILER_VERSION_PATCH __clang_patchlevel__
#endif

/// Compiler is intel
#if !defined(__INTEL_COMPILER)
#define ARGPARSER_COMPILER_IS_INTEL 0
#elif !defined(__INTEL_COMPILER_UPDATE)
#define ARGPARSER_COMPILER_IS_INTEL 1
/* __INTEL_COMPILER = XXYZ */
#define ARGPARSER_COMPILER_VERSION_MAJOR (__INTEL_COMPILER / 100)
#define ARGPARSER_COMPILER_VERSION_MINOR (__INTEL_COMPILER % 100 / 10)
#define ARGPARSER_COMPILER_VERSION_PATCH (__INTEL_COMPILER % 10)
#else
#define ARGPARSER_COMPILER_IS_INTEL 1
/* __INTEL_COMPILER = XXYZ */
#define ARGPARSER_COMPILER_VERSION_MAJOR (__INTEL_COMPILER / 100)
#define ARGPARSER_COMPILER_VERSION_MINOR (__INTEL_COMPILER % 100 / 10)
#define ARGPARSER_COMPILER_VERSION_PATCH __INTEL_COMPILER_UPDATE
#endif

/// Compiler is msc
#if !defined(_MSC_VER)
#define ARGPARSER_COMPILER_IS_MSVC 0
#elif ARGPARSER_COMPILER_IS(CLANG)
#define ARGPARSER_COMPILER_IS_MSVC 0
#elif ARGPARSER_COMPILER_IS(INTEL)
#define ARGPARSER_COMPILER_IS_MSVC 0
#elif _MSC_VER >= 1400
#define ARGPARSER_COMPILER_IS_MSVC 1
/* _MSC_FULL_VER = XXYYZZZZZ */
#define ARGPARSER_COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 10000000)
#define ARGPARSER_COMPILER_VERSION_MINOR (_MSC_FULL_VER % 10000000 / 100000)
#define ARGPARSER_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 100000)
#elif defined(_MSC_FULL_VER)
#define ARGPARSER_COMPILER_IS_MSVC 1
/* _MSC_FULL_VER = XXYYZZZZ */
#define ARGPARSER_COMPILER_VERSION_MAJOR (_MSC_FULL_VER / 1000000)
#define ARGPARSER_COMPILER_VERSION_MINOR (_MSC_FULL_VER % 1000000 / 10000)
#define ARGPARSER_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 10000)
#else
#define ARGPARSER_COMPILER_IS_MSVC 1
/* _MSC_VER = XXYY */
#define ARGPARSER_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
#define ARGPARSER_COMPILER_VERSION_MINOR (_MSC_VER % 100)
#define ARGPARSER_COMPILER_VERSION_PATCH 0
#endif

/// Compiler is gcc
#if !defined(__GNUC__)
#define ARGPARSER_COMPILER_IS_GCC 0
#elif ARGPARSER_COMPILER_IS(APPLE)
#define ARGPARSER_COMPILER_IS_GCC 0
#elif ARGPARSER_COMPILER_IS(CLANG)
#define ARGPARSER_COMPILER_IS_GCC 0
#elif ARGPARSER_COMPILER_IS(INTEL)
#define ARGPARSER_COMPILER_IS_GCC 0
#else
#define ARGPARSER_COMPILER_IS_GCC 1
#define ARGPARSER_COMPILER_VERSION_MAJOR __GNUC__
#define ARGPARSER_COMPILER_VERSION_MINOR __GNUC_MINOR__
#define ARGPARSER_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__
#endif

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Warnings
//-----------------------------------------------------------------------------

/**
 * @defgroup compiler Compiler Warnings
 * @{
 */

#if ARGPARSER_COMPILER_IS(CLANG)
#define ARGPARSER_PRAGMA_TO_STR(x) _Pragma(#x)
#define ARGPARSER_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
#define ARGPARSER_CLANG_SUPPRESS_WARNING(w) ARGPARSER_PRAGMA_TO_STR(clang diagnostic ignored w)
#define ARGPARSER_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
#define ARGPARSER_CLANG_SUPPRESS_WARNING_WITH_PUSH(w) \
  ARGPARSER_CLANG_SUPPRESS_WARNING_PUSH ARGPARSER_CLANG_SUPPRESS_WARNING(w)
#else // ARGPARSER_CLANG
#define ARGPARSER_CLANG_SUPPRESS_WARNING_PUSH
#define ARGPARSER_CLANG_SUPPRESS_WARNING(w)
#define ARGPARSER_CLANG_SUPPRESS_WARNING_POP
#define ARGPARSER_CLANG_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // ARGPARSER_CLANG

#if ARGPARSER_COMPILER_IS(GCC)
#define ARGPARSER_PRAGMA_TO_STR(x) _Pragma(#x)
#define ARGPARSER_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
#define ARGPARSER_GCC_SUPPRESS_WARNING(w) ARGPARSER_PRAGMA_TO_STR(GCC diagnostic ignored w)
#define ARGPARSER_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
#define ARGPARSER_GCC_SUPPRESS_WARNING_WITH_PUSH(w) \
  ARGPARSER_GCC_SUPPRESS_WARNING_PUSH ARGPARSER_GCC_SUPPRESS_WARNING(w)
#else // ARGPARSER_GCC
#define ARGPARSER_GCC_SUPPRESS_WARNING_PUSH
#define ARGPARSER_GCC_SUPPRESS_WARNING(w)
#define ARGPARSER_GCC_SUPPRESS_WARNING_POP
#define ARGPARSER_GCC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // ARGPARSER_GCC

#if ARGPARSER_COMPILER_IS(MSVC)
#define ARGPARSER_MSVC_SUPPRESS_WARNING_PUSH __pragma(warning(push))
#define ARGPARSER_MSVC_SUPPRESS_WARNING(w) __pragma(warning(disable : w))
#define ARGPARSER_MSVC_SUPPRESS_WARNING_POP __pragma(warning(pop))
#define ARGPARSER_MSVC_SUPPRESS_WARNING_WITH_PUSH(w) \
  ARGPARSER_MSVC_SUPPRESS_WARNING_PUSH ARGPARSER_MSVC_SUPPRESS_WARNING(w)
#else // ARGPARSER_MSVC
#define ARGPARSER_MSVC_SUPPRESS_WARNING_PUSH
#define ARGPARSER_MSVC_SUPPRESS_WARNING(w)
#define ARGPARSER_MSVC_SUPPRESS_WARNING_POP
#define ARGPARSER_MSVC_SUPPRESS_WARNING_WITH_PUSH(w)
#endif // ARGPARSER_MSVC

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Import/Export
//-----------------------------------------------------------------------------

/**
 * @defgroup export Export Definitions
 * @{
 */

#if defined(_WIN32)
#define ARGPARSER_NO_EXPORT_ATTR
#define ARGPARSER_API_EXPORT __declspec(dllexport)
#define ARGPARSER_API_IMPORT __declspec(dllimport)
#define ARGPARSER_DEPRECATED_ATTR __declspec(deprecated)
#else // _WIN32
#define ARGPARSER_API_EXPORT __attribute__((visibility("default")))
#define ARGPARSER_API_IMPORT __attribute__((visibility("default")))
#define ARGPARSER_NO_EXPORT_ATTR __attribute__((visibility("hidden")))
#define ARGPARSER_DEPRECATED_ATTR __attribute__((__deprecated__))
#endif // _WIN32

/**
 * @def ARGPARSER_API
 * @brief Macro for public API symbol export/import.
 * @details Use this macro to annotate all public API functions for correct symbol visibility on all platforms.
 */

#if defined(ARGPARSER_BUILD_STATIC)
#define ARGPARSER_API
#elif defined(ARGPARSER_BUILD_SHARED)
/* We are building this library */
#define ARGPARSER_API ARGPARSER_API_EXPORT
#elif defined(ARGPARSER_IMPORT)
/* We are using this library */
#define ARGPARSER_API ARGPARSER_API_IMPORT
#else // ARGPARSER_BUILD_STATIC
#define ARGPARSER_API
#endif // ARGPARSER_BUILD_STATIC

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] Data Structures
//-----------------------------------------------------------------------------

/**
 * @defgroup basic Basic Types
 * @brief Core types and data structures for Argparser.
 * @{
 */

/**
 * @enum ArgumentType
 * @brief Represents the type of an argument.
 * @details Used to distinguish between flag, keyword argument and table types as defined in the TOML specification.
 */
typedef enum ArgumentType
{
  FLAG,  /**< A flag argument, which is a boolean switch. */
  KWARG, /**< A keyword argument, which has a name and a value. */
  ARG,   /**< A positional argument, which is required and has a value. */
} ArgumentType;

/**
 * @enum ArgumentErrorType
 * @brief Represents the type of an argument error.
 */
typedef enum ArgumentErrorType
{
  /**
   * @name Argparser error types
   * @{
   */

  UKNOWN = -1,
  MAP,        /**< Errors in map lookups */
  HELP,       /**< An exception that indicates that the user has requested help */
  USAGE,      /**< Errors that occur during usage */
  EXTRA,      /**< Errors that occurs when a singular flag is specified multiple times */
  PARSE,      /**< Errors that occur during regular parsing */
  REQUIRED,   /**< Errors that when a required flag is omitted */
  VALIDATION, /**< Errors that are detected from group validation after parsing finishes */
  COMPLETION, /**< An exception that contains autocompletion reply */

  /** @} */

} ArgumentErrorType;

/**
 * @name ArgumentError data type
 * @{
 */

/**
 * @struct ArgumentError_t
 * @brief Represents an error encountered during Argument parsing.
 * @details Contains error type and message for diagnostics.
 */
typedef struct ArgumentError_t
{
  ArgumentErrorType type; /**< ArgumentType of error. */
  const char *message;    /**< Error message string. */
  const char *arg;        /**< The Argument related to error. */
} ArgumentError_t;

/** @} */

/**
 * @name Argument data type
 * @{
 */

/**
 * @struct Argument
 * @brief Represents an argument.
 * @details Used to store any Argument, including flag,kwargs and args.
 */
typedef struct Argument_t
{
  ArgumentType type; /**< The type of the argument (FLAG, KWARG, ARG). */
  char *def_val;     /**< The default value for the argument. */
  int required;      /**< Whether the argument is required. */
  char *help;        /**< The help message for the argument. */
  char *name;        /**< The name of the argument. */
  int count;         /**< The number of arguments expected. */
  char sym;          /**< The short symbol for the argument. */
  union
  {
    char *value;   /**< The value of the argument. */
    char **values; /**< The values of the argument if multiple. */
  };

} Argument_t;

/** @} */

/**
 * @name ArgumentParser_t data type
 * @{
 */

/**
 * @struct ArgumentParser_t
 * @brief Represents the Argument parser.
 */
typedef struct ArgumentParser_t
{
  char *program;         /**< The name of the program. */
  char *usage;           /**< The usage message. */
  char *epilog;          /**< The epilog message. */
  int count;             /**< The number of arguments. */
  char *description;     /**< The description of the program. */
  Argument_t *arguments; /**< The list of arguments. */
  char prefix_char;      /**< The prefix character. */
  const char *argument_default;
  bool add_help;
  bool allow_abbrev;
  bool exit_on_error;
} ArgumentParser_t;

/** @} */

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

  /**
   * Initializes an ArgumentParser instance.
   *
   * @param parser The ArgumentParser to initialize.
   * @param program The name of the program.
   * @param usage The usage message.
   * @param description The description of the program.
   * @param epilog The epilog message.
   * @param add_help Whether to add a help flag automatically.
   *
   * Example usage:
   * @code
   * ArgumentParser parser;
   * ArgumentParserInit(&parser, "my_program", "Usage: my_program [options]", "This is a sample program.", "Epilog message", 1);
   * @endcode
   */
  ARGPARSER_API void ArgumentParserInit(ArgumentParser_t *, const char *, const char *, const char *, const char *);

  /**
   * Frees the memory allocated for the ArgumentParser instance.
   *
   * @param parser The ArgumentParser instance.
   *
   * Example usage:
   * ArgumentParserFree(parser);
   */
  ARGPARSER_API void ArgumentParserFree(ArgumentParser_t *);

  /**
   * Adds an argument to the argument parser.
   *
   * @param parser The ArgumentParser to add the argument to.
   * @param sym The short symbol for the argument.
   * @param name The long name for the argument.
   * @param required Whether the argument is required.
   * @param nargs The number of arguments expected.
   * @param default_value The default value for the argument.
   * @param help The help message for the argument.
   *
   * Example usage:
   * ArgumentParserAddArg(parser, 'o', "output", 1, 1, "default_output.txt", "Output file");
   */
  ARGPARSER_API void ArgumentParserAddArg(ArgumentParser_t *, char, const char *, int, int, const char *, const char *);

  /**
   * Adds a keyword argument to the argument parser.
   *
   * @param parser The ArgumentParser to add the argument to.
   * @param sym The short symbol for the argument.
   * @param name The long name for the argument.
   * @param required Whether the argument is required.
   * @param default_value The default value for the argument.
   * @param help The help message for the argument.
   *
   * Example usage:
   * ArgumentParserAddKwarg(parser, 'v', "verbose", 0, "false", "Enable verbose mode");
   */
  ARGPARSER_API void ArgumentParserAddKwarg(ArgumentParser_t *, char, const char *, int, const char *, const char *);

  /**
   * Adds a flag argument to the argument parser.
   *
   * @param parser The ArgumentParser to add the argument to.
   * @param sym The short symbol for the argument.
   * @param name The long name for the argument.
   * @param help The help message for the argument.
   *
   * Example usage:
   * ArgumentParserAddFlag(parser, 'h', "help", "Show help message");
   */
  ARGPARSER_API void ArgumentParserAddFlag(ArgumentParser_t *, char, const char *, const char *);

  /**
   * Parses the command-line arguments.
   *
   * @param parser The ArgumentParser instance.
   * @param argc The argument count.
   * @param argv The argument vector.
   *
   * Example usage:
   * ArgumentParserParseArgs(parser, argc, argv);
   */
  ARGPARSER_API void ArgumentParserParseArgs(ArgumentParser_t *, int, char **);

  /**
   * Retrieves the value of an argument.
   *
   * @param parser The ArgumentParser instance.
   * @param name The name of the argument.
   * @return The value of the argument.
   *
   * Example usage:
   * const char *output = ArgumentParserGetArg(parser, "output");
   */
  ARGPARSER_API const char *ArgumentParserGetArg(ArgumentParser_t *, const char *);

  /**
   * Retrieves the value of a keyword argument.
   *
   * @param parser The ArgumentParser instance.
   * @param name The name of the keyword argument.
   * @return The value of the keyword argument.
   *
   * Example usage:
   * const char *verbose = ArgumentParserGetKwarg(parser, "verbose");
   */
  ARGPARSER_API const char *ArgumentParserGetKwarg(ArgumentParser_t *, const char *);

  /**
   * Retrieves the value of a flag argument.
   *
   * @param parser The ArgumentParser instance.
   * @param name The name of the flag argument.
   * @return The value of the flag argument.
   *
   * Example usage:
   * int help = ArgumentParserGetFlag(parser, "help");
   */
  ARGPARSER_API int ArgumentParserGetFlag(ArgumentParser_t *, const char *);

  /**
   * Prints the help message.
   *
   * @param parser The ArgumentParser instance.
   * @param description Whether to print the description.
   * @param usage Whether to print the usage.
   * @param epilog Whether to print the epilog.
   * @param group Whether
   *
   * Example usage:
   * ArgumentParserPrintHelp(parser);
   */
  ARGPARSER_API void ArgumentParserPrintHelp(ArgumentParser_t *);

  /**
   * @brief Gets the error arg.
   * @param[in] error The error.
   * @return The error argument.
   */
  ARGPARSER_API const char *ArgumetParserErrorArg(ArgumentError_t *);

  /**
   * @brief Gets the error message.
   * @param[in] error The error.
   * @return The error message.
   */
  ARGPARSER_API const char *ArgumetParserErrorWhat(ArgumentError_t *);

  /**
   * @brief Gets the error type.
   * @param[in] error The error.
   * @return The error type.
   */
  ARGPARSER_API ArgumentErrorType ArgumetParserErrorType(ArgumentError_t *);

#ifdef __cplusplus
}
#endif //__cplusplus

#ifdef __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------
namespace argparser
{

  /**
   * @class ArgumentError
   * @brief ArgumentError class for Argument-related errors.
   */
  class ArgumentError : public std::exception
  {
  public:
    /**
     * @brief Constructs an exception with a specific error type.
     * @param type The type of the error.
     */
    ArgumentError(ArgumentError_t type);

    /**
     * @brief Gets the error arg.
     * @return The error argument.
     */
    const char *arg() const noexcept;

    /**
     * @brief Gets the error message.
     * @return The error message.
     */
    const char *what() const noexcept override;

    /**
     * @brief Gets the error type.
     * @return The error type.
     */
    ArgumentErrorType type() const noexcept;

  private:
    ArgumentError_t m_Error; /**< The error type. */
  };

  /** Errors that occur during usage
   */
  class UsageError : public ArgumentError
  {
  public:
    UsageError(ArgumentError_t error)
        : ArgumentError(error) {};
    virtual ~UsageError() {}
  };

  /** Errors that occur during regular parsing
   */
  class ParseError : public ArgumentError
  {
  public:
    ParseError(ArgumentError_t error)
        : ArgumentError(error) {};
    virtual ~ParseError() {}
  };

  /** Errors that when a required flag is omitted
   */
  class RequiredError : public ArgumentError
  {
  public:
    RequiredError(ArgumentError_t error)
        : ArgumentError(error) {};
    virtual ~RequiredError() {};
  };

}; // namespace argparser

#endif //__cplusplus

#endif // ARGPARSER_H

#ifdef ARGPARSER_IMPLEMENTATION

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
extern "C"
{
#endif // __cplusplus

  //-----------------------------------------------------------------------------
  // [SECTION] Declarations
  //-----------------------------------------------------------------------------

  ARGPARSER_API void _ArgumentParserPrintArgHelp(ArgumentParser_t *, int);

  ARGPARSER_API void _ArgumentParserPrintFlagHelp(ArgumentParser_t *, int);

  ARGPARSER_API void _ArgumentParserPrintKwargHelp(ArgumentParser_t *, int);

  /**
   * @brief Constructs an exception with a specific message and error type.
   * @param type The type of the error.
   * @param message The error message.
   * @param arg The error arg.
   */
  ARGPARSER_API ArgumentError_t _ArgumentErrorInit(ArgumentErrorType, const char *, const char *);

  /**
   * @brief Destroy and free an ArgumentError_t.
   * @param error The ArgumentError_t to destory.
   */
  ARGPARSER_API void _ArgumentErrorFree(ArgumentError_t *);

  //-----------------------------------------------------------------------------
  // [SECTION] Definations
  //-----------------------------------------------------------------------------

  ARGPARSER_API void _ArgumentParserPrintArgHelp(ArgumentParser_t *parser, int i)
  {
    printf("-%c --%s ", parser->arguments[i].sym ? parser->arguments[i].sym : ' ', parser->arguments[i].name);
    printf("(required: %d , [%s] ) ", parser->arguments[i].required, parser->arguments[i].def_val ? parser->arguments[i].def_val : "None");
    printf("= %s \n", parser->arguments[i].help ? parser->arguments[i].help : "No description");
  };

  ARGPARSER_API void _ArgumentParserPrintFlagHelp(ArgumentParser_t *parser, int i)
  {
    printf("-" FT "%c" NC "--" NT "%s " NC, parser->arguments[i].sym ? parser->arguments[i].sym : '\0', parser->arguments[i].name);
    printf(CC ":" NC HT "%s" NC "\n", parser->arguments[i].help ? parser->arguments[i].help : "");
  };

  ARGPARSER_API void _ArgumentParserPrintKwargHelp(ArgumentParser_t *parser, int i)
  {
    printf("-" FT "%c" NC "--" NT "%s " NC, parser->arguments[i].sym ? parser->arguments[i].sym : '\0', parser->arguments[i].name);
    printf(CC ":" NC HT "%s" NC, parser->arguments[i].help ? parser->arguments[i].help : "");

    printf("[" NC HT "%s" NC, parser->arguments[i].help ? parser->arguments[i].help : "");

    printf("[" NC "required " NC CC ": " NC " %d , [%s] ) ", parser->arguments[i].required, parser->arguments[i].def_val ? parser->arguments[i].def_val : "");
  };

  ARGPARSER_API ArgumentError_t _ArgumentErrorInit(ArgumentErrorType type, const char *message, const char *arg)
  {
    ArgumentError_t error = {.type = type, .message = strdup(message), .arg = arg};
    return error;
  };

  ARGPARSER_API void _ArgumentErrorFree(ArgumentError_t *error) {
  };

#ifdef __cplusplus
}
#endif // __cplusplus

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

#endif //__cplusplus

#pragma endregion

#pragma region Argparser

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

  ARGPARSER_API void ArgumentParserInit(ArgumentParser_t *parser, const char *program, const char *usage, const char *description, const char *epilog)
  {
    parser->program = strdup(program);
    parser->usage = strdup(usage);
    parser->description = strdup(description);
    parser->epilog = strdup(epilog);
    parser->arguments = NULL;
    parser->count = 0;
    parser->prefix_char = '-';
    parser->add_help = true;
    parser->allow_abbrev = true;
    parser->exit_on_error = true;

    if (parser->add_help)
    {
      ArgumentParserAddFlag(parser, 'h', "help", "Shows this help Menu");
    }
  }

  ARGPARSER_API void ArgumentParserFree(ArgumentParser_t *parser)
  {
    if (!parser)
      return;

    for (int i = 0; i < parser->count; i++)
    {
      free(parser->arguments[i].name);
      if (parser->arguments[i].help)
        free(parser->arguments[i].help);
      if (parser->arguments[i].def_val)
        free(parser->arguments[i].def_val);
      if (parser->arguments[i].type == ARG || parser->arguments[i].type == KWARG)
      {
        if (parser->arguments[i].count == 1)
        {
          if (parser->arguments[i].value)
            free(parser->arguments[i].value);
        }
        else
        {
          if (parser->arguments[i].values)
          {
            for (size_t j = 0; j < parser->arguments[i].count; j++)
            {
              if (parser->arguments[i].values[j])
                free(parser->arguments[i].values[j]);
            }
            free(parser->arguments[i].values); // Free the values array itself
          }
        }
      }
    }
    free(parser->arguments);

    if (parser->program)
      free(parser->program);
    if (parser->usage)
      free(parser->usage);
    if (parser->description)
      free(parser->description);
    if (parser->epilog)
      free(parser->epilog);
  }

  ARGPARSER_API void ArgumentParserAddArg(ArgumentParser_t *parser, char sym, const char *name, int required, int nargs, const char *default_value, const char *help)
  {
    parser->arguments = (Argument_t *)realloc(parser->arguments, sizeof(Argument_t) * (parser->count + 1));
    parser->arguments[parser->count].name = strdup(name);
    parser->arguments[parser->count].required = required;
    parser->arguments[parser->count].def_val = default_value ? strdup(default_value) : NULL;
    parser->arguments[parser->count].value = NULL;
    parser->arguments[parser->count].sym = sym ? sym : '0';
    parser->arguments[parser->count].help = help ? strdup(help) : NULL;
    parser->arguments[parser->count].type = ARG;
    parser->arguments[parser->count].count = nargs;
    parser->count++;
  }

  ARGPARSER_API void ArgumentParserAddKwarg(ArgumentParser_t *parser, char sym, const char *name, int required, const char *default_value, const char *help)
  {
    parser->arguments = (Argument_t *)realloc(parser->arguments, sizeof(Argument_t) * (parser->count + 1));
    parser->arguments[parser->count].name = strdup(name);
    parser->arguments[parser->count].required = required;
    parser->arguments[parser->count].def_val = default_value ? strdup(default_value) : NULL;
    parser->arguments[parser->count].value = NULL;
    parser->arguments[parser->count].sym = sym ? sym : '0';
    parser->arguments[parser->count].help = help ? strdup(help) : NULL;
    parser->arguments[parser->count].type = KWARG;
    parser->count++;
  }

  ARGPARSER_API void ArgumentParserAddFlag(ArgumentParser_t *parser, char sym, const char *name, const char *help)
  {
    parser->arguments = (Argument_t *)realloc(parser->arguments, sizeof(Argument_t) * (parser->count + 1));
    parser->arguments[parser->count].name = strdup(name);
    parser->arguments[parser->count].required = 0;
    parser->arguments[parser->count].def_val = NULL;
    parser->arguments[parser->count].value = NULL;
    parser->arguments[parser->count].sym = sym ? sym : '0';
    parser->arguments[parser->count].help = help ? strdup(help) : NULL;
    parser->arguments[parser->count].type = FLAG;
    parser->count++;
  }

  ARGPARSER_API void ArgumentParserParseArgs(ArgumentParser_t *parser, int argc, char *argv[])
  {
    for (int i = 1; i < argc; i++)
    {
      if (strncmp(argv[i], "--", 2) == 0)
      {
        char *arg = argv[i] + 2;
        char *value = strchr(arg, '=');
        if (value)
        {
          *value = '\0';
          value++;
        }
        else
        {
          value = NULL;
        }
        for (int j = 0; j < parser->count; j++)
        {
          if (strcmp(parser->arguments[j].name, arg) == 0)
          {
            parser->arguments[j].value = strdup(value);
            break;
          }
        }
        for (size_t j = 0; j < parser->count; j++)
        {
          if (strcmp(parser->arguments[j].name, arg) == 0 && parser->arguments[j].type == FLAG)
          {
            parser->arguments[j].value = strdup("true");
            break;
          }
          else if (strcmp(parser->arguments[j].name, arg) == 0 && parser->arguments[j].type == KWARG)
          {
            parser->arguments[j].value = strdup(value);
            break;
          }
        }
      }

      // for -o -i -s=hello or -ois=hello
      else if (strncmp(argv[i], "-", 1) == 0)
      {
        char *arg = argv[i] + 1;
        char *value = strchr(arg, '=');
        if (value)
        {
          *value = '\0';
          value++;
        }
        else
        {
          value = NULL;
        }
        if (arg)
        {
          for (size_t j = 0; j < strlen(arg); j++)
          {
            for (size_t k = 0; k < parser->count; k++)
            {
              if (parser->arguments[k].sym == arg[j] && parser->arguments[k].type == FLAG)
              {
                parser->arguments[k].value = strdup("true");
                break;
              }
              else if (parser->arguments[k].sym == arg[j] && parser->arguments[k].type == KWARG)
              {
                parser->arguments[k].value = strdup(value);
                break;
              }
            }
          }
        }
      }
      else
      {
        char *arg = argv[i];
        char *value = strchr(arg, '=');
        if (value)
        {
          *value = '\0';
          value++;
        }
        else
        {
          value = NULL;
        }
        printf("%s", arg);
        for (int j = 0; j < parser->count; j++)
        {
          if (strcmp(parser->arguments[j].name, arg) == 0)
          {
            parser->arguments[j].value = strdup(value);
            break;
          }
        }
        for (size_t j = 0; j < parser->count; j++)
        {
          if (strcmp(parser->arguments[j].name, arg) == 0 && parser->arguments[j].type == FLAG)
          {
            parser->arguments[j].value = strdup("true");
            break;
          }
          else if (strcmp(parser->arguments[j].name, arg) == 0 && parser->arguments[j].type == KWARG)
          {
            parser->arguments[j].value = strdup(value);
            break;
          }
        }
      }
    }

    for (int i = 0; i < parser->count; i++)
    {
      if (parser->arguments[i].required && !parser->arguments[i].value)
      {
        fprintf(stderr, "Missing required argument: %s\n", parser->arguments[i].name);
        exit(EXIT_FAILURE);
      }
      if (!parser->arguments[i].value)
      {
        parser->arguments[i].value = parser->arguments[i].def_val;
      }
    }
  }

  ARGPARSER_API const char *ArgumentParserGetArg(ArgumentParser_t *parser, const char *name)
  {
    for (int i = 0; i < parser->count; i++)
    {
      if (strcmp(parser->arguments[i].name, name) == 0)
      {
        if (parser->arguments[i].type == ARG)

          if (parser->arguments[i].value != NULL)
            return parser->arguments[i].value;
          else
            return parser->arguments[i].def_val;
        else
          return NULL;
      }
    }
    return NULL;
  }

  ARGPARSER_API const char *ArgumentParserGetKwarg(ArgumentParser_t *parser, const char *name)
  {
    for (int i = 0; i < parser->count; i++)
    {
      if (strcmp(parser->arguments[i].name, name) == 0)
      {
        if (parser->arguments[i].type == KWARG)

          if (parser->arguments[i].value != NULL)
            return parser->arguments[i].value;
          else
            return parser->arguments[i].def_val;
        else
          return NULL;
      }
    }
    return NULL;
  }

  ARGPARSER_API int ArgumentParserGetFlag(ArgumentParser_t *parser, const char *name)
  {
    for (int i = 0; i < parser->count; i++)
    {
      if (strcmp(parser->arguments[i].name, name) == 0)
      {
        if (parser->arguments[i].type == FLAG)
          if (parser->arguments[i].value != NULL)
            return 1;
          else
            return 0;
        else
          return 0;
      }
    }
    return 0;
  }

  ARGPARSER_API void ArgumentParserPrintHelp(ArgumentParser_t *parser)
  {
    if (parser == NULL)
    {
      return;
    }

    for (int i = 0; i < parser->count; i++)
    {
      if (parser->arguments[i].type == FLAG)
      {
        _ArgumentParserPrintFlagHelp(parser, i);
      }
      else if (parser->arguments[i].type == KWARG)
      {
        _ArgumentParserPrintKwargHelp(parser, i);
      }
      else
      {
        _ArgumentParserPrintArgHelp(parser, i);
      }
    }
  }

  ARGPARSER_API const char *ArgumetParserErrorArg(ArgumentError_t *error)
  {
    return error->arg;
  };

  ARGPARSER_API const char *ArgumetParserErrorWhat(ArgumentError_t *error)
  {
    return error->message;
  };

  ARGPARSER_API ArgumentErrorType ArgumetParserErrorType(ArgumentError_t *error)
  {
    return error->type;
  };

#ifdef __cplusplus
}
#endif // __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

#ifdef __cplusplus

ArgumentError::ArgumentError(ArgumentError_t error)
{
  m_Error = {.type = error.type, .message = strdup(error.message), .arg = error.arg};
};

const char *ArgumentError::arg() const noexcept
{
  return m_Error.arg;
};

const char *ArgumentError::what() const noexcept
{
  return m_Error.message;
};

ArgumentErrorType ArgumentError::type() const noexcept
{
  return m_Error.type;
};

#endif //__cplusplus

#pragma endregion

#endif // ARGPARSER_IMPLEMENTATION
