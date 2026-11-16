#pragma once

/// <summary>
/// Renvoie le message codé dans l'image en paramètre
/// </summary>
/// <param name="path_img"></param>
/// <returns></returns>
std::string GetMessage(std::string path_img);

/// <summary>
/// Code le message donné en paramètre dans l'image donnée en paramètre
/// </summary>
/// <param name="path_old_img"></param>
/// <param name="path_new_img"></param>
/// <param name="message_code"></param>
void SetMessage(std::string path_old_img, std::string path_new_img, std::string message_code);