
/**
 * Example usage:
 *
 * int main(int argc, char *argv[]) {
 *     ArgumentParser *parser = new_parser("my_program", "Usage: my_program [options]", "This is a sample program.", "Epilog message", 1);
 *     add_arg(parser, 'o', "output", 1, 1, "default_output.txt", "Output file");
 *     add_kwarg(parser, 'v', "verbose", 0, "false", "Enable verbose mode");
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

// TODO : nargs
// TODO : arg parsing without - or --
// TODO : Complete C++ Wrapper
// TODO : Reimplement print_args
// TODO : Documentation
// TODO : Modify README

#ifndef DJOEZEKE_MYARGS_H
#define DJOEZEKE_MYARGS_H

#include <stdio.h>  // for printf
#include <stdlib.h> // for realloc
#include <string.h> // for strdup strlen
#include <stdarg.h>
#include <stdbool.h>

#ifdef __cplusplus
#include <iostream>
#include <exception>
#endif //__cplusplus

#define MYARGS_VERSION_MAJOR 0
#define MYARGS_VERSION_MINOR 1
#define MYARGS_VERSION_PATCH 0

#ifdef MYARGS_DEBUG
#endif // MYARGS_DEBUG
#define MYARGS_THEME_HELP
#ifdef MYARGS_THEME_HELP
#define ST "\e[0;32m" // symbol
#define NT "\e[0;30m" // name
#define RT "\e[0;33m" // required
#define DT "\e[0;33m" // default
#define FT "\e[0;30m" // allowed
#define FT "\e[0;30m" // implicit
#define CC "\e[0;34m" // colon
#define NC "\e[0;30m" // none
#define HT "\e[0;30m" //
#else
#define TNAME(x)
#define TIMEIT()
#endif // MYARGS_THEME_HELP

#pragma region STRUCTURES

/**
 * Represents the type of an argument.
 */
typedef enum Type
{
    FLAG,  /**< A flag argument, which is a boolean switch. */
    KWARG, /**< A keyword argument, which has a name and a value. */
    ARG,   /**< A positional argument, which is required and has a value. */
} Type;

typedef struct ArgumentError_t
{
    const char *argument;
    const char *message;
} ArgumentError_t;

typedef struct ArgumentTypeError_t
{
    ArgumentError_t *error;
} ArgumentTypeError_t;

/**
 * Represents an argument in the argument parser.
 */
typedef struct
{
    char *name;    /**< The name of the argument. */
    char sym;      /**< The short symbol for the argument. */
    int required;  /**< Whether the argument is required. */
    char *help;    /**< The help message for the argument. */
    Type type;     /**< The type of the argument (FLAG, KWARG, ARG). */
    int count;     /**< The number of arguments expected. */
    char *def_val; /**< The default value for the argument. */
    union
    {
        char *value;   /**< The value of the argument. */
        char **values; /**< The values of the argument if multiple. */
    };

} Argument;

/**
 * Represents the argument parser.
 */
typedef struct ArgumentParser
{
    char *program;       /**< The name of the program. */
    char *usage;         /**< The usage message. */
    char *epilog;        /**< The epilog message. */
    int count;           /**< The number of arguments. */
    char *description;   /**< The description of the program. */
    Argument *arguments; /**< The list of arguments. */
    char prefix_char;
    const char *argument_default;
    bool add_help;
    bool allow_abbrev;
    bool exit_on_error;
} ArgumentParser;

#ifdef __cplusplus

class ArgumentError : std::exception
{
private:
    ArgumentError_t m_Error;

public:
    const char *what() { return ""; };
};

class ArgumentTypeError : ArgumentError
{
};

class Argparse
{
private:
    ArgumentParser m_Parser;

public:
    Argparse();
    Argparse(std::string program, std::string usage, std::string description, std::string epilog);
    ~Argparse();

    void Help(int description = 1, int usage = 1, int epilog = 1, int group = 1);
    void Parse(int argc, char *argv[]);

    int GetFlag(const char *name);
    const char *GetArg(const char *name);
    const char *GetKwarg(const char *name);

