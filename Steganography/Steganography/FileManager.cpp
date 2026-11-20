#include <string>
#include <fstream>
#include <iostream>
#include <bitset>
#include <stdexcept>
#include <vector>

#include "FileManager.h"
#include "Utilities.h"

bool CheckFile(std::string path_img)
{
    std::fstream read_file(path_img, std::ios::binary);
    if (!read_file.is_open())
    {
        throw std::runtime_error("File can't be opened");
    }
   

    /*if (data[0] != 'B' || data[1] != 'M')
    {
        throw std::runtime_error("Not a BMP file");
    }
    */
}



std::uint8_t ReadByte(const std::vector<std::uint8_t>& data,const std::vector<std::size_t>& positions,std::size_t& cursor)
{
    if (cursor + 8 > positions.size())
    {
        throw std::runtime_error("Image too small");
    }
    std::uint8_t byte = 0;
    for (int k = 7; k >= 0; --k)                         
    {
        if (GetBit(data[positions[cursor]], 0))           
        {
            byte = SetBit(byte, int(k));
        }
        ++cursor;
    }
    return byte;
}

std::uint32_t Read32(const std::vector<std::uint8_t>& data, std::size_t offset)
{
    return  static_cast<std::uint32_t>(data[offset])
        | (static_cast<std::uint32_t>(data[offset + 1]) << 8)
        | (static_cast<std::uint32_t>(data[offset + 2]) << 16)
        | (static_cast<std::uint32_t>(data[offset + 3]) << 24);
}


std::vector<std::size_t> GetColorBytePositions(std::vector<std::uint8_t> data)
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
    CheckFile(path_img);
    read_file.seekg(0, std::ios::end);
    std::streamsize size = read_file.tellg();
    std::vector<std::uint8_t> data(static_cast<std::size_t>(size));
    read_file.seekg(0, std::ios::beg);
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
