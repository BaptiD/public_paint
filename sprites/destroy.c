/*
** EPITECH PROJECT, 2023
** paint
** File description:
** sprites_destroy.c
*/

#include "my.h"

void destroy_sprites(sprite_t *sprites)
{
    for (int k = 0; k < SIZE_TAB; k++) {
        sfSprite_destroy(sprites[k].sprite);
        sfTexture_destroy(sprites[k].texture);
    }
    free(sprites);
}
