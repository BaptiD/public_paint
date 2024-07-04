/*
** EPITECH PROJECT, 2023
** event_manage.c
** File description:
** managing event
*/

#include "my.h"


int is_in_size_selec(sfVector2i pos, sprite_t *sprites)
{
    sfVector2f pos_ball = sfSprite_getPosition(sprites[SIZE_BALL].sprite);
    int resx = pos.x - pos_ball.x;
    int resy = pos.y - pos_ball.y;

    if (resx < RESIZE[SIZE_BALL].x && resx > 0)
        if (resy < RESIZE[SIZE_BALL].y && resy > 0)
            return 1;
    return 0;
}

static void manage_cursor_pos(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    if (pos.x > 205)
        pos.x = 205;
    if (pos.x < 77)
        pos.x = 77;
    cursor->size = (pos.x - 87) / (128.0 / MAX_SIZE);
    if (cursor->size < 1)
        cursor->size = 1;
}

static int manage_events(sfRenderWindow *window, action_t *cursor,
    sprite_t *sprites)
{
    sfEvent event;
    int x = 77 + (cursor->size * 128.0 / MAX_SIZE);
    sfVector2f pos = (sfVector2f){x, POSITION[SIZE_BALL].y};

    sfSprite_setPosition(sprites[SIZE_BALL].sprite, pos);
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (sfMouse_isButtonPressed(sfMouseLeft) == sfFalse)
            return 0;
    }
    return 1;
}

static void display_hint(sfRenderWindow *window, sfRectangleShape *rect,
    action_t *cursor)
{
    sfVector2f pos = {0, (cursor->size * 2)};
    int y = POSITION[SIZE_BAR].y;

    sfRectangleShape_setSize(rect, (sfVector2f){cursor->size * 2,
        cursor->size * 2});
    sfRectangleShape_setOrigin(rect, pos);
    sfRectangleShape_setPosition(rect, (sfVector2f){250, y});
    sfRenderWindow_drawRectangleShape(window, rect, NULL);
}

static sfRectangleShape *hint_init(void)
{
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setOutlineThickness(rect, 1.0);
    sfRectangleShape_setOutlineColor(rect, sfBlack);
    sfRectangleShape_setFillColor(rect, sfTransparent);
    return rect;
}

void change_size(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, image_list_t **images)
{
    int run = 1;
    sfRectangleShape *rect = hint_init();

    sfSprite_setColor(sprites[SIZE_BALL].sprite, MENU_COLORS[2]);
    while (run == 1 && sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        run = manage_events(window, cursor, sprites);
        manage_cursor_pos(window, sprites, cursor);
        draw_board((*images)->image, window);
        display_ui(window, sprites, cursor);
        display_hint(window, rect, cursor);
        sfRenderWindow_display(window);
    }
    sfRectangleShape_destroy(rect);
    sfSprite_setColor(sprites[SIZE_BALL].sprite, MENU_COLORS[0]);
}
