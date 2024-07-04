/*
** EPITECH PROJECT, 2023
** event_manage.c
** File description:
** managing event
*/

#include "my.h"

int is_in_hitbox(sfVector2i pos, int index)
{
    int resx = pos.x - POSITION[index].x;
    int resy = pos.y - POSITION[index].y;

    if (resx < RESIZE[index].x && resx > 0)
        if (resy < RESIZE[index].y && resy > 0)
            return 1;
    return 0;
}

void manage_sprite_hover(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, int k)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);
    sfIntRect rect;

    if (is_in_hitbox(pos, k) == 1) {
        rect = get_rect(k, 1);
        sfSprite_setTextureRect(sprites[k].sprite, rect);
    } else {
        rect = get_rect(k, 0);
        sfSprite_setTextureRect(sprites[k].sprite, rect);
    }
}

void manage_hover(sfRenderWindow *window, sprite_t *sprites, action_t *cursor)
{
    for (int k = 0; k < NB_MODES; k++)
        manage_sprite_hover(window, sprites, cursor, MODES[k]);
    for (int k = 0; k < NB_MENUS; k++)
        manage_sprite_hover(window, sprites, cursor, MENUS[k]);
    if (cursor->forme != SQR_SHAPE)
        manage_sprite_hover(window, sprites, cursor, SQR_SHAPE);
    if (cursor->forme != CRC_SHAPE)
        manage_sprite_hover(window, sprites, cursor, CRC_SHAPE);
}
