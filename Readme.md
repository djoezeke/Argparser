# MyArgs | Modern Argument Parser

## Overview

`Myargs` is a lightweight and feature-rich command-line argument parsing library for C/C++.
It offers a modern and intuitive interface allowing for straightforward argument configuration and parsing.

## 📖 Description

A lightweight header-only library for parsing command-line arguments, including support for flags and keyword arguments in an elegant manner.

## ✨ Features

- Parse keyword arguments
- Parse positional arguments
- Parse flags
- Set default values for arguments
- Print help messages

MyArgs distinguishes 3 different types of arguments:

| Type    | Functin   | Description                                                             |
| ------- | --------- | ----------------------------------------------------------------------- |
| `arg`   | add_arg   | named positional arguments (e.g. file)                                  |
| `flag`  | add_flag  | a boolean argument that is by default false (e.g. --verbose)            |
| `kwarg` | add_kwarg | keyworded-arguments that require a key and a value, (e.g. --variable=5) |

### 📝 Supported Syntax

```
--help --verbose --input=file.txt
-hvi=file.txt
-h --verbose -i file.txt
--long value
```

## 🛠️ Installation

To use MyArgs in your project, simply include the `myargs.h` header file in your source files.

```cpp
#include "myargs.h"
```

## 🚀 Usage

```c
#include "myargs.h"

int main(int argc, char *argv[])
{
    ArgumentParser parser;

    init_parser(&parser, NULL, NULL, NULL, NULL, 1);

    add_flag(&parser, 'v', "verbose", "Enable verbose mode");
    add_flag(&parser, 's', "store", "Save file Name");
    add_kwarg(&parser, 'c', "count", 0, NULL, "Number of times");

    parse_args(&parser, argc, argv);

    int verbose = get_flag(&parser, "verbose");
    int store = get_flag(&parser, "store");
    int help = get_flag(&parser, "help");
    const char *count = get_kwarg(&parser, "count");

    if (help)
        print_help(&parser, 1, 1, 1, 1);
    if (count)
        printf("Count: %s\n", count);
    if (store)
        printf("Store: %d\n", store);
    if (verbose)
        printf("Verbose: %d\n", verbose);

    free_parser(&parser);

    return 0;
}
```

### Example Help

```sh
$ ./sample --help
Welcome to MyArgs
Usage: ./sample file.txt -v [FILE] [-h | -v ] [--output FILE]  [options...]
            file.txt : Output path [required]
            -v : Verbose Output [default: false]

Options:
               -k : An implicit int parameter [implicit: "3", required]
       -a,--alpha : An optional float parameter with default value [default: 0.6]
        -b,--beta : An optional float parameter with std::optional return [default: none]
     -n,--numbers : An int vector, comma separated [required]
          --files : multiple arguments [required]
       -c,--color : An Enum input [allowed: <red, blue, green>, required]
     -v,--verbose : A flag to toggle verbose [implicit: "true", default: false]
           --help : print help [implicit: "true", default: false]
```

## Compiler Compatibilty

| Compiler | Min Version |
| :-: | :-: |
| GNU G++ | 13 |
| Clang | 17 |

> [!NOTE]
>
> Although currently the project has been properly verified using only the G++ and Clang compilers it should work fine with other compilers like MSVC.

## License 📄

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing 🤝

Contributions are welcome! Please open an issue or submit a pull request on GitHub.

## Acknowledgements 🙏

MyArgs is inspired by Python Argparse and aims to provide a simple and lightweight solution for C/C++ projects.
