/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** DlError
*/


#ifndef LIBLOADER_DLERROR_HPP
#define LIBLOADER_DLERROR_HPP

#include <stdexcept>

namespace Exceptions
{
    class DLError : public std::exception
    {
        public:
            explicit DLError(char const *err);
            [[nodiscard]] const char * what() const noexcept override;

        protected:
            char const *error = nullptr;
    };
} // Exceptions

#endif //LIBLOADER_DLERROR_HPP
