/*
** EPITECH PROJECT, 2023
** draw_circle.c
** File description:
** draw circle function
*/

#include "my.h"

static void display_all(sfRenderWindow *window, sprite_t *sprites,
    sfImage *board, action_t *cursor)
{
    sfRenderWindow_clear(window, sfBlack);
    draw_board(board, window);
    display_ui(window, sprites, cursor);
}

static char *manage_popup_events(sfRenderWindow *window, sprite_t *sprites,
    int *run)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonReleased)
            *run = 0;
    }
}

static void display_hint(sfRenderWindow *window, sfCircleShape *circle,
    action_t *cursor, sfVector2i pos1)
{
    sfVector2i pos2 = sfMouse_getPosition((sfWindow *)window);

    sfCircleShape_setRadius(circle, pos2.x - pos1.x);
    sfCircleShape_setOrigin(circle,
        (sfVector2f){pos2.x - pos1.x, pos2.x - pos1.x});
    sfRenderWindow_drawCircleShape(window, circle, NULL);
}

static sfCircleShape *hint_init(sfVector2i pos1, action_t *cursor)
{
    sfCircleShape *circle = sfCircleShape_create();
    sfVector2f pos_start = (sfVector2f){pos1.x, pos1.y};

    sfCircleShape_setRadius(circle, (float)cursor->size);
    sfCircleShape_setFillColor(circle, cursor->color);
    sfCircleShape_setPosition(circle, pos_start);
    return circle;
}

void draw_circle_on_board(int x, int y, sfImage *board, action_t *cursor)
{
    if (x >= 0 && x < BOARD_SIZE[0] && y >= 0 && y < BOARD_SIZE[1]) {
        sfImage_setPixel(board, x, y, cursor->color);
    }
}

static void draw_if_circle(sfVector2i pos, action_t *cursor,
    sfImage *board, sfVector2i orgn)
{
    if (pos.x * pos.x + pos.y * pos.y <= cursor->size * cursor->size)
        if (orgn.x + pos.x >= 0 &&
            orgn.x + pos.x < BOARD_SIZE[0] &&
            orgn.y + pos.y >= 0 &&
            orgn.y + pos.y < BOARD_SIZE[1])
            draw_circle_on_board(orgn.x + pos.x,
                orgn.y + pos.y, board, cursor);
}

static void draw_circle(sfImage *board, sfVector2i pos, action_t *cursor)
{
    for (int y = -cursor->size; y <= cursor->size; ++y)
        for (int x = -cursor->size; x <= cursor->size; ++x)
            draw_if_circle((sfVector2i){x, y}, cursor, board, pos);
}

int draw_circle_in_board(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, sfImage *board)
{
    int run = 1;
    sfVector2i pos1 = sfMouse_getPosition((sfWindow *)window);
    sfCircleShape *circle = hint_init(pos1, cursor);
    sfVector2i pos2;

    while (run == 1 && sfRenderWindow_isOpen(window)) {
        manage_popup_events(window, sprites, &run);
        display_all(window, sprites, board, cursor);
        display_hint(window, circle, cursor, pos1);
        sfRenderWindow_display(window);
    }
    sfCircleShape_destroy(circle);
    pos2 = sfMouse_getPosition((sfWindow *)window);
    cursor->size = (int)(pos1.x - pos2.x);
    if (cursor->size < 0)
        cursor->size = cursor->size * -1;
    pos1 = (sfVector2i){pos1.x - BOARD_MARG[0], pos1.y - BOARD_MARG[1]};
    draw_circle(board, pos1, cursor);
    return run;
}
