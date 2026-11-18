#include <string>
#include <fstream>
#include <iostream>
#include <bitset>
#include <stdexcept>
#include <vector>

#include "Parser.h"
#include "Utilities.h"

bool CheckFile(std::string path_img)
{
    std::ifstream read_file(path_img, std::ios::binary);
    if (!read_file.is_open())
    {
        throw std::runtime_error("File can't be opened");
    }
    read_file.seekg(0, std::ios::end);
    std::streamsize size = read_file.tellg();
    std::vector<std::uint8_t> data(static_cast<std::size_t>(size));

    if (data[0] != 'B' || data[1] != 'M')
    {
        throw std::runtime_error("Not a BMP file");
    }
}

std::string GetMessage(std::string path_img)
{
    std::ifstream read_file(path_img, std::ios::binary);

    if (!CheckFile(path_img))
    {
        throw std::runtime_error("Error File");
    }
    read_file.seekg(0, std::ios::beg);
    std::size_t cursor = 0;
    std::uint32_t length = 0;
    for (int i = 0; i < 4; ++i)
    {
        length = (length << 8);
    }
    constexpr std::size_t buffer_size = 500;
    char buffer[buffer_size];

    read_file.read(buffer, buffer_size);

    std::streamsize bytes_read = read_file.gcount();
    std::string result(buffer, static_cast<std::size_t>(bytes_read));
    read_file.close();
    return result;
}


void SetMessage(std::string& path_old_img, std::string& path_new_img, std::string message_code)
{
	std::fstream file;
	file.open(path_old_img, std::ios::binary | std::ios::ate);
	int size = file.tellp();
	
	if (!file.is_open())
	{
		//std::cout << "Ouverture fail";
		throw std::exception("File can't be opened");
	}
	//std::cout << "Ouverture sucess";

	int pos_cursor = 54;
	int counter = 0;

	std::cout << "...";
	for (int i = 0; i < size - pos_cursor && i < message_code.size() ; i++)
	{
		std::cout << "rentre dans boucle 1";
		for (int j = 0; j < 8; j++)
		{
			std::cout << "rentre dans boucle 2";
			file.seekp(pos_cursor, std::ios::beg);
			//std::uint8_t octet = message_code[i] & 1u;

			std::uint8_t bit = message_code[i] >> j &1u;
			//std::uint8_t bit = octet &j;
			
			char test;
			file.read(&test, 1);
			test = (file.tellp() & 0xFEu) | bit;

			file.write(&test, 1);

			pos_cursor++;
			counter++;
			if (counter == 3)
			{
				pos_cursor += 2;
				counter = 0;
			}
		}
	}
	file.close();
	return;
}