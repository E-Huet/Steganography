#include <string>
#include <fstream>

#include "Parser.h"

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




	//file.write(text.data(), text.size());

	file.close();
	return;
}
