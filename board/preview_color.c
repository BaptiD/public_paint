/*
** EPITECH PROJECT, 2023
** preview_color.c
** File description:
** preview the color you chose
*/

#include "my.h"

void display_preview(sfRenderWindow *window, action_t *cursor)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(window);

    if (cursor->type == PICKER && sfMouse_isButtonPressed(sfMouseLeft) &&
        is_in_board(pos.x, pos.y))
        sfRenderWindow_drawRectangleShape(window, cursor->preview, NULL);
    sfRenderWindow_setMouseCursorVisible(window, sfTrue);
}

void preview_color_click(sfImage *board, action_t *cursor,
    sfRenderWindow *window)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(window);
    sfVector2f pos_preview = (sfVector2f){pos.x, pos.y - 50};
    int x = pos.x - BOARD_MARG[0];
    int y = pos.y - BOARD_MARG[1];

    cursor->color = sfImage_getPixel(board, x, y);
    sfRectangleShape_setPosition(cursor->preview, pos_preview);
    sfRectangleShape_setFillColor(cursor->preview, cursor->color);
}
