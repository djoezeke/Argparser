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
    ArgumentParser_t argparser;

    // Initialize the argparser with program details and add a help flag automatically
    // init_parser(&argparser, "my_program", "Usage: my_program [options]", "This is a sample program.", "Epilog message");

    ArgumentParserInit(&argparser, "my_program", "Usage: my_program [options]", "This is a sample program.", "Epilog message");

    // Add flag arguments
    ArgumentParserAddFlag(&argparser, 'v', "verbose", "Enable verbose mode");
    ArgumentParserAddFlag(&argparser, 's', "store", "Save file Name");

    // Add keyword argument
    ArgumentParserAddKwarg(&argparser, 'c', "count", 0, NULL, "Number of times");

    // Parse the command-line arguments
    ArgumentParserParseArgs(&argparser, argc, argv);

    // Retrieve the values of the arguments
    int verbose = ArgumentParserGetFlag(&argparser, "verbose");
    int store = ArgumentParserGetFlag(&argparser, "store");
    int help = ArgumentParserGetFlag(&argparser, "help");
    const char *count = ArgumentParserGetKwarg(&argparser, "count");

    // Print the help message if the help flag is set
    if (help)
        ArgumentParserPrintHelp(&argparser);

    // Print the values of the arguments
    if (count)
        printf("Count: %s\n", count);
    if (store)
        printf("Store: %d\n", store);
    if (verbose)
        printf("Verbose: %d\n", verbose);

    // Free the memory allocated for the argparser
    ArgumentParserFree(&argparser);

    return 0;
}