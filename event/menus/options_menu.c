/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include "my.h"

static void display_menu(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, sfImage *board)
{
    sfRenderWindow_clear(window, sfBlack);
    draw_board(board, window);
    display_ui(window, sprites, cursor);
    sfRenderWindow_drawSprite(window, sprites[LOGIN].sprite, NULL);
    sfRenderWindow_display(window);
}

static int still_in_menu(sfVector2i pos)
{
    int resx = pos.x - MENU_POSITION[OPTIONS].x;
    int resy = pos.y - MENU_POSITION[OPTIONS].y;

    if (resx < MENU_SIZE[OPTIONS].x && resx > 0)
        if (resy < MENU_SIZE[OPTIONS].y && resy > 0)
            return 1;
    return 0;
}

static void new_login(sfRenderWindow *window, action_t *cursor,
    sprite_t *sprites, sfImage *board)
{
    sfIntRect rect = get_rect(LOGIN, 2);
    char *new_username = NULL;

    cursor->menu = 0;
    sfSprite_setTextureRect(sprites[LOGIN].sprite, rect);
    rect = get_rect(OPT_BUTTON, 0);
    sfSprite_setTextureRect(sprites[OPT_BUTTON].sprite, rect);
    new_username = login_input(window, sprites, cursor, board);
    if (new_username != NULL)
        cursor->username = new_username;
    rect = get_rect(LOGIN, 0);
    sfSprite_setTextureRect(sprites[LOGIN].sprite, rect);
}

static void manage_menu_click(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, sfImage *board)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    if (still_in_menu(pos) == 0)
        cursor->menu = 0;
    else if (is_in_hitbox(pos, LOGIN) == 1)
        new_login(window, cursor, sprites, board);
}

static void manage_button_hover(sfRenderWindow *window, action_t *cursor,
    sprite_t *sprites, int k)
{
    sfIntRect rect;
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    if (is_in_hitbox(pos, k) == 1) {
        rect = get_rect(k, 1);
        sfSprite_setTextureRect(sprites[k].sprite, rect);
    } else {
        rect = get_rect(k, 0);
        sfSprite_setTextureRect(sprites[k].sprite, rect);
    }
}

static void manage_options_hover(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor)
{
    manage_button_hover(window, cursor, sprites, LOGIN);
}

static void manage_menu_events(sfRenderWindow *window, action_t *cursor,
    sprite_t *sprites, sfImage *board)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        manage_options_hover(window, sprites, cursor);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed)
            manage_menu_click(window, sprites, cursor, board);
    }
}

void options_menu(sfRenderWindow *window, action_t *cursor, sprite_t *sprites,
    sfImage *board)
{
    sfIntRect rect = get_rect(OPT_BUTTON, 2);

    sfSprite_setTextureRect(sprites[OPT_BUTTON].sprite, rect);
    cursor->menu = 2;
    while (cursor->menu == 2 && sfRenderWindow_isOpen(window)) {
        manage_menu_events(window, cursor, sprites, board);
        if (cursor->menu == 2)
            display_menu(window, sprites, cursor, board);
    }
    rect = get_rect(OPT_BUTTON, 0);
    sfSprite_setTextureRect(sprites[OPT_BUTTON].sprite, rect);
}
