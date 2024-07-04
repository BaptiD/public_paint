/*
** EPITECH PROJECT, 2023
** event_manage.c
** File description:
** managing event
*/

#include "my.h"

static void manage_size_up(sprite_t *sprites, action_t *cursor)
{
    int y = POSITION[SIZE_BALL].y;
    sfVector2f pos = (sfVector2f){77 + (cursor->size * 128.0 / MAX_SIZE), y};

    sfSprite_setPosition(sprites[SIZE_BALL].sprite, pos);
    cursor->size += 1;
}

static void manage_size_down(sprite_t *sprites, action_t *cursor)
{
    int y = POSITION[SIZE_BALL].y;
    sfVector2f pos = (sfVector2f){77 + (cursor->size * 128.0 / MAX_SIZE), y};

    sfSprite_setPosition(sprites[SIZE_BALL].sprite, pos);
    cursor->size -= 1;
}

static void manage_keyboard_click_lctrl(sfRenderWindow *window,
    sprite_t *sprites, action_t *cursor, image_list_t **images)
{
    if (sfKeyboard_isKeyPressed(sfKeyS))
        popup_save_file(window, sprites, cursor, (*images)->image);
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        go_back_image(images);
    if (sfKeyboard_isKeyPressed(sfKeyN))
        create_new_file(window, sprites, cursor, images);
    if (sfKeyboard_isKeyPressed(sfKeyO))
        open_file_from_import(window, sprites, cursor, images);
}

static void manage_keyboard_click(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, image_list_t **images)
{
    if (sfKeyboard_isKeyPressed(sfKeyT) == sfTrue)
        change_type(cursor);
    if (sfKeyboard_isKeyPressed(sfKeyF)) {
        if (cursor->forme == 0)
            cursor->forme = 1;
        else
            cursor->forme = 0;
    }
    if (sfKeyboard_isKeyPressed(sfKeyUp) == sfTrue)
        if (cursor->size < MAX_SIZE)
            manage_size_up(sprites, cursor);
    if (sfKeyboard_isKeyPressed(sfKeyDown) == sfTrue)
        if (cursor->size > 1)
            manage_size_down(sprites, cursor);
    if (sfKeyboard_isKeyPressed(sfKeyLControl))
        manage_keyboard_click_lctrl(window, sprites, cursor, images);
}

static void manage_mode_select(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, int k)
{
    int old = cursor->type + PTR_BUTTON;
    int new = k + PTR_BUTTON;

    if (cursor->type != k) {
        cursor->type = k;
    } else
        cursor->type = 0;
}

static void manage_shape_change(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, image_list_t **images)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(window);
    sfIntRect rect;

    if (is_in_size_selec(pos, sprites) == 1)
        return change_size(window, sprites, cursor, images);
    if (is_in_hitbox(pos, SQR_SHAPE) == 1) {
        rect = get_rect(SQR_SHAPE, 2);
        sfSprite_setTextureRect(sprites[SQR_SHAPE].sprite, rect);
        rect = get_rect(CRC_SHAPE, 0);
        sfSprite_setTextureRect(sprites[CRC_SHAPE].sprite, rect);
        cursor->forme = 1;
    }
    if (is_in_hitbox(pos, CRC_SHAPE) == 1) {
        rect = get_rect(CRC_SHAPE, 2);
        sfSprite_setTextureRect(sprites[CRC_SHAPE].sprite, rect);
        rect = get_rect(SQR_SHAPE, 0);
        sfSprite_setTextureRect(sprites[SQR_SHAPE].sprite, rect);
        cursor->forme = 0;
    }
}

static void manage_mouse_click(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, image_list_t **images)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(window);

    if (cursor->type == ERASER || cursor->type == PAINTER)
        manage_shape_change(window, sprites, cursor, images);
    if (is_in_board(pos.x - BOARD_MARG[0], pos.y - BOARD_MARG[1]))
        return add_image_list(images, (*images)->image);
    if (is_in_hitbox(pos, FILE_BUTTON) == 1)
        return file_menu(window, cursor, sprites, images);
    if (is_in_hitbox(pos, OPT_BUTTON) == 1)
        return options_menu(window, cursor, sprites, (*images)->image);
    if (is_in_hitbox(pos, WIN_BUTTON) == 1)
        return window_menu(window, cursor, sprites, (*images)->image);
    if (is_in_hitbox(pos, HELP_BUTTON) == 1)
        return help_menu(window, cursor, sprites, (*images)->image);
    for (int k = 0; k <= TYPE_MAX; k++)
        if (is_in_hitbox(pos, k + PTR_BUTTON) == 1)
            return manage_mode_select(window, sprites, cursor, k);
}

void event_listener(sfRenderWindow *window, image_list_t **images,
    action_t *cursor, sprite_t *sprites)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        manage_hover(window, sprites, cursor);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed)
            manage_mouse_click(window, sprites, cursor, images);
        if (event.type == sfEvtKeyPressed)
            manage_keyboard_click(window, sprites, cursor, images);
        if (sfMouse_isButtonPressed(sfMouseLeft))
            board_action((*images)->image, window, cursor, sprites);
    }
}
