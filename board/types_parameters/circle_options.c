/*
** EPITECH PROJECT, 2024
** circle_options.c
** File description:
** every circle functions
*/

#include "my.h"

static void display_actual_color(sfRenderWindow *window, action_t *cursor)
{
    sfRectangleShape *actual_color = sfRectangleShape_create();

    sfRectangleShape_setFillColor(actual_color, cursor->color);
    sfRectangleShape_setSize(actual_color, (sfVector2f){180, 20});
    sfRectangleShape_setPosition(actual_color, (sfVector2f){30, 300});
    sfRectangleShape_setOutlineThickness(actual_color, 1);
    sfRectangleShape_setOutlineColor(actual_color, sfBlack);
    sfRenderWindow_drawRectangleShape(window, actual_color, NULL);
    sfRectangleShape_destroy(actual_color);
}

static sfBool is_in_palet(sfVector2i pos)
{
    if (pos.x > POSITION[PALET_COLOR].x &&
        pos.x < POSITION[PALET_COLOR].x + IMG_SIZE[PALET_COLOR][0] &&
        pos.y > POSITION[PALET_COLOR].y &&
        pos.y < POSITION[PALET_COLOR].y + IMG_SIZE[PALET_COLOR][1])
        return sfTrue;
    return sfFalse;
}

static void get_pixel_from_palet(sfImage *palet, sfRenderWindow *window,
    action_t *cursor)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(window);

    if (sfMouse_isButtonPressed(sfMouseLeft) && is_in_palet(pos)) {
        cursor->color = sfImage_getPixel(palet,
            pos.x - (int)POSITION[PALET_COLOR].x,
            pos.y - (int)POSITION[PALET_COLOR].y);
    }
}

static void display_palet(sfRenderWindow *window, action_t *cursor)
{
    sfImage *palet = sfImage_createFromFile(IMG_PATH[PALET_COLOR]);
    sfTexture *texture = sfTexture_createFromImage(palet, NULL);
    sfSprite *sprite = sfSprite_create();

    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setPosition(sprite, (sfVector2f){3, 350});
    sfRenderWindow_drawSprite(window, sprite, NULL);
    get_pixel_from_palet(palet, window, cursor);
    sfImage_destroy(palet);
    sfTexture_destroy(texture);
    sfSprite_destroy(sprite);
}

void display_circle_opt(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor)
{
    display_actual_color(window, cursor);
    display_palet(window, cursor);
}