    void AddFlag(char sym, const char *name, const char *help);
    void AddKwarg(char sym, const char *name, int required, const char *default_value, const char *help);
    void AddArg(char sym, const char *name, int required, int nargs, const char *default_value, const char *help);
};

#endif // __cplusplus

#pragma endregion // STRUCTURES

#pragma region DECLARATIONS

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

    /**
     * Prints the help message.
     *
     * @param parser The ArgumentParser instance.
     * @param p program.
     * @param d description.
     * @param u usage.
     * @param e epilog.
     * @param c prefix_chars
     * @param h add_help
     * @param a allow_abbrev
     * @param r exit_on_error
     * @param D argument_default
     *
     * Example usage:
     * print_help(parser, 1, 1, 1, 0);
     */
    void parser(ArgumentParser *parser, const char *format, ...);

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
     * ArgumentParser parser;
     * init_parser(&parser, "my_program", "Usage: my_program [options]", "This is a sample program.", "Epilog message", 1);
     */
    void init_parser(ArgumentParser *parser, const char *program, const char *usage, const char *description, const char *epilog);

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
     * add_arg(parser, 'o', "output", 1, 1, "default_output.txt", "Output file");
     */
    void add_arg(ArgumentParser *parser, char sym, const char *name, int required, int nargs, const char *default_value, const char *help);

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
     * add_kwarg(parser, 'v', "verbose", 0, "false", "Enable verbose mode");
     */
    void add_kwarg(ArgumentParser *parser, char sym, const char *name, int required, const char *default_value, const char *help);

    /**
     * Adds a flag argument to the argument parser.
     *
     * @param parser The ArgumentParser to add the argument to.
     * @param sym The short symbol for the argument.
     * @param name The long name for the argument.
     * @param help The help message for the argument.
     *
     * Example usage:
     * add_flag(parser, 'h', "help", "Show help message");
     */
    void add_flag(ArgumentParser *parser, char sym, const char *name, const char *help);

    /**
     * Parses the command-line arguments.
     *
     * @param parser The ArgumentParser instance.
     * @param argc The argument count.
     * @param argv The argument vector.
     *
     * Example usage:
     * parse_args(parser, argc, argv);
     */
    void parse_args(ArgumentParser *parser, int argc, char *argv[]);

    /**
     * Retrieves the value of an argument.
     *
     * @param parser The ArgumentParser instance.
     * @param name The name of the argument.
     * @return The value of the argument.
     *
     * Example usage:
     * const char *output = get_arg(parser, "output");
     */
    const char *get_arg(ArgumentParser *parser, const char *name);

    /**
     * Retrieves the value of a keyword argument.
     *
     * @param parser The ArgumentParser instance.
     * @param name The name of the keyword argument.
     * @return The value of the keyword argument.
     *
     * Example usage:
     * const char *verbose = get_kwarg(parser, "verbose");
     */
    const char *get_kwarg(ArgumentParser *parser, const char *name);

    /**
     * Retrieves the value of a flag argument.
     *
     * @param parser The ArgumentParser instance.
     * @param name The name of the flag argument.
     * @return The value of the flag argument.
     *
     * Example usage:
     * int help = get_flag(parser, "help");
     */
    int get_flag(ArgumentParser *parser, const char *name);

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
     * print_help(parser, 1, 1, 1, 0);
     */
    void print_help(ArgumentParser *parser, int description, int usage, int epilog, int group);

    /**
     * Prints the help message.
     *
     * @param parser The ArgumentParser instance.
     *
     * Example usage:
     * print_flag_help(parser, 1, 1, 1, 0);
     */
    void print_arg_help(ArgumentParser *parser, int i);

    /**
     * Prints the help message.
     *
     * @param parser The ArgumentParser instance.
     *
     * Example usage:
     * print_flag_help(parser, 1, 1, 1, 0);
     */
    void print_flag_help(ArgumentParser *parser, int i);

    /**
     * Prints the help message.
     *
     * @param parser The ArgumentParser instance.
     *
     * Example usage:
     * print_flag_help(parser, 1, 1, 1, 0);
     */
    void print_kwarg_help(ArgumentParser *parser, int i);

    /**
     * Frees the memory allocated for the ArgumentParser instance.
     *
     * @param parser The ArgumentParser instance.
     *
     * Example usage:
     * free_parser(parser);
     */
    void free_parser(ArgumentParser *parser);

