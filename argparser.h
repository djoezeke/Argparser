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
   Do this:
    #define ARGPARSER_IMPLEMENTATION
   before you include this file in *one* C or C++ file to create the implementation.

   // i.e. it should look like this:
   #include ...
   #include ...
   #define ARGPARSER_IMPLEMENTATION
   #include "argparser.h"

* Example usage:
 * @code
 * int main(int argc, char *argv[]) {
 *     Argparser *parser = new_parser("my_program", "Usage: my_program
 * [options]", "This is a sample program.", "Epilog message", 1);
 *     add_arg(parser, 'o', "output", 1, 1, "default_output.txt", "Output
 * file"); add_kwarg(parser, 'v', "verbose", 0, "false", "Enable verbose mode");
 *     add_flag(parser, 'h', "help", "Show help message");
 *
 *     parse_args(parser, argc, argv);
 *
 *     const char *output = get_arg(parser, "output");
 *     const char *verbose = get_kwarg(parser, "verbose");
 *     int help = get_flag(parser, "help");
 *
 *     if (help) {
 *         print_help(parser, 1, 1, 1, 0);
 *         free_parser(parser);
 *         return 0;
 *     }
 *
 *     printf("Output: %s\n", output);
 *     printf("Verbose: %s\n", verbose);
 *
 *     free_parser(parser);
 *     return 0;
 * }
 * @endcode
 *
 * Index of this file:
 *
 *  [SECTION] Header mess
 *  [SECTION] Configurable macros
 *  [SECTION] Imports/Exports
 *  [SECTION] Data Structures
 *  [SECTION] C Only Functions
 *  [SECTION] C++ Only Classes
 *
 * ARGPARSER_IMPLEMENTATION
 *
 *  Internal:
 *
 *  [SECTION] Defines
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

#endif //__cplusplus

#ifdef ARGPARSER_TESTS
#endif // ARGPARSER_TESTS

//-----------------------------------------------------------------------------
// [SECTION] Configurable Macros
//-----------------------------------------------------------------------------

#ifndef ARGPARSER_THEMED_PRINT

#define ST "\e[0;32m" // symbol
#define NT "\e[0;30m" // name
#define RT "\e[0;33m" // required
#define DT "\e[0;33m" // default
#define FT "\e[0;30m" // allowed
#define FT "\e[0;30m" // implicit
#define CC "\e[0;34m" // colon
#define NC "\e[0;30m" // none
#define HT "\e[0;30m" //

#endif // ARGPARSER_THEMED_PRINT

#ifdef ARGPARSER_TESTS
#endif // ARGPARSER_TESTS

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

  UKNOWN = -1,
  MAP,        /**< Errors in map lookups */
  HELP,       /**< An exception that indicates that the user has requested help */
  USAGE,      /**< Errors that occur during usage */
  EXTRA,      /**< Errors that occurs when a singular flag is specified multiple times */
  PARSE,      /**< Errors that occur during regular parsing */
  REQUIRED,   /**< Errors that when a required flag is omitted */
  VALIDATION, /**< Errors that are detected from group validation after parsing finishes */
  COMPLETION, /**< An exception that contains autocompletion reply */

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
typedef struct Argument
{
} Argument;

/** @} */

/**
 * @name Argparser_t data type
 * @{
 */

/**
 * @struct Argparser_t
 * @brief Represents the Argument parser.
 */
typedef struct Argparser_t
{
} Argparser_t;

/** @} */

/** @} */

//-----------------------------------------------------------------------------
// [SECTION] C Only Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

  ARGPARSER_API Argparser_t *ArgumentParserInit(const char *, ...);

  /**
   * @brief Destroy and free an Argprser.
   * @param argparser The Argparser to destory.
   */
  ARGPARSER_API void ArgumentParserFree(Argparser_t *);

  /**
   * @brief Gets the error arg.
   * @param[in] error The error.
   * @return The error argument.
   */
  ARGPARSER_API const char *arg(ArgumentError_t *error);

  /**
   * @brief Gets the error message.
   * @param[in] error The error.
   * @return The error message.
   */
  ARGPARSER_API const char *what(ArgumentError_t *error);

  /**
   * @brief Gets the error type.
   * @param[in] error The error.
   * @return The error type.
   */
  ARGPARSER_API ArgumentErrorType type(ArgumentError_t *error);

#ifdef __cplusplus
}
#endif //__cplusplus

#ifdef __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] C++ Only Classes
//-----------------------------------------------------------------------------

/**
 * @class ArgumentError
 * @brief ArgumentError class for Argument-related errors.
 */
class ArgumentError : public std::exception
{
public:
  /**
   * @brief Default constructor.
   */
  ArgumentError();

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

  ARGPARSER_API const char *arg(ArgumentError_t *error)
  {
    return error->arg;
  };

  ARGPARSER_API const char *what(ArgumentError_t *error)
  {
    return error->message;
  };

  ARGPARSER_API ArgumentErrorType type(ArgumentError_t *error)
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

ArgumentError::ArgumentError()
{
  m_Error = {.type = UKNOWN, .message = "UKNOWN"};
};

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
