/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu]
** File description:
** NullReference
*/

#include "Exceptions/NullReference.hpp"

namespace Exceptions
{
    const char *NullReference::what() const noexcept
    {
        return "Cannot dereference a null pointer.";
    }
} // Exceptions
