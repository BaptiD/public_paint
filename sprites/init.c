/*
** EPITECH PROJECT, 2023
** paint
** File description:
** sprites_init.c
*/

#include "my.h"

static void init_sprites_params(sprite_t *sprites)
{
    sfIntRect rect;

    for (int k = 0; k < SIZE_TAB; k++) {
        if (k != PALET_COLOR && k != BUCKET && k != ERASER_PNG) {
            rect = get_rect(k, 0);
            sfSprite_setTextureRect(sprites[k].sprite, rect);
        }
    }
    sfSprite_setColor(sprites[BLK_BCK].sprite, MENU_COLORS[1]);
}

sprite_t *init_spritesarray(void)
{
    sprite_t *sprites = malloc(sizeof(sprite_t) * SIZE_TAB);
    sprite_t temp;
    sfVector2f size;

    for (int k = 0; k < SIZE_TAB; k++) {
        temp.sprite = sfSprite_create();
        temp.texture = sfTexture_createFromFile(IMG_PATH[k], NULL);
        sfSprite_setPosition(temp.sprite, POSITION[k]);
        sfSprite_setTexture(temp.sprite, temp.texture, sfTrue);
        size.x = RESIZE[k].x / IMG_SIZE[k][0];
        size.y = RESIZE[k].y / IMG_SIZE[k][1];
        sfSprite_scale(temp.sprite, size);
        sprites[k] = temp;
    }
    init_sprites_params(sprites);
    return sprites;
}
