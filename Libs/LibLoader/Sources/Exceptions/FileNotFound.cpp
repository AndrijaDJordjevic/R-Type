/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** FileNotFound
*/


#include "Exceptions/FileNotFound.hpp"

namespace Exceptions
{
    FileNotFound::FileNotFound(std::string const &path) noexcept : _message("File \"" + path + "\" could not be found.") { }
    FileNotFound::FileNotFound(const std::filesystem::path &path) noexcept  : _message("File \"" + path.string() + "\" could not be found.") { }

    char const *FileNotFound::what() const noexcept
    {
        return _message.c_str();
    }

} // Exceptions
