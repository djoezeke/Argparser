#include <iostream>
#include "myargs.h"

class Argparse
{
private:
    ArgumentParser m_Parser;

public:
    Argparse();
    Argparse(std::string program, std::string usage, std::string description, std::string epilog, int add_help);
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

Argparse::Argparse()
{
    init_parser(&m_Parser, "", "", "", "", 1);
};

Argparse::Argparse(std::string program, std::string usage, std::string description, std::string epilog, int add_help)
{
    init_parser(&m_Parser, program.c_str(), usage.c_str(), description.c_str(), epilog.c_str(), add_help);
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
