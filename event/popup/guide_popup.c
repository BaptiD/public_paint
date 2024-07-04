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
    sfRenderWindow_drawSprite(window, sprites[GUIDE_POPUP].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[GUIDE_CROSS].sprite, NULL);
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

static void manage_options_hover(sfRenderWindow *window, sprite_t *sprites)
{
    manage_button_hover(window, sprites, GUIDE_CROSS);
}

static int still_in_popup(sfVector2i pos)
{
    int resx = pos.x - POSITION[GUIDE_POPUP].x;
    int resy = pos.y - POSITION[GUIDE_POPUP].y;

    if (resx < RESIZE[GUIDE_POPUP].x && resx > 0)
        if (resy < RESIZE[GUIDE_POPUP].y && resy > 0)
            return 1;
    return 0;
}

static int find_click(sfVector2i pos, int *run, sprite_t *sprites)
{
    sfIntRect rect;

    if (still_in_popup(pos) == 0)
        return -1;
    if (is_in_hitbox(pos, GUIDE_CROSS) == 1)
        return -1;
    return *run;
}

static void manage_popup_click(sfRenderWindow *window, sprite_t *sprites,
    int *run)
{
    sfIntRect rect;
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    *run = find_click(pos, run, sprites);
}

static void manage_popup_events(sfRenderWindow *window, sprite_t *sprites,
    int *run)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        manage_options_hover(window, sprites);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed)
            manage_popup_click(window, sprites, run);
        if (event.type == sfEvtKeyPressed &&
        sfKeyboard_isKeyPressed(sfKeyEscape))
            *run = -1;
    }
}

void guide_popup(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, sfImage *board)
{
    int run = 1;

    sfRenderWindow_setMouseCursorVisible(window, sfTrue);
    while (run == 1 && sfRenderWindow_isOpen(window)) {
        manage_popup_events(window, sprites, &run);
        display_popup(window, sprites, board, cursor);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
}
