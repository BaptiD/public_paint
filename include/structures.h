/*
** EPITECH PROJECT, 2024
** paint
** File description:
** structures.h
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>

#ifndef _STRUCTS
    #define _STRUCTS

typedef struct sprite_s {
    sfSprite *sprite;
    sfTexture *texture;
} sprite_t;

typedef struct action_s {
    char *username;
    int type;
    int forme;
    sfColor color;
    int size;
    sfRectangleShape *preview;
    int menu;
} action_t;

typedef struct bucket_s {
    int nb_recursive;
    sfVector2i pos;
    sfColor replace_color;
} bucket_t;

typedef struct image_list_s {
    sfImage *image;
    struct image_list_s *next;
} image_list_t;

#endif
