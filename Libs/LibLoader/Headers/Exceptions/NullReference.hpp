/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** NullReference
*/

#ifndef LIBLOADER_NULLREFERENCE_HPP
#define LIBLOADER_NULLREFERENCE_HPP

#include <exception>

namespace Exceptions
{
    class NullReference : public std::exception
    {
        public:
            [[nodiscard]] const char *what() const noexcept override;
    };

} // Exceptions

#endif //LIBLOADER_NULLREFERENCE_HPP
