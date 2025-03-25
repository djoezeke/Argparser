#include "../myargs.h"

int main(int argc, char *argv[])
{
    // Initialize the parser with program details and add a help flag automatically
    Argparse parser("my_program", "Usage: my_program [options]", "This is a sample program.", "Epilog message", 1);

    // Add flag arguments
    parser.AddFlag('v', "verbose", "Enable verbose mode");
    parser.AddFlag('s', "store", "Save file Name");

    // Add keyword argument
    parser.AddKwarg('c', "count", 0, NULL, "Number of times");

    // Parse the command-line arguments
    parser.Parse(argc, argv);

    // Retrieve the values of the arguments
    int verbose = parser.GetFlag("verbose");
    int store = parser.GetFlag("store");
    int help = parser.GetFlag("help");
    const char *count = parser.GetKwarg("count");

    // Print the help message if the help flag is set
    if (help)
        parser.Help();

    // Print the values of the arguments
    if (count)
        printf("Count: %s\n", count);
    if (store)
        printf("Store: %d\n", store);
    if (verbose)
        printf("Verbose: %d\n", verbose);

    return 0;
}