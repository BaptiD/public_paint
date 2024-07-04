/*
** EPITECH PROJECT, 2024
** my_strcat_auto self project
** File description:
** desc
*/

#include <stdlib.h>
#include "my.h"

char *my_strcat_auto(char *dest, char *str, int opt)
{
    int dest_len = my_strlen(dest);
    int str_len = my_strlen(str);
    char *dest2 = malloc(sizeof(char) * (dest_len + str_len + 1));

    my_strcpy(dest2, dest);
    my_strcpy(dest2 + dest_len, str);
    dest2[dest_len + str_len] = '\0';
    if (opt == 1)
        free(dest);
    return dest2;
}
