/*
** EPITECH PROJECT, 2024
** bucket.c
** File description:
** bucket functions
*/

#include "my.h"

static sfBool is_same_color(sfColor color1, sfColor color2)
{
    if (color1.r != color2.r || color1.g != color2.g || color1.b != color2.b)
        return sfFalse;
    return sfTrue;
}

sfBool is_in_board(int x, int y)
{
    if (x >= 0 && x < BOARD_SIZE[0] && y >= 0 && y < BOARD_SIZE[1])
        return sfTrue;
    return sfFalse;
}

static void save_changes_info(bucket_t *fill, int x, int y)
{
    fill->pos.x = x;
    fill->pos.y = y;
    fill->nb_recursive += 1;
}

static int stop_case(sfColor color, sfVector2i pos, bucket_t *fill)
{
    if (is_same_color(color, fill->replace_color) == sfTrue || (pos.x <= 0 &&
        pos.x > BOARD_SIZE[0] && pos.y <= 0 && pos.y > BOARD_SIZE[1]))
        return 1;
    if (fill->nb_recursive >= 10000)
        return 0;
    return 2;
}

static int get_every_pixel(sfImage *board, bucket_t *fill, sfColor color)
{
    sfVector2i pos = fill->pos;

    if (stop_case(color, pos, fill) != 2)
        return stop_case(color, pos, fill);
    sfImage_setPixel(board, pos.x, pos.y, color);
    if (search_for_pixels(color, (sfVector2i){pos.x + 1, pos.y},
        fill, board) != 1)
        return 0;
    if (search_for_pixels(color, (sfVector2i){pos.x, pos.y + 1},
        fill, board) != 1)
        return 0;
    if (search_for_pixels(color, (sfVector2i){pos.x - 1, pos.y},
        fill, board) != 1)
        return 0;
    if (search_for_pixels(color, (sfVector2i){pos.x, pos.y - 1},
        fill, board) != 1)
        return 0;
    return 1;
}

int search_for_pixels(sfColor color, sfVector2i pos, bucket_t *fill,
    sfImage *board)
{
    if (is_in_board(pos.x, pos.y) && is_same_color(sfImage_getPixel(
        board, pos.x, pos.y), fill->replace_color)) {
        save_changes_info(fill, pos.x, pos.y);
        if (get_every_pixel(board, fill, color) == 0)
            return 0;
    }
    return 1;
}

void draw_inside_form(sfImage *board, action_t *cursor, sfVector2i pos,
    sfColor color)
{
    bucket_t *fill = malloc(sizeof(bucket_t));
    int stop = 0;

    pos.x -= BOARD_MARG[0];
    pos.y -= BOARD_MARG[1];
    fill->pos = (sfVector2i){pos.x, pos.y};
    fill->replace_color = sfImage_getPixel(board, pos.x, pos.y);
    fill->nb_recursive = 0;
    while (stop != 1) {
        stop = get_every_pixel(board, fill, color);
        fill->nb_recursive = 0;
    }
    free(fill);
}
