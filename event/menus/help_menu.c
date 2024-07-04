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
    sfRenderWindow_drawSprite(window, sprites[USR_GUIDE].sprite, NULL);
    sfRenderWindow_display(window);
}

static int still_in_menu(sfVector2i pos)
{
    int resx = pos.x - MENU_POSITION[HELP].x;
    int resy = pos.y - MENU_POSITION[HELP].y;

    if (resx < MENU_SIZE[HELP].x && resx > 0)
        if (resy < MENU_SIZE[HELP].y && resy > 0)
            return 1;
    return 0;
}

static void display_guide(sfRenderWindow *window, action_t *cursor,
    sprite_t *sprites, sfImage *board)
{
    sfIntRect rect = get_rect(USR_GUIDE, 2);

    cursor->menu = 0;
    sfSprite_setTextureRect(sprites[USR_GUIDE].sprite, rect);
    rect = get_rect(HELP_BUTTON, 0);
    sfSprite_setTextureRect(sprites[HELP_BUTTON].sprite, rect);
    guide_popup(window, sprites, cursor, board);
    rect = get_rect(USR_GUIDE, 0);
    sfSprite_setTextureRect(sprites[USR_GUIDE].sprite, rect);
    return;
}

static void manage_menu_click(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, sfImage *board)
{
    sfIntRect rect;
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    if (still_in_menu(pos) == 0)
        cursor->menu = 0;
    else if (is_in_hitbox(pos, USR_GUIDE))
        display_guide(window, cursor, sprites, board);
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
    manage_button_hover(window, cursor, sprites, USR_GUIDE);
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

void help_menu(sfRenderWindow *window, action_t *cursor, sprite_t *sprites,
    sfImage *board)
{
    sfIntRect rect = get_rect(HELP_BUTTON, 2);

    sfSprite_setTextureRect(sprites[HELP_BUTTON].sprite, rect);
    cursor->menu = 4;
    while (cursor->menu == 4 && sfRenderWindow_isOpen(window)) {
        manage_menu_events(window, cursor, sprites, board);
        if (cursor->menu == 4)
            display_menu(window, sprites, cursor, board);
    }
    rect = get_rect(HELP_BUTTON, 0);
    sfSprite_setTextureRect(sprites[HELP_BUTTON].sprite, rect);
}
