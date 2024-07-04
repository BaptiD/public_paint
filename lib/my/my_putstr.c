/*
** EPITECH PROJECT, 2023
** my_putstr
** File description:
** write one-by-one charaters of a string
*/
#include "my.h"

void my_putstr(char const *str)
{
    write(1, str, my_strlen(str));
}
