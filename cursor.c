/*
** EPITECH PROJECT, 2023
** cursor.c
** File description:
** cursor functions
*/

#include "my.h"

action_t *set_cursor(void)
{
    action_t *cursor = malloc(sizeof(action_t));

    cursor->type = MOUSE;
    cursor->color = (sfColor){255, 0, 0, 255};
    cursor->size = 3;
    cursor->menu = 0;
    cursor->forme = 1;
    cursor->preview = sfRectangleShape_create();
    sfRectangleShape_setSize(cursor->preview, (sfVector2f){80, 35});
    sfRectangleShape_setOutlineThickness(cursor->preview, 1);
    sfRectangleShape_setOutlineColor(cursor->preview, sfBlack);
    return cursor;
}

static int is_mouse_on_board(action_t *cursor, sfRenderWindow *window)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    if (pos.x >= BOARD_MARG[0] && pos.x < BOARD_SIZE[0] &&
        pos.y >= BOARD_MARG[1] && pos.y < BOARD_SIZE[1]) {
        return 1;
    }
    return 0;
}

static void cursor_circle(action_t *cursor, sfRenderWindow *window,
    sfVector2i pos)
{
    sfCircleShape *circle = sfCircleShape_create();

    sfCircleShape_setRadius(circle, cursor->size);
    sfCircleShape_setOrigin(circle, (sfVector2f){cursor->size, cursor->size});
    sfCircleShape_setPosition(circle, (sfVector2f){pos.x, pos.y});
    sfCircleShape_setOutlineThickness(circle, 1.0);
    sfCircleShape_setOutlineColor(circle, sfBlack);
    sfCircleShape_setFillColor(circle, sfTransparent);
    sfRenderWindow_drawCircleShape(window, circle, NULL);
}

static void cursor_rectangle(action_t *cursor, sfRenderWindow *window,
    sfVector2i pos)
{
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setSize(rect, (sfVector2f){cursor->size * 2,
        cursor->size * 2});
    sfRectangleShape_setOrigin(rect,
        (sfVector2f){(cursor->size * 2) / 2, (cursor->size * 2) / 2});
    sfRectangleShape_setPosition(rect, (sfVector2f){pos.x, pos.y});
    sfRectangleShape_setOutlineThickness(rect, 1.0);
    sfRectangleShape_setOutlineColor(rect, sfBlack);
    sfRectangleShape_setFillColor(rect, sfTransparent);
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
}

static void display_painting_cursor(action_t *cursor, sfRenderWindow *window)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    if (cursor->forme == 1) {
        cursor_rectangle(cursor, window, pos);
    } else
        cursor_circle(cursor, window, pos);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
}

static void display_eraser_cursor(action_t *cursor, sfRenderWindow *window,
    sprite_t *sprites)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    sfSprite_setPosition(sprites[ERASER_PNG].sprite,
        (sfVector2f){pos.x + cursor->size + 10, pos.y - cursor->size - 20});
    sfRenderWindow_drawSprite(window, sprites[ERASER_PNG].sprite, NULL);
    if (cursor->forme == 1) {
        cursor_rectangle(cursor, window, pos);
    } else
        cursor_circle(cursor, window, pos);
    sfRectangleShape_destroy(rect);
}

static void display_bucket_cursor(action_t *cursor, sfRenderWindow *window,
    sprite_t *sprite)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);
    sfCircleShape *circle = sfCircleShape_create();

    sfCircleShape_setRadius(circle, 2);
    sfCircleShape_setPosition(circle, (sfVector2f){pos.x, pos.y});
    sfCircleShape_setFillColor(circle, sfBlack);
    sfSprite_setPosition(sprite[BUCKET].sprite,
        (sfVector2f){pos.x + 10, pos.y - 25});
    sfRenderWindow_drawCircleShape(window, circle, NULL);
    sfRenderWindow_drawSprite(window, sprite[BUCKET].sprite, NULL);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    sfCircleShape_destroy(circle);
}

void display_custom_cursor(action_t *cursor, sfRenderWindow *window,
    sprite_t *sprite)
{
    if (is_mouse_on_board(cursor, window) == 1) {
        if (cursor->type == MOUSE)
            sfRenderWindow_setMouseCursorVisible(window, sfTrue);
        if (cursor->type == PAINTER)
            display_painting_cursor(cursor, window);
        if (cursor->type == FILLER)
            display_bucket_cursor(cursor, window, sprite);
        if (cursor->type == PICKER)
            display_preview(window, cursor);
        if (cursor->type == ERASER)
            display_eraser_cursor(cursor, window, sprite);
    } else {
        sfRenderWindow_setMouseCursorVisible(window, sfTrue);
    }
}
