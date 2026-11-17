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
    argument 2 -> old_img.bmp
    argument 3 -> key
    argument 4 -> changed_img.bmp
    argument 5 -> message
    decode
    argument 2 -> changed_img.bmp
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
        if (argc != 6)
        {
            throw std::runtime_error("Wrong number of arguments");
        }
        cout << "fonctionne" << endl;
        SetMessage(tab[2], tab[4], Encode(tab[3], tab[5]));
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
