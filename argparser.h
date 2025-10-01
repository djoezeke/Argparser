/* -*- C++ -*- compatibility header. */

/** @file argparser.h
 *
 *  This is a  C/C++ Argument Parser Library Header  @c argparser.h.
 *  You should @c \#include this file in your programs, for all compilers C or
 C++.
 *

 * @author Sackey Ezekiel Etrue.
 * @version 0.1.0
 * @c <https://www.github.com/djoezeke/argparser>.
 *
 */

#ifndef ARGPARSER_H

/**
 * Example usage:
 *
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
 */

#define ARGPARSER_H

#define ARGPARSER_VERSION "0.1.0"
#define ARGPARSER_VERSION_MAJOR 0
#define ARGPARSER_VERSION_MINOR 1
#define ARGPARSER_VERSION_PATCH 0

/* All the headers include this file. */
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>  // for printf
#include <stdlib.h> // for realloc
#include <string.h> // for strdup strlen

#ifdef __cplusplus

/* C++ Exclusive headers. */
#include <exception>
#include <iostream>

#endif //__cplusplus

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
// [SECTION] Je-Prof Import/Export
//-----------------------------------------------------------------------------

#if defined(_WIN32)
#define ARGPARSER_API_EXPORT __declspec(dllexport)
#define ARGPARSER_API_IMPORT __declspec(dllimport)
#else // _WIN32
#define ARGPARSER_API_EXPORT __attribute__((visibility("default")))
#define ARGPARSER_API_IMPORT __attribute__((visibility("default")))
#endif // _WIN32

#if defined(ARGPARSER_BUILD_STATIC)
#define ARGPARSER_API
#elif defined(ARGPARSER_BUILD_SHARED)
#ifdef ARGPARSER_EXPORT
#define ARGPARSER_API ARGPARSER_API_EXPORT
#else // ARGPARSER_EXPORT
#define ARGPARSER_API ARGPARSER_API_IMPORT
#endif // ARGPARSER_EXPORT
#else  // ARGPARSER_BUILD_STATIC
#define ARGPARSER_API
#endif // ARGPARSER_BUILD_STATIC

//-----------------------------------------------------------------------------
// [SECTION] Je-Prof Structures
//-----------------------------------------------------------------------------

/**
 * Represents the type of an argument.
 */
typedef enum Type {
  FLAG,  /**< A flag argument, which is a boolean switch. */
  KWARG, /**< A keyword argument, which has a name and a value. */
  ARG,   /**< A positional argument, which is required and has a value. */
} Type;

/**
 * Represents the type of argument error.
 */
typedef enum ArgumentError_t {
  UKNOWN = -1,
} ArgumentError_t;

/**
 * Represents an argument type.
 */
typedef struct Argument_t {
  char *name;    /**< The name of the argument. */
  char sym;      /**< The short symbol for the argument. */
  int required;  /**< Whether the argument is required. */
  char *help;    /**< The help message for the argument. */
  Type type;     /**< The type of the argument (FLAG, KWARG, ARG). */
  int count;     /**< The number of arguments expected. */
  char *def_val; /**< The default value for the argument. */
  union {
    char *value;   /**< The value of the argument. */
    char **values; /**< The values of the argument if multiple. */
  };

} Argument_t;

/**
 * Represents the argument parser type.
 */
typedef struct ArgumentParser_t {
  char *program;         /**< The name of the program. */
  char *usage;           /**< The usage message. */
  char *epilog;          /**< The epilog message. */
  int count;             /**< The number of arguments. */
  char *description;     /**< The description of the program. */
  Argument_t *arguments; /**< The list of arguments. */
  char *longprefix;      /**< The prefix character. */
  char *shortprefix;     /**< The prefix character. */
  char *terminator;      /**< The prefix character. */
  const char *argument_default;
  bool add_help;
  bool allow_abbrev;
  bool exit_on_error;
} ArgumentParser_t;

#ifdef __cplusplus

//-----------------------------------------------------------------------------
// [SECTION] Je-Prof C++ Only
//-----------------------------------------------------------------------------

#ifdef ARGPARSER_TESTS
namespace argstest {
#else

/** \namespace argparser
 * \brief contains all the functionality of the argparser library
 */
namespace argparser {
#endif

/**
 * @brief ArgumentError class for Argument-related errors.
 */
class ArgumentError : public std::exception {
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
   * @brief Constructs an exception with a specific message and error type.
   * @param message The error message.
   * @param type The type of the error.
   */
  ArgumentError(const std::string &message, ArgumentError_t type);

  /**
   * @brief Gets the error message.
   * @return The error message.
   */
  const char *what() const noexcept override;

