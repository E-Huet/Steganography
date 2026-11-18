#include <string>
#include <fstream>

#include "Parser.h"
#include "Utilities.h"

std::string GetMessage(std::string path_img)
{
	return std::string();
}


void SetMessage(std::string& path_img, std::string message_code)
{
	std::fstream file;
	file.open(path_img, std::ios::binary);

	
	if (!file.is_open())
	{
		std::cout << "Ouverture fail";
		throw std::exception("File can't be opened");
	}
	std::cout << "Ouverture sucess";

	int pos_cursor = 54;
	int counter = 0;

	std::cout << "...";
	for (int i = 0; i < path_img.size()-pos_cursor && i < message_code.size() ; i++) // taille de chemin et pas du fichier, à corriger
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