/*
** EPITECH PROJECT, 2024
** my_paint.c
** File description:
** my hunter game
*/

#include "my.h"
#include "statics.h"

void display_loading(sfRenderWindow *window)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *t = sfTexture_createFromFile("assets/loading.png", NULL);
    int sizex = WIN_SIZE[0] / 2 - 400;
    int sizey = WIN_SIZE[1] / 2 - 100;
    sfVector2f pos = (sfVector2f){sizex, sizey};

    sfRenderWindow_clear(window, sfWhite);
    sfSprite_setTexture(sprite, t, sfTrue);
    sfSprite_setPosition(sprite, pos);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfRenderWindow_display(window);
    sfSprite_destroy(sprite);
    sfTexture_destroy(t);
}

static int paint(sfRenderWindow *window, sprite_t *sprites,
    image_list_t **images, action_t *cursor)
{
    if (!window)
        return 84;
    cursor->username = login_input(window, sprites, cursor, (*images)->image);
    while (sfRenderWindow_isOpen(window)) {
        event_listener(window, images, cursor, sprites);
        draw_board((*images)->image, window);
        display_custom_cursor(cursor, window, sprites);
        display_ui(window, sprites, cursor);
        sfRenderWindow_display(window);
        sfRenderWindow_clear(window, sfBlack);
    }
    return 0;
}

int paint_launcher(void)
{
    int status = 0;
    sfRenderWindow* window = NULL;
    sprite_t *sprites = NULL;
    image_list_t *images = NULL;
    action_t *cursor = set_cursor();

    window = sfRenderWindow_create((sfVideoMode){WIN_SIZE[0], WIN_SIZE[1], 32},
        "MY PAINT", sfResize | sfClose, NULL);
    if (!window)
        return 84;
    sfRenderWindow_setFramerateLimit(window, FPS);
    add_image_list(&images, set_board_image());
    display_loading(window);
    sprites = init_spritesarray();
    status = paint(window, sprites, &images, cursor);
    destroy_sprites(sprites);
    sfRenderWindow_destroy(window);
    clear_image_list(&images);
    return status;
}
