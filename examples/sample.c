#include "../argparser.h"
#include <assert.h>

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
    Argparser argparser;

    // Initialize the argparser with program details and add a help flag automatically
    // init_parser(&argparser, "my_program", "Usage: my_program [options]", "This is a sample program.", "Epilog message");

    parser(&argparser, "%p %u %d %e %D %c", "my_program", "Usage: my_program [options]", "This is a sample program.", "Epilog message", "--log", '-');

    // Add flag arguments
    add_flag(&argparser, 'v', "verbose", "Enable verbose mode");
    add_flag(&argparser, 's', "store", "Save file Name");

    // Add keyword argument
    add_kwarg(&argparser, 'c', "count", 0, NULL, "Number of times");

    // Parse the command-line arguments
    parse_args(&argparser, argc, argv);

    // Retrieve the values of the arguments
    int verbose = get_flag(&argparser, "verbose");
    int store = get_flag(&argparser, "store");
    int help = get_flag(&argparser, "help");
    const char *count = get_kwarg(&argparser, "count");

    // Print the help message if the help flag is set
    if (help)
        print_help(&argparser, 1, 1, 1, 1);

    // Print the values of the arguments
    if (count)
        printf("Count: %s\n", count);
    if (store)
        printf("Store: %d\n", store);
    if (verbose)
        printf("Verbose: %d\n", verbose);

    // Free the memory allocated for the argparser
    free_parser(&argparser);

    return 0;
}