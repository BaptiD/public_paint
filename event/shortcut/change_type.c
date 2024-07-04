/*
** EPITECH PROJECT, 2023
** change_type.c
** File description:
** change the type of the cursor
*/

#include "my.h"

void change_type(action_t *cursor)
{
    cursor->type += 1;
    if (cursor->type > TYPE_MAX)
        cursor->type = MOUSE;
}
