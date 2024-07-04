/*
** EPITECH PROJECT, 2024
** my_hunter.c
** File description:
** my hunter game
*/

#include "my.h"

sfIntRect get_rect(int index, int offset)
{
    sfIntRect rect;

    rect.left = RESIZE[index].x * offset;
    rect.top = 0;
    rect.width = RESIZE[index].x;
    rect.height = RESIZE[index].y;
    return rect;
}

sfText *init_text(sfFont *font)
{
    sfText *text = sfText_create();

    sfText_setColor(text, sfBlack);
    sfText_setPosition(text, (sfVector2f){725, 523});
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 25);
    return text;
}