  /**
   * @brief Gets the error type.
   * @return The error type.
   */
  ArgumentError_t GetErrType() const noexcept;

  /**
   * @brief Gets the name of the error type.
   * @param error The error type.
   * @return The name of the error type.
   */
  std::string GetErrName(ArgumentError_t error) const noexcept;

private:
  std::string m_Arg;         //!< The Argument which cause the error.
  mutable std::string m_Msg; //!< The error message.
  ArgumentError_t m_Error;   //!< The error type.
};

class Argparser {
private:
  ArgumentParser_t *m_Parser;

public:
  /**
   * @brief Default constructor.
   */
  Argparser();
  Argparser(std::string program, std::string usage, std::string description,
            std::string epilog);

  void Help(int description, int usage, int epilog, int group);
  void Parse(int argc, char **argv);

  int GetFlag(const char *name);
  const char *GetArg(const char *name);
  const char *GetKwarg(const char *name);

  void AddFlag(char sym, const char *name, const char *help);
  void AddKwarg(char sym, const char *name, int required,
                const char *default_value, const char *help);
  void AddArg(char sym, const char *name, int required, int nargs,
              const char *default_value, const char *help);

  /**
   * @brief Destructor.
   */
  ~Argparser();
};
} // namespace argparser

#else // C

//-----------------------------------------------------------------------------
// [SECTION] Je-Prof C Only
//-----------------------------------------------------------------------------

/**
 * @brief ArgumentError struct for Argument-related errors.
 */
typedef struct ArgumentError {
  ArgumentError_t m_Type; //!< The error type.
  const char *m_Arg;      //!< The Argument which cause the error.
  const char *m_Msg;      //!< The error message.

  /**
   * @brief Gets the error message.
   * @return The error message.
   */
  const char *(*what)(ArgumentError *);

  /**
   * @brief Gets the error type.
   * @return The error type.
   */
  ArgumentError_t (*GetErrType)(ArgumentError *);

  /**
   * @brief Gets the name of the error type.
   * @param error The error type.
   * @return The name of the error type.
   */
  const char *(*GetErrName)(ArgumentError *);

} ArgumentError;

/**
 * Represents the Argument parser.
 */
typedef struct Argparser {
  ArgumentParser_t *m_Parser;

  void (*Help)(Argparser *, int, int, int, int);
  void (*Parse)(Argparser *, int, char **);

  int (*GetFlag)(Argparser *, const char *);
  const char *(*GetArg)(Argparser *, const char *);
  const char *(*GetKwarg)(Argparser *, const char *);

  void (*AddFlag)(Argparser *, char, const char *, const char *);
  void (*AddKwarg)(Argparser *, char, const char *, int, const char *,
                   const char *);
  void (*AddArg)(Argparser *, char, const char *, int, int, const char *,
                 const char *);

} Argparser;

/**
 * @brief Constructs an exception with a specific message and error type.
 * @param message The error message.
 * @param type The type of the error.
 */
ArgumentError *newArgumentError(const char *message, ArgumentError_t type);

/**
 * @brief Gets the error message.
 * @return The error message.
 */
const char *what(ArgumentError *);

/**
 * @brief Gets the error type.
 * @return The error type.
 */
ArgumentError_t GetErrType(ArgumentError *);

/**
 * @brief Gets the name of the error type.
 * @param error The error type.
 * @return The name of the error type.
 */
const char *GetErrName(ArgumentError *);

void freeArgumentError(ArgumentError *);

/**
 * @brief Constructs an Argparser with a specific format.
 * @param format parser format strind.
 * @param parser The Argparser instance.
 * @param p program.
 * @param d description.
 * @param u usage.
 * @param e epilog.
 * @param c prefix_chars
 * @param h add_help
 * @param a allow_abbrev
 * @param r exit_on_error
 * @param D argument_default
 * @return An Argparser Object.
 *
 * Example usage:
 * newArgumentParser(format,...);
 */
Argparser *newArgumentParser(const char *, ...);

void Help(Argparser *, int, int, int, int);
void Parse(Argparser *, int, char **);

int GetFlag(Argparser *, const char *);
const char *GetArg(Argparser *, const char *);
const char *GetKwarg(Argparser *, const char *);

void AddFlag(Argparser *, char, const char *, const char *);
void AddKwarg(Argparser *, char, const char *, int, const char *, const char *);
void AddArg(Argparser *, char, const char *, int, int, const char *,
            const char *);

/**
 * @brief Destroy and free an Argprser.
 * @param argparser The Argparser to destory.
 */
void freeArgumentParser(Argparser *);

#endif // __cplusplus

#endif // ARGPARSER_H

// Copyright (c) 2025 Sackey Ezekiel Etrue

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
