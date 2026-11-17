#include "Encode.h"

std::string Encode(std::string key, std::string message)
{
	std::string message_code;
	int indice_key = 0;
	for (int i = 0; i < message.size(); i++)
	{
		std::uint8_t result_xor = key[indice_key] ^ message[i];
		message_code += result_xor;
		if (indice_key < key.size()-1)
		{
			indice_key++;
		}
		else
		{
			indice_key = 0;
		}
	}
	return message_code;
}