#ifdef __cplusplus
}
#endif //__cplusplus

#pragma endregion // DECLARATIONS

#pragma region DEFINATIONS

void parser(ArgumentParser *parser, const char *format, ...)
{

    parser->program = NULL;
    parser->usage = NULL;
    parser->description = NULL;
    parser->epilog = NULL;
    parser->arguments = NULL;
    parser->count = 0;
    parser->prefix_char = '-';
    parser->add_help = true;
    parser->allow_abbrev = true;
    parser->exit_on_error = true;

    if (format != NULL)
    {
        va_list args;

        va_start(args, format);

        size_t format_lenght = strlen(format);
        char cc;

        for (size_t i = 0; i < format_lenght; i++)
        {
            if (format[i] == '%')
            {
                i++;

                if (format[i] == 'p') // program
                {
                    parser->program = strdup(va_arg(args, const char *));
                }
                else if (format[i] == 'u') // usage
                {
                    parser->usage = strdup(va_arg(args, const char *));
                }
                else if (format[i] == 'd') // description
                {
                    parser->description = strdup(va_arg(args, const char *));
                }
                else if (format[i] == 'D') // argument_default
                {
                    parser->argument_default = strdup(va_arg(args, const char *));
                }
                else if (format[i] == 'e') // epilog
                {
                    parser->program = strdup(va_arg(args, const char *));
                }
                else if (format[i] == 'c') // prefix_chars
                {
                    parser->prefix_char = va_arg(args, int);
                }
                else if (format[i] == 'h') // add_help
                {
                    parser->add_help = va_arg(args, int);
                }
                else if (format[i] == 'a') // allow_abbrev
                {
                    parser->allow_abbrev = va_arg(args, int);
                }
                else if (format[i] == 'r') // exit_on_error
                {
                    parser->exit_on_error = va_arg(args, int);
                }
            }
        }
        // Clean up argument list
        va_end(args);
    }

    if (parser->add_help)
    {
        add_flag(parser, 'h', "help", "Shows this help Menu");
    }
};

void init_parser(ArgumentParser *parser, const char *program, const char *usage, const char *description, const char *epilog)
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
        add_flag(parser, 'h', "help", "Shows this help Menu");
    }
}

