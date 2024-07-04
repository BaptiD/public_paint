/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include "my.h"

static void display_popup(sfRenderWindow *window, sprite_t *sprites,
    sfImage *board, action_t *cursor)
{
    sfRenderWindow_clear(window, sfBlack);
    draw_board(board, window);
    display_ui(window, sprites, cursor);
    sfRenderWindow_drawSprite(window, sprites[BLK_BCK].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[SAVE_POPUP].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[CONFIRM].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[CROSS].sprite, NULL);
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

static void manage_options_hover(sfRenderWindow *window, action_t *cursor,
    sprite_t *sprites)
{
    manage_button_hover(window, cursor, sprites, CONFIRM);
    manage_button_hover(window, cursor, sprites, CROSS);
}

static int still_in_popup(sfVector2i pos)
{
    int resx = pos.x - POSITION[SAVE_POPUP].x;
    int resy = pos.y - POSITION[SAVE_POPUP].y;

    if (resx < RESIZE[SAVE_POPUP].x && resx > 0)
        if (resy < RESIZE[SAVE_POPUP].y && resy > 0)
            return 1;
    return 0;
}

static int is_in_selector(sfVector2i pos)
{
    int rx = pos.x - 825;
    int ry = pos.y - 475;

    if (rx < 25 && rx > 0 && ry < 25 && ry > 0)
        return 1;
    if (rx < 25 && rx > 0 && (ry - 49) < 25 && (ry - 49) > 0)
        return 2;
    if (rx < 25 && rx > 0 && (ry - (49 * 2)) < 25 && (ry - (49 * 2)) > 0)
        return 3;
    return 0;
}

static int find_click(sfVector2i pos, int copy, int *run, sprite_t *sprites)
{
    sfIntRect rect;

    if (still_in_popup(pos) == 0)
        return 100;
    if (is_in_hitbox(pos, CROSS) == 1)
        return 100;
    if (is_in_hitbox(pos, CONFIRM) == 1 && copy != 0) {
        rect = get_rect(CONFIRM, 2);
        sfSprite_setTextureRect(sprites[CONFIRM].sprite, rect);
        return copy + 3;
    }
    return *run;
}

static void manage_popup_click(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, int *run)
{
    int copy = *run;
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);
    int selector = is_in_selector(pos);

    if (selector == *run && selector != 0)
        *run = 0;
    else
        *run = selector;
    *run = find_click(pos, copy, run, sprites);
}

static void manage_popup_events(sfRenderWindow *window, action_t *cursor,
    sprite_t *sprites, int *run)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        manage_options_hover(window, cursor, sprites);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed)
            manage_popup_click(window, sprites, cursor, run);
        if (event.type == sfEvtKeyPressed &&
            sfKeyboard_isKeyPressed(sfKeyEscape))
            *run = -1;
        if (event.type == sfEvtKeyPressed &&
            sfKeyboard_isKeyPressed(sfKeyReturn) &&
            *run != 0)
            *run += 3;
    }
}

void display_selected(sfRenderWindow *window, sprite_t *sprites, int run)
{
    sfVector2f pos;

    if (run != 0 && run < 4) {
        pos = (sfVector2f){830, 480 + (49 * (run - 1))};
        sfSprite_setPosition(sprites[SELECTOR].sprite, pos);
        sfRenderWindow_drawSprite(window, sprites[SELECTOR].sprite, NULL);
    }
}

void popup_save_file(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, sfImage *board)
{
    int run = 0;
    char *filename = save_input(window, sprites, cursor, board);

    if (!filename || filename[0] == 0)
        return;
    sfRenderWindow_setMouseCursorVisible(window, sfTrue);
    while (run < 4 && sfRenderWindow_isOpen(window)) {
        manage_popup_events(window, cursor, sprites, &run);
        display_popup(window, sprites, board, cursor);
        display_selected(window, sprites, run);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    save_image_as_file(cursor->username, run - 3, board, filename);
}
