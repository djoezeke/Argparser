/**
 * @file argparser.c
 * @brief Argument Parser Library Source for C/C++.
 * This is a  C/C++ Json Parser Library Header @c argparser.h.
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
 *
 * Resources:
 * - Homepage ................... https://github.com/djoezeke/argparser
 * - Releases & changelog ....... https://github.com/djoezeke/argparser/releases
 * - Issues & support ........... https://github.com/djoezeke/argparser/issues
 *
 */

#define ARGPARSER_IMPLEMENTATION
#include "argparser.h"