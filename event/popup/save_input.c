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
    sfRenderWindow_drawSprite(window, sprites[INPUT_POPUP].sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[CONFIRM].sprite, NULL);
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

static void manage_options_hover(sfRenderWindow *window, sprite_t *sprites)
{
    manage_button_hover(window, sprites, CONFIRM);
    manage_button_hover(window, sprites, CROSS);
}

static int still_in_popup(sfVector2i pos)
{
    int resx = pos.x - POSITION[INPUT_POPUP].x;
    int resy = pos.y - POSITION[INPUT_POPUP].y;

    if (resx < RESIZE[INPUT_POPUP].x && resx > 0)
        if (resy < RESIZE[INPUT_POPUP].y && resy > 0)
            return 1;
    return 0;
}

static int find_click(sfVector2i pos, int *run, sprite_t *sprites,
    char *filename)
{
    sfIntRect rect;

    if (still_in_popup(pos) == 0)
        return -1;
    if (is_in_hitbox(pos, CROSS) == 1)
        return -1;
    if (is_in_hitbox(pos, CONFIRM) == 1 && filename[0] != 0) {
        rect = get_rect(CONFIRM, 2);
        sfSprite_setTextureRect(sprites[CONFIRM].sprite, rect);
        return 0;
    }
    return *run;
}

static void manage_popup_click(sfRenderWindow *window, sprite_t *sprites,
    int *run, char *filename)
{
    sfIntRect rect;
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    *run = find_click(pos, run, sprites, filename);
}

static char *manage_keyboard_click(char *filename, int *run)
{
    int len = my_strlen(filename);

    if (sfKeyboard_isKeyPressed(sfKeyReturn) && len > 0)
        *run = 0;
    if (sfKeyboard_isKeyPressed(sfKeyEscape))
            *run = -1;
    if (len < 24)
        filename = add_chars(filename);
    if (len > 0)
        if (sfKeyboard_isKeyPressed(sfKeyBackspace) == sfTrue)
            filename = my_str_delchar(filename, 1);
    return filename;
}

static char *manage_popup_events(sfRenderWindow *window, sprite_t *sprites,
    int *run, char *filename)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        manage_options_hover(window, sprites);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed)
            manage_popup_click(window, sprites, run, filename);
        if (event.type == sfEvtKeyPressed)
            filename = manage_keyboard_click(filename, run);
    }
    return filename;
}

static char *manage_exit(char *filename, int status, sfFont *font,
    sfText *text)
{
    sfText_destroy(text);
    sfFont_destroy(font);
    if (status == 0)
        return filename;
    free(filename);
    return NULL;
}

char *save_input(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, sfImage *board)
{
    sfFont *font = sfFont_createFromFile("assets/fonts/font.otf");
    sfText *text = init_text(font);
    char *filename = malloc(sizeof(char));
    int run = 1;

    filename[0] = 0;
    sfRenderWindow_setMouseCursorVisible(window, sfTrue);
    while (run == 1 && sfRenderWindow_isOpen(window)) {
        filename = manage_popup_events(window, sprites, &run, filename);
        display_popup(window, sprites, board, cursor);
        sfText_setString(text, filename);
        sfRenderWindow_drawText(window, text, NULL);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    return manage_exit(filename, run, font, text);
}
