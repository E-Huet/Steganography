#pragma once
#include <string>

/// <summary>
/// Renvoi le paramètre "message" codé en XOR avec le paramètre "key".
/// </summary>
/// <param name="key"></param>
/// <param name="message"></param>
/// <returns></returns>
std::string Encode(std::string key, std::string message);

std::string Decode(std::string key, std::string message);