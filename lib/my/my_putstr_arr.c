/*
** EPITECH PROJECT, 2023
** my_putchar
** File description:
** put char
*/
#include "my.h"

void my_putstr_arr(char **array)
{
    for (int i = 0; array[i] != NULL; ++i) {
        my_putstr(array[i]);
        my_putchar('\n');
    }
}
