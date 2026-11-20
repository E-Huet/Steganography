#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
#include <stdexcept>

//#include <typeinfo>

#include "Encode.h"
#include "FileManager.h"


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

    std::string* tab = new std::string[argc];
    for (int i = 0; i < argc; i++)
    {
        tab[i] = argv[i];
       std::cout << tab[i] << "\n";
    }

    std::cout << argc << std::endl;
    if (argc > 1 && tab[1] == "encode")
    {
        if (argc != 5)
        {
            throw std::runtime_error("Wrong number of arguments");
        }
        std::cout << "fonctionne" << std::endl;
        SetMessage(tab[2], Encode(tab[3], tab[5]));
    }
    else if (argc > 1 && tab[1] == "decode")
    {
        if (argc != 4)
        {
            throw std::runtime_error("Wrong number of arguments");
        }
        std::cout << "nop" << std::endl;
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
