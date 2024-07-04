/*
** EPITECH PROJECT, 2023
** pixels_drawing.c
** File description:
** pixel managing
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

static void display_hint(sfRenderWindow *window, sfRectangleShape *rect,
    action_t *cursor, sfVector2i pos1)
{
    sfVector2i pos2 = sfMouse_getPosition((sfWindow *)window);

    sfRectangleShape_setSize(rect, (sfVector2f){pos2.x - pos1.x,
        pos2.y - pos1.y});
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
}

static sfRectangleShape *hint_init(sfVector2i pos1, action_t *cursor)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfVector2f pos_start = (sfVector2f){pos1.x, pos1.y};

    sfRectangleShape_setFillColor(rect, cursor->color);
    sfRectangleShape_setPosition(rect, pos_start);
    return rect;
}

static void draw_rect(sfVector2i pos1, sfVector2i pos2, sfImage *board,
    action_t *cursor)
{
    int temp = 0;
    int margx = BOARD_MARG[0];
    int margy = BOARD_MARG[1];

    if (pos1.x > pos2.x) {
        temp = pos1.x;
        pos1.x = pos2.x;
        pos2.x = temp;
    }
    if (pos1.y > pos2.y) {
        temp = pos1.y;
        pos1.y = pos2.y;
        pos2.y = temp;
    }
    for (int x = pos1.x; x != pos2.x; ++x)
        for (int y = pos1.y; y != pos2.y; ++y)
            draw_only_on_board(x - margx, y - margy, board, cursor);
}

int draw_rect_in_board(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, sfImage *board)
{
    int run = 1;
    sfVector2i pos1 = sfMouse_getPosition((sfWindow *)window);
    sfRectangleShape *rect = hint_init(pos1, cursor);
    sfVector2i pos2;

    while (run == 1 && sfRenderWindow_isOpen(window)) {
        manage_popup_events(window, sprites, &run);
        display_all(window, sprites, board, cursor);
        display_hint(window, rect, cursor, pos1);
        sfRenderWindow_display(window);
    }
    sfRectangleShape_destroy(rect);
    pos2 = sfMouse_getPosition((sfWindow *)window);
    draw_rect(pos1, pos2, board, cursor);
    return run;
}
