/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include "my.h"


static char *manage_shift_pressed(char *filename)
{
    for (int k = 0; k != 26; k++)
        if (sfKeyboard_isKeyPressed(k) == sfTrue)
            return my_str_addchar(filename, k + 65, 1);
    for (int k = 0; k != 10; k++)
        if (sfKeyboard_isKeyPressed(k + 26) == sfTrue)
            return my_str_addchar(filename, k + 48, 1);
    if (sfKeyboard_isKeyPressed(sfKeySlash) == sfTrue)
        return my_str_addchar(filename, '/', 1);
    if (sfKeyboard_isKeyPressed(sfKeyPeriod) == sfTrue)
        return my_str_addchar(filename, '.', 1);
    return filename;
}

static char *manage_no_shift_pressed(char *filename)
{
    for (int k = 0; k != 26; k++)
        if (sfKeyboard_isKeyPressed(k) == sfTrue)
            return my_str_addchar(filename, k + 97, 1);
    for (int k = 0; k != 10; k++)
        if (sfKeyboard_isKeyPressed(k + 75) == sfTrue)
            return my_str_addchar(filename, k + 48, 1);
    if (sfKeyboard_isKeyPressed(sfKeyNum8) == sfTrue)
        return my_str_addchar(filename, '_', 1);
    return filename;
}

char *add_chars(char *filename)
{
    if (sfKeyboard_isKeyPressed(sfKeyLShift) == sfTrue)
        return manage_shift_pressed(filename);
    else
        return manage_no_shift_pressed(filename);
}
