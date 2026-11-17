#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
#include <stdexcept>

//#include <typeinfo>

#include "Encode.h"
#include "Parser.h"

using namespace std;

int main(int argc, char** argv)
{
    /*

    argument 1 -> encode / decode
    encode
    argument 2 -> img.bmp
    argument 3 -> key
    argument 4 -> message
    decode
    argument 2 -> img.bmp
    argument 3 -> key

    */

    string* tab = new string[argc];
    for (int i = 0; i < argc; i++)
    {
        tab[i] = argv[i];
        cout << tab[i] << "\n";
    }

    cout << argc << endl;
    if (argc > 1 && tab[1] == "encode")
    {
        if (argc != 5)
        {
            throw std::runtime_error("Wrong number of arguments");
        }
        cout << "fonctionne" << endl;
        SetMessage(tab[2], Encode(tab[3], tab[4]));
    }
    else if (argc > 1 && tab[1] == "decode")
    {
        if (argc != 4)
        {
            throw std::runtime_error("Wrong number of arguments");
        }
        cout << "nop" << endl;
        Encode(tab[3], GetMessage(tab[2]));
    }
    else
    {
        throw std::runtime_error("Command invalid");
    }

    return 0;
}

/*
std::cout << typeid(command).name() << '\n';*/
