/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** FileNotFound
*/

#ifndef LIBLOADER_FILENOTFOUND_HPP
#define LIBLOADER_FILENOTFOUND_HPP

#include <exception>
#include <string>
#include <filesystem>

namespace Exceptions
{
    class FileNotFound : std::exception
    {
        public:
            explicit FileNotFound(std::string const &path) noexcept;
            explicit FileNotFound(std::filesystem::path const &path) noexcept;

            [[nodiscard]] char const *what() const noexcept override;

        protected:
            std::string _message;
    };

} // Exceptions

#endif //LIBLOADER_FILENOTFOUND_HPP
