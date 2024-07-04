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
    sfRenderWindow_drawSprite(window, sprites[CONFIRM_POPUP].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[CONFIRM].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[CANCEL].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[CROSS].sprite, NULL);
}

static void manage_button_hover(sfRenderWindow *window, sprite_t *sprites,
    int k)
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

static int still_in_popup(sfVector2i pos)
{
    int resx = pos.x - POSITION[CONFIRM_POPUP].x;
    int resy = pos.y - POSITION[CONFIRM_POPUP].y;

    if (resx < RESIZE[CONFIRM_POPUP].x && resx > 0)
        if (resy < RESIZE[CONFIRM_POPUP].y && resy > 0)
            return 1;
    return 0;
}

static int find_click(sfVector2i pos, int *run, sprite_t *sprites)
{
    sfIntRect rect;

    if (still_in_popup(pos) == 0)
        return -1;
    if (is_in_hitbox(pos, CROSS) == 1)
        return -1;
    if (is_in_hitbox(pos, CANCEL) == 1)
        return -1;
    if (is_in_hitbox(pos, CONFIRM) == 1) {
        rect = get_rect(CONFIRM, 2);
        sfSprite_setTextureRect(sprites[CONFIRM].sprite, rect);
        return 1;
    }
    return *run;
}

static void manage_popup_click(sfRenderWindow *window, sprite_t *sprites,
    int *run)
{
    sfIntRect rect;
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    *run = find_click(pos, run, sprites);
}

static void manage_keyboard_click(int *run)
{
    if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
        *run = -1;
    if (sfKeyboard_isKeyPressed(sfKeyReturn) == sfTrue)
        *run = 1;
}

static char *manage_popup_events(sfRenderWindow *window, sprite_t *sprites,
    int *run)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        manage_button_hover(window, sprites, CONFIRM);
        manage_button_hover(window, sprites, CROSS);
        manage_button_hover(window, sprites, CANCEL);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed)
            manage_popup_click(window, sprites, run);
        if (event.type == sfEvtKeyPressed)
            manage_keyboard_click(run);
    }
}

int confirmation(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, sfImage *board)
{
    int run = 0;

    sfRenderWindow_setMouseCursorVisible(window, sfTrue);
    while (run == 0 && sfRenderWindow_isOpen(window)) {
        manage_popup_events(window, sprites, &run);
        display_popup(window, sprites, board, cursor);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    return run;
}
