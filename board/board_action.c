/*
** EPITECH PROJECT, 2023
** pixels_drawing.c
** File description:
** pixel managing
*/

#include "my.h"

void draw_only_on_board(int x, int y, sfImage *board, action_t *cursor)
{
    if (x >= 0 && x < BOARD_SIZE[0] && y >= 0 && y < BOARD_SIZE[1]) {
        if (cursor->type == PAINTER || cursor->type == SQUARE)
            sfImage_setPixel(board, x, y, cursor->color);
        if (cursor->type == ERASER)
            sfImage_setPixel(board, x, y, sfWhite);
    }
}

static void draw_square(int posx, int posy, sfImage *board, action_t *cursor)
{
    for (int x = posx - cursor->size; x != posx + cursor->size; ++x)
        for (int y = posy - cursor->size; y != posy + cursor->size; ++y)
            draw_only_on_board(x, y, board, cursor);
}

static void draw_if_circle(sfVector2i pos, action_t *cursor,
    sfImage *board, sfVector2i orgn)
{
    if (pos.x * pos.x + pos.y * pos.y <= cursor->size * cursor->size)
        if (orgn.x + pos.x >= 0 &&
            orgn.x + pos.x < BOARD_SIZE[0] &&
            orgn.y + pos.y >= 0 &&
            orgn.y + pos.y < BOARD_SIZE[1])
            draw_only_on_board(orgn.x + pos.x, orgn.y + pos.y, board, cursor);
}

static void draw_circle(sfImage *board, sfVector2i pos, action_t *cursor)
{
    for (int y = -cursor->size; y <= cursor->size; ++y)
        for (int x = -cursor->size; x <= cursor->size; ++x)
            draw_if_circle((sfVector2i){x, y}, cursor, board, pos);
}

static void draw_square_in_board(sfImage *board, sfVector2i pos,
    action_t *cursor)
{
    pos.x -= BOARD_MARG[0];
    pos.y -= BOARD_MARG[1];
    if (cursor->forme == 1)
        draw_square(pos.x, pos.y, board, cursor);
    if (cursor->forme == 0)
        draw_circle(board, (sfVector2i){pos.x, pos.y}, cursor);
}

void board_action(sfImage *board, sfRenderWindow *window, action_t *cursor,
    sprite_t *sprites)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(window);

    if (pos.x >= BOARD_MARG[0] && pos.x < BOARD_SIZE[0] &&
        pos.y >= BOARD_MARG[1] && pos.y < BOARD_SIZE[1]) {
        if (cursor->type == PAINTER || cursor->type == ERASER)
            draw_square_in_board(board, pos, cursor);
        if (cursor->type == FILLER)
            draw_inside_form(board, cursor, pos, cursor->color);
        if (cursor->type == PICKER)
            preview_color_click(board, cursor, window);
        if (cursor->type == LINE)
            draw_line_in_board(board, pos, cursor);
        if (cursor->type == SQUARE)
            draw_rect_in_board(window, sprites, cursor, board);
        if (cursor->type == CIRCLE)
            draw_circle_in_board(window, sprites, cursor, board);
    }
}
