#include <string>
#include "Parser.h"
#include <iostream>
#include <bitset>
#include <fstream>
#include <stdexcept>

std::string GetMessage(std::string path_img)
{
    std::ifstream read_file(path_img, std::ios::binary);

    if (!read_file.is_open())
    {
        throw std::runtime_error("File can't be opened");
    }

    constexpr std::size_t buffer_size = 500;
    char buffer[buffer_size];

    read_file.read(buffer, buffer_size);

    std::streamsize bytes_read = read_file.gcount();

    std::string result(buffer, static_cast<std::size_t>(bytes_read));
    read_file.close();
    return result;
}

void SetMessage(std::string path_img, std::string path_new_img, std::string message_code)
{
	return;
}
