/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** DlError
*/


#include "Exceptions/DlError.hpp"

namespace Exceptions
{
    DLError::DLError(const char *err) : error(err) { }

    const char *DLError::what() const noexcept
    {
        return error;
    }
} // Exceptions
