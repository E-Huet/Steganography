#include <string>
#include <fstream>
#include <iostream>
#include <bitset>
#include <stdexcept>
#include <vector>

#include "Parser.h"
#include "Utilities.h"


/// Récup les octets autres que les pixels + mettre avec les pixels dans un vector -> c'est ça qu'on envoie à CreateNewImg
/// 
/// Rendre le code plus beau


void CheckFile(std::ifstream& file)
{
    if (!file.is_open())
    {
        throw std::runtime_error("File can't be opened");
    }
	
    file.seekg(0, std::ios::beg);
	char octet1;
	file.read(&octet1, 1);
	file.seekg(0, std::ios::cur);
	char octet2;
	file.read(&octet2, 1);

	std::cout << "Octet 1 : " << octet1 << " | Octet 2 : " << octet2 << std::endl;

    if (octet1 != 'B' || octet2 != 'M')
    {
        throw std::runtime_error("Not a BMP file");
    }
}

std::string GetMessage(std::string path_img)
{
    std::ifstream read_file(path_img, std::ios::binary);

	CheckFile(read_file);
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

void CreateNewImg(std::string& path_new_img, std::vector<char> new_octets)
{
	std::ofstream new_file(path_new_img);

	for (int i = 0; i < new_octets.size(); i++)
	{
		new_file.write(&new_octets[i], 1);
	}
}

void SetMessage(std::string& path_old_img, std::string& path_new_img, std::string message_code)
{
	std::vector<char> new_octets = {};

	std::ifstream file;
	file.open(path_old_img, std::ios::binary | std::ios::in | std::ios::out);

	CheckFile(file);
	
	file.seekg(0, std::ios::end);
	int size = file.tellg();
	std::cout << "Size : " << size;
	int pos_cursor = 0;

	for (int i = 0; i < 54; i++)
	{
		file.seekg(pos_cursor, std::ios::beg);
		char octet;
		file.read(&octet, 1);
		new_octets.push_back(octet);
		pos_cursor++;
	}
	
	int counter = 0;

	std::cout << "...";
	for (int i = 0; i < size - pos_cursor && i < message_code.size(); i++)
	{
		std::cout << "rentre dans boucle 1";
		for (int j = 0; j < 8; j++)
		{
			std::cout << "rentre dans boucle 2";
			char octet;
			file.seekg(pos_cursor, std::ios::beg);
			if (counter == 3)
			{
				pos_cursor++;
				counter = -1;
			}
			else
			{
				std::uint8_t bit = message_code[i] >> j & 1u;
				octet = (file.tellg() & 0xFEu) | bit;
			}
			file.read(&octet, 1);
			new_octets.push_back(octet);

			pos_cursor++;
			counter++;
		}
	}
	CreateNewImg(path_new_img, new_octets);
	file.close();
	return;
}

//std::uint8_t octet = message_code[i] & 1u;
//std::uint8_t bit = octet &j;
