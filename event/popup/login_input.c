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
    sfRenderWindow_drawSprite(window, sprites[LOGIN_POPUP].sprite, NULL);
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

static int still_in_popup(sfVector2i pos)
{
    int resx = pos.x - POSITION[LOGIN_POPUP].x;
    int resy = pos.y - POSITION[LOGIN_POPUP].y;

    if (resx < RESIZE[LOGIN_POPUP].x && resx > 0)
        if (resy < RESIZE[LOGIN_POPUP].y && resy > 0)
            return 1;
    return 0;
}

static int find_click(sfVector2i pos, int *run, sprite_t *sprites,
    char *username)
{
    sfIntRect rect;

    if (still_in_popup(pos) == 0)
        return -1;
    if (is_in_hitbox(pos, CROSS) == 1)
        return -1;
    if (is_in_hitbox(pos, CONFIRM) == 1 && username[0] != 0) {
        rect = get_rect(CONFIRM, 2);
        sfSprite_setTextureRect(sprites[CONFIRM].sprite, rect);
        return 0;
    }
    return *run;
}

static void manage_popup_click(sfRenderWindow *window, sprite_t *sprites,
    int *run, char *username)
{
    sfIntRect rect;
    sfVector2i pos = sfMouse_getPosition((sfWindow *)window);

    *run = find_click(pos, run, sprites, username);
}

static char *manage_keyboard_click(char *username, int *run)
{
    int len = my_strlen(username);

    if (sfKeyboard_isKeyPressed(sfKeyReturn) && len > 0)
        *run = 0;
    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        *run = -1;
    if (len < 24)
        username = add_chars(username);
    if (len > 0)
        if (sfKeyboard_isKeyPressed(sfKeyBackspace) == sfTrue)
            username = my_str_delchar(username, 1);
    return username;
}

static char *manage_popup_events(sfRenderWindow *window, sprite_t *sprites,
    int *run, char *username)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(window, &event)) {
        manage_button_hover(window, sprites, CONFIRM);
        manage_button_hover(window, sprites, CROSS);
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtMouseButtonPressed)
            manage_popup_click(window, sprites, run, username);
        if (event.type == sfEvtKeyPressed)
            username = manage_keyboard_click(username, run);
    }
    return username;
}

static char *manage_exit(char *username, int status, sfFont *font,
    sfText *text)
{
    sfText_destroy(text);
    sfFont_destroy(font);
    if (status == 0)
        return username;
    free(username);
    return NULL;
}

sfText *init_new_usr(action_t *cursor, sfFont *font)
{
    sfText *text;
    char *sentence = "Current username: ";

    if (cursor->username == NULL)
        return NULL;
    text = init_text(font);
    sfText_setPosition(text, (sfVector2f){715, 460});
    sentence = my_strcat_auto(sentence, cursor->username, 0);
    sfText_setString(text, sentence);
    return text;
}

char *login_input(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, sfImage *board)
{
    sfFont *font = sfFont_createFromFile("assets/fonts/font.otf");
    sfText *text = init_text(font);
    sfText *current_username = init_new_usr(cursor, font);
    char *username = malloc(sizeof(char));
    int run = 1;

    username[0] = 0;
    sfRenderWindow_setMouseCursorVisible(window, sfTrue);
    while (run == 1 && sfRenderWindow_isOpen(window)) {
        username = manage_popup_events(window, sprites, &run, username);
        display_popup(window, sprites, board, cursor);
        sfText_setString(text, username);
        sfRenderWindow_drawText(window, text, NULL);
        if (current_username != NULL)
            sfRenderWindow_drawText(window, current_username, NULL);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    return manage_exit(username, run, font, text);
}
