#include <string>
#include <fstream>
#include <iostream>
#include <bitset>
#include <stdexcept>
#include <vector>

#include "FileManager.h"
#include "Utilities.h"


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

    if (octet1 != 'B' || octet2 != 'M')
    {
        throw std::runtime_error("Not a BMP file");
    }
}

std::uint8_t ReadByte(const std::vector<char>& data,const std::vector<std::size_t>& positions,std::size_t& cursor)
{
    if (cursor + 8 > positions.size())
    {
        throw std::runtime_error("Image too small");
    }

    std::uint8_t byte = 0;
    for (int k = 0; k < 8; k++)                         
    {
        if (GetBit(data[positions[cursor]], 0))           
        {
            byte = SetBit(byte, int(k));
        }
        ++cursor;
    }
    return byte;
}

std::uint32_t Read32(const std::vector<char>& data, std::size_t offset)
{
    return  static_cast<std::uint32_t>(static_cast<unsigned char>(data[offset]))
        | (static_cast<std::uint32_t>(static_cast<unsigned char>(data[offset + 1])) << 8)
        | (static_cast<std::uint32_t>(static_cast<unsigned char>(data[offset + 2])) << 16)
        | (static_cast<std::uint32_t>(static_cast<unsigned char>(data[offset + 3])) << 24);
}

std::vector<std::size_t> GetColorBytePositions(std::vector<char> data)
{
    std::uint32_t pixel_offset = Read32(data, 10);
    std::int32_t  width = static_cast<std::int32_t>(Read32(data, 18));
    std::int32_t  height = static_cast<std::int32_t>(Read32(data, 22));

    std::size_t row_bytes = static_cast<std::size_t>(width) * 3;   // octets utiles
    std::size_t row_size = (row_bytes + 3) / 4 * 4;

    if (height < 0)
    {
        height = -height;
    }
    std::vector<std::size_t> positions;
    positions.reserve(row_bytes * static_cast<std::size_t>(height));

    for (std::int32_t y = 0; y < height; ++y)
    {
        for (std::size_t x = 0; x < row_bytes; ++x)   // s'arrête avant le padding
        {
            positions.push_back(pixel_offset + static_cast<std::size_t>(y) * row_size + x);
        }
    }
    return positions;
}


std::string GetMessage(std::string path_img)
{
    std::ifstream read_file(path_img, std::ios::binary);
    CheckFile(read_file);

    read_file.seekg(0, std::ios::end);
    std::streamsize size = read_file.tellg();

    read_file.seekg(0, std::ios::beg);
    std::vector<char> data(static_cast<std::size_t>(size));
    read_file.read(data.data(), size);

    ///Ce qui est nécessaire pour la fonction RB
    std::vector<std::size_t> positions = GetColorBytePositions(data);
    std::size_t cursor = 0;
    std::uint32_t length = 0;

    for (int i = 0; i < 4; ++i)
    {
        length = (length << 8) | ReadByte(data, positions, cursor);
    }

    std::string message;
    message.reserve(length);
    for (std::uint32_t i = 0; i < length; ++i)
    {
        message += static_cast<char>(ReadByte(data, positions, cursor));
    }
    return message;
}

void CopieImg(std::string& path_new_img, std::vector<char> buffer)
{
	std::ofstream new_file(path_new_img, std::ios::binary);

	if (!new_file.is_open())
	{
		throw std::runtime_error("File can't be opened");
	}

	for (int i = 0; i < buffer.size(); ++i)
	{
		new_file.write(&buffer[i], 1);
	}

	new_file.close();
}

void CodeImg(std::string& path_new_img, std::string message_code)
{
    std::ifstream read_file(path_new_img, std::ios::binary);
    CheckFile(read_file);

    read_file.seekg(0, std::ios::end);
    int size = read_file.tellg();
    std::vector<char> data(size);
    read_file.seekg(0, std::ios::beg);
    read_file.read(data.data(), size);

    std::vector<size_t> pixels_color_positions = GetColorBytePositions(data);

    read_file.close();

    int pos_cursor = 0;

    for (int i = 0; i < message_code.size(); i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (pos_cursor >= pixels_color_positions.size())
            {
                throw std::runtime_error("Message too long for the image");
            }

            std::size_t pos = pixels_color_positions[pos_cursor];
            char octet = data[pos];

            std::uint8_t bit = message_code[i] >> j & 1u;
            octet = (octet & 0xFEu) | bit;
            data[pos] = octet;

            pos_cursor++;
        }
    }

    std::ofstream file(path_new_img, std::ios::binary);
    file.write(data.data(), size);
}

void SetMessage(std::string& path_old_img, std::string& path_new_img, std::string message_code)
{
	std::vector<char> new_octets = {};

	std::ifstream file;
	file.open(path_old_img, std::ios::binary | std::ios::in | std::ios::out);

	CheckFile(file);
	
	file.seekg(0, std::ios::end);
	std::size_t size = file.tellg();
	//std::cout << "Size : " << size;

	file.seekg(0, std::ios::beg);
	std::vector<char> buffer_char(size);
	file.read(buffer_char.data(), size);

	CopieImg(path_new_img, buffer_char);

	CodeImg(path_new_img, message_code);

	file.close();
	return;
}
