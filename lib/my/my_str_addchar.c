/*
** EPITECH PROJECT, 2024
** my_str_addchar
** File description:
** desc
*/

#include <stdlib.h>
#include "my.h"

char *my_str_addchar(char *dest, char c, int opt)
{
    int len = my_strlen(dest);
    char *dest2 = malloc((len + 2) * sizeof(char));

    my_strcpy(dest2, dest);
    if (len > 0 && opt == 1)
        free(dest);
    dest2[len] = c;
    dest2[len + 1] = '\0';
    return dest2;
}

char *my_str_delchar(char *str, int opt)
{
    int len = my_strlen(str);
    char *new_str = malloc(sizeof(char) * len);
    int k = 0;

    for (; str[k + 1] != 0; k++)
        new_str[k] = str[k];
    new_str[k] = 0;
    if (opt == 1)
        free(str);
    return new_str;
}
