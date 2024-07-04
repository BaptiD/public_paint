/*
** EPITECH PROJECT, 2023
** my_nb_args_array.c
** File description:
** nb of arguments in array of char *
*/
#include "my.h"

int nb_args_array(char **array_str)
{
    int nb = 0;

    while (array_str[nb] != NULL)
        nb += 1;
    return nb;
}
