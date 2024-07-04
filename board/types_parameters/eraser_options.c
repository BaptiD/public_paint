/*
** EPITECH PROJECT, 2023
** eraser_options.c
** File description:
** every eraser functions
*/

#include "my.h"

void display_eraser_opt(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor)
{
    sfIntRect rect = get_rect(SHAPES[cursor->forme], 2);

    sfSprite_setTextureRect(sprites[SHAPES[cursor->forme]].sprite, rect);
    sfRenderWindow_drawSprite(window, sprites[SIZE_SELECT].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[SQR_SHAPE].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[CRC_SHAPE].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[SIZE_BAR].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[SIZE_BALL].sprite, NULL);
    rect = get_rect(cursor->forme, 0);
    sfSprite_setTextureRect(sprites[SHAPES[cursor->forme]].sprite, rect);
}
