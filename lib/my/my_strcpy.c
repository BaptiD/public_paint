/*
** EPITECH PROJECT, 2024
** my_strcpy
** File description:
** fonction that copies a string into another
*/

#include "my.h"

char *my_strcpy(char *dest, char *src)
{
    int k = 0;

    while (src[k] != '\0') {
        dest[k] = src[k];
        k++;
    }
    dest[k] = '\0';
    return dest;
}
