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
    sfRenderWindow_drawSprite(window, sprites[NEW_FILE].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[OPEN_FILE].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[SAVE_FILE].sprite, NULL);
    sfRenderWindow_display(window);
}

static int still_in_menu(sfVector2i pos)
{
    int resx = pos.x - MENU_POSITION[FILE].x;
    int resy = pos.y - MENU_POSITION[FILE].y;

    if (resx < MENU_SIZE[FILE].x && resx > 0)
        if (resy < MENU_SIZE[FILE].y && resy > 0)
            return 1;
    return 0;
}

static void new_file(sfRenderWindow *window, action_t *cursor,
    sprite_t *sprites, image_list_t **images)
{
    sfIntRect rect = get_rect(NEW_FILE, 2);

    cursor->menu = 0;
    sfSprite_setTextureRect(sprites[NEW_FILE].sprite, rect);
    rect = get_rect(FILE_BUTTON, 0);
    sfSprite_setTextureRect(sprites[FILE_BUTTON].sprite, rect);
    create_new_file(window, sprites, cursor, images);
    rect = get_rect(NEW_FILE, 0);
    sfSprite_setTextureRect(sprites[NEW_FILE].sprite, rect);
    return;
}

static void open_file(sfRenderWindow *window, action_t *cursor,
    sprite_t *sprites, image_list_t **images)
{
    sfIntRect rect = get_rect(OPEN_FILE, 2);

    cursor->menu = 0;
    sfSprite_setTextureRect(sprites[OPEN_FILE].sprite, rect);
    rect = get_rect(FILE_BUTTON, 0);
    sfSprite_setTextureRect(sprites[FILE_BUTTON].sprite, rect);
    open_file_from_import(window, sprites, cursor, images);
    rect = get_rect(OPEN_FILE, 0);
    sfSprite_setTextureRect(sprites[OPEN_FILE].sprite, rect);
    return;
}

static void save_file(sfRenderWindow *window, action_t *cursor,
    sprite_t *sprites, sfImage *board)
{
    sfIntRect rect = get_rect(SAVE_FILE, 2);

    cursor->menu = 0;
    sfSprite_setTextureRect(sprites[SAVE_FILE].sprite, rect);
    rect = get_rect(FILE_BUTTON, 0);
    sfSprite_setTextureRect(sprites[FILE_BUTTON].sprite, rect);
    popup_save_file(window, sprites, cursor, board);
    rect = get_rect(SAVE_FILE, 0);
    sfSprite_setTextureRect(sprites[SAVE_FILE].sprite, rect);
    return;
}

static void manage_menu_click(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, image_list_t **images)
{
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    if (still_in_menu(pos) == 0) {
        cursor->menu = 0;
        return;
    }
    if (is_in_hitbox(pos, NEW_FILE) == 1)
        return new_file(window, cursor, sprites, images);
    if (is_in_hitbox(pos, SAVE_FILE) == 1)
        return save_file(window, cursor, sprites, (*images)->image);
    if (is_in_hitbox(pos, OPEN_FILE) == 1)
        return open_file(window, cursor, sprites, images);
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
    manage_button_hover(window, cursor, sprites, NEW_FILE);
    manage_button_hover(window, cursor, sprites, OPEN_FILE);
    manage_button_hover(window, cursor, sprites, SAVE_FILE);
}

static void manage_menu_events(sfRenderWindow *window, action_t *cursor,
    sprite_t *sprites, image_list_t **images)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        manage_options_hover(window, cursor, sprites);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed)
            manage_menu_click(window, sprites, cursor, images);
    }
}

void file_menu(sfRenderWindow *window, action_t *cursor, sprite_t *sprites,
    image_list_t **images)
{
    sfIntRect rect = get_rect(FILE_BUTTON, 2);

    sfSprite_setTextureRect(sprites[FILE_BUTTON].sprite, rect);
    cursor->menu = 1;
    while (cursor->menu == 1 && sfRenderWindow_isOpen(window)) {
        manage_menu_events(window, cursor, sprites, images);
        if (cursor->menu == 1)
            display_menu(window, sprites, cursor, (*images)->image);
    }
    rect = get_rect(FILE_BUTTON, 0);
    sfSprite_setTextureRect(sprites[FILE_BUTTON].sprite, rect);
}
