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
	std::ofstream file;
	file.open(path_img, std::ios::binary);

	if (!file.is_open())
	{
		throw std::exception("File can't be opened");
	}

	int pos_cursor = 54;
	int counter = 0;
	for (int i = 0; i < path_img.size()-pos_cursor || i < message_code.size() ; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			file.seekp(pos_cursor, std::ios::beg);
			//std::uint8_t octet = message_code[i] & 1u;

			std::uint8_t bit = message_code[i] &j;
			//std::uint8_t bit = octet &j;
			
			file.tellp() = (file.tellp() & 0xFEu) | bit;

			pos_cursor++;
			counter++;
			if (counter == 3)
			{
				pos_cursor += 2;
				counter = 0;
			}
		}
	}
	//file.write(text.data(), text.size());

	file.close();
	return;
}