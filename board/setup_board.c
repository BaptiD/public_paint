/*
** EPITECH PROJECT, 2024
** pixels.c
** File description:
** manage pixels
*/

#include "my.h"

void draw_board(sfImage *board_image, sfRenderWindow *window)
{
    sfSprite *board = sfSprite_create();
    sfTexture *board_texture = NULL;

    board_texture = sfTexture_createFromImage(board_image, NULL);
    sfSprite_setTexture(board, board_texture, sfTrue);
    sfSprite_setPosition(board, (sfVector2f){BOARD_MARG[0], BOARD_MARG[1]});
    sfRenderWindow_drawSprite(window, board, NULL);
    sfTexture_destroy(board_texture);
    sfSprite_destroy(board);
}

sfImage *set_board_image(void)
{
    sfImage *board_image = NULL;
    sfColor base_color = {255, 255, 255, 255};

    board_image = sfImage_create(BOARD_SIZE[0], BOARD_SIZE[1]);
    if (board_image == NULL)
        return NULL;
    for (int x = 0; x < BOARD_SIZE[0]; ++x) {
        for (int y = 0; y < BOARD_SIZE[1]; ++y) {
            sfImage_setPixel(board_image, x, y, base_color);
        }
    }
    return board_image;
}
