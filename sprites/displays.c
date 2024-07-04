/*
** EPITECH PROJECT, 2023
** paint
** File description:
** displays.c
*/

#include "my.h"

static void display_buttons(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor)
{
    int i = cursor->type + MODES[0];
    sfIntRect rect = get_rect(i, 2);

    sfSprite_setTextureRect(sprites[i].sprite, rect);
    for (int k = 0; k < NB_MODES; k++)
        sfRenderWindow_drawSprite(window, sprites[MODES[k]].sprite, NULL);
    rect = get_rect(i, 0);
    sfSprite_setTextureRect(sprites[i].sprite, rect);
}

void display_ui(sfRenderWindow *window, sprite_t *sprites, action_t *cursor)
{
    sfRenderWindow_drawSprite(window, sprites[BACKGROUND].sprite, NULL);
    display_buttons(window, sprites, cursor);
    for (int k = 0; k < NB_MENUS; k++)
        sfRenderWindow_drawSprite(window, sprites[MENUS[k]].sprite, NULL);
    if (cursor->type == PAINTER)
        display_pencil_opt(window, sprites, cursor);
    if (cursor->type == ERASER)
        display_eraser_opt(window, sprites, cursor);
    if (cursor->type == FILLER)
        display_bucket_opt(window, sprites, cursor);
    if (cursor->type == PICKER)
        display_picker_opt(window, sprites, cursor);
    if (cursor->type == CIRCLE)
        display_circle_opt(window, sprites, cursor);
}
