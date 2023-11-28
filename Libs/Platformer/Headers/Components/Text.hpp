/*
** EPITECH PROJECT, 2023
** Libs [WSL: Ubuntu]
** File description:
** Text
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_

    #include <string.h>

struct Text {
    char *_text;

    Text(char *text) {_text = strdup(text);};
};

#endif /* !TEXT_HPP_ */
