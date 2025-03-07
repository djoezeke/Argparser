#include "myargs.h"

/**
 * Main function demonstrating the usage of the ArgumentParser.
 *
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return Exit status.
 *
 * Example usage:
 * ./my_program -v -s -c 5
 */
int main(int argc, char *argv[])
{
    ArgumentParser parser;

    // Initialize the parser with program details and add a help flag automatically
    init_parser(&parser, "my_program", "Usage: my_program [options]", "This is a sample program.", "Epilog message", 1);

    // Add flag arguments
    add_flag(&parser, 'v', "verbose", "Enable verbose mode");
    add_flag(&parser, 's', "store", "Save file Name");

    // Add keyword argument
    add_kwarg(&parser, 'c', "count", 0, NULL, "Number of times");

    // Parse the command-line arguments
    parse_args(&parser, argc, argv);

    // Retrieve the values of the arguments
    int verbose = get_flag(&parser, "verbose");
    int store = get_flag(&parser, "store");
    int help = get_flag(&parser, "help");
    const char *count = get_kwarg(&parser, "count");

    // Print the help message if the help flag is set
    if (help)
        print_help(&parser, 1, 1, 1, 1);

    // Print the values of the arguments
    if (count)
        printf("Count: %s\n", count);
    if (store)
        printf("Store: %d\n", store);
    if (verbose)
        printf("Verbose: %d\n", verbose);

    // Free the memory allocated for the parser
    free_parser(&parser);

    return 0;
}