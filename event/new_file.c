/*
** EPITECH PROJECT, 2023
** new_file.c
** File description:
** create new file
*/

#include "my.h"

void create_new_file(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, image_list_t **images)
{
    if (confirmation(window, sprites, cursor, (*images)->image) == 1) {
        clear_image_list(images);
        (*images) = NULL;
        add_image_list(images, set_board_image());
        add_image_list(images, set_board_image());
    }
}
