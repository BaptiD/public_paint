/*
** EPITECH PROJECT, 2023
** save_file.c
** File description:
** save_file in differents formats
*/

#include "my.h"

sfBool save_image_as_file(char *username, int format, sfImage *board,
    char *file_name)
{
    sfBool result = sfFalse;
    char *file = NULL;
    char *temp = NULL;

    if (username != NULL) {
        temp = my_str_addchar(username, '_', 0);
        file_name = my_strcat_auto(temp, file_name, 1);
    }
    if (format == 1)
        file = my_strcat_auto(file_name, ".jpg", 0);
    if (format == 2)
        file = my_strcat_auto(file_name, ".png", 0);
    if (format == 3)
        file = my_strcat_auto(file_name, ".bmp", 0);
    if (file != NULL)
        result = sfImage_saveToFile(board, file);
    return result;
}