void add_arg(ArgumentParser *parser, char sym, const char *name, int required, int nargs, const char *default_value, const char *help)
{
    parser->arguments = (Argument *)realloc(parser->arguments, sizeof(Argument) * (parser->count + 1));
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

void add_kwarg(ArgumentParser *parser, char sym, const char *name, int required, const char *default_value, const char *help)
{
    parser->arguments = (Argument *)realloc(parser->arguments, sizeof(Argument) * (parser->count + 1));
    parser->arguments[parser->count].name = strdup(name);
    parser->arguments[parser->count].required = required;
    parser->arguments[parser->count].def_val = default_value ? strdup(default_value) : NULL;
    parser->arguments[parser->count].value = NULL;
    parser->arguments[parser->count].sym = sym ? sym : '0';
    parser->arguments[parser->count].help = help ? strdup(help) : NULL;
    parser->arguments[parser->count].type = KWARG;
    parser->count++;
}

void add_flag(ArgumentParser *parser, char sym, const char *name, const char *help)
{
    parser->arguments = (Argument *)realloc(parser->arguments, sizeof(Argument) * (parser->count + 1));
    parser->arguments[parser->count].name = strdup(name);
    parser->arguments[parser->count].required = 0;
    parser->arguments[parser->count].def_val = NULL;
    parser->arguments[parser->count].value = NULL;
    parser->arguments[parser->count].sym = sym ? sym : '0';
    parser->arguments[parser->count].help = help ? strdup(help) : NULL;
    parser->arguments[parser->count].type = FLAG;
    parser->count++;
}

void parse_args(ArgumentParser *parser, int argc, char *argv[])
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

const char *get_arg(ArgumentParser *parser, const char *name)
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

const char *get_kwarg(ArgumentParser *parser, const char *name)
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

int get_flag(ArgumentParser *parser, const char *name)
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

void print_arg_help(ArgumentParser *parser, int i)
{
    printf("-%c --%s ", parser->arguments[i].sym ? parser->arguments[i].sym : ' ', parser->arguments[i].name);
    printf("(required: %d , [%s] ) ", parser->arguments[i].required, parser->arguments[i].def_val ? parser->arguments[i].def_val : "None");
    printf("= %s \n", parser->arguments[i].help ? parser->arguments[i].help : "No description");
};

void print_flag_help(ArgumentParser *parser, int i)
{
    printf("-" FT "%c" NC "--" NT "%s " NC, parser->arguments[i].sym ? parser->arguments[i].sym : '\0', parser->arguments[i].name);
    printf(CC ":" NC HT "%s" NC "\n", parser->arguments[i].help ? parser->arguments[i].help : "");
};

void print_kwarg_help(ArgumentParser *parser, int i)
{
    // -c, --color : An Enum input [allowed:<red, blue, green>, required]

    printf("-" FT "%c" NC "--" NT "%s " NC, parser->arguments[i].sym ? parser->arguments[i].sym : '\0', parser->arguments[i].name);
    printf(CC ":" NC HT "%s" NC, parser->arguments[i].help ? parser->arguments[i].help : "");

    printf("[" NC HT "%s" NC, parser->arguments[i].help ? parser->arguments[i].help : "");

    printf("[" NC "required " NC CC ": " NC " %d , [%s] ) ", parser->arguments[i].required, parser->arguments[i].def_val ? parser->arguments[i].def_val : "");
};

void print_help(ArgumentParser *parser, int description, int usage, int epilog, int group)
{
    if (parser == NULL)
    {
        return;
    }

    for (int i = 0; i < parser->count; i++)
    {
        if (parser->arguments[i].type == FLAG)
        {
            print_flag_help(parser, i);
        }
        else if (parser->arguments[i].type == KWARG)
        {
            print_kwarg_help(parser, i);
        }
        else
        {
            print_arg_help(parser, i);
        }
    }
}

void free_parser(ArgumentParser *parser)
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

#ifdef __cplusplus

Argparse::Argparse()
{
    init_parser(&m_Parser, "", "", "", "");
};

Argparse::Argparse(std::string program, std::string usage, std::string description, std::string epilog)
{
    init_parser(&m_Parser, program.c_str(), usage.c_str(), description.c_str(), epilog.c_str());
}

void Argparse::Help(int description, int usage, int epilog, int group)
{
    print_help(&m_Parser, description, usage, epilog, group);
};

const char *Argparse::GetArg(const char *name)
{
    return get_arg(&m_Parser, name);
};

int Argparse::GetFlag(const char *name)
{
    return get_flag(&m_Parser, name);
};

const char *Argparse::GetKwarg(const char *name)
{
    return get_kwarg(&m_Parser, name);
};

void Argparse::Parse(int argc, char *argv[])
{
    parse_args(&m_Parser, argc, argv);
};

void Argparse::AddFlag(char sym, const char *name, const char *help)
{
    add_flag(&m_Parser, sym, name, help);
};

void Argparse::AddArg(char sym, const char *name, int required, int nargs, const char *default_value, const char *help)
{
    add_arg(&m_Parser, sym, name, required, nargs, default_value, help);
};

void Argparse::AddKwarg(char sym, const char *name, int required, const char *default_value, const char *help)
{
    add_kwarg(&m_Parser, sym, name, required, default_value, help);
};

Argparse::~Argparse()
{
    free_parser(&m_Parser);
}

#endif // __cplusplus

#pragma endregion // DEFINATIONS

#endif // DJOEZEKE_MYARGS_H