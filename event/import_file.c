/*
** EPITECH PROJECT, 2023
** import_file.c
** File description:
** import files
*/

#include "my.h"
#include <sys/stat.h>

static int get_size(char *name)
{
    struct stat fs = {0};

    stat(name, &fs);
    return fs.st_size;
}

void open_file_from_import(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, image_list_t **images)
{
    sfBool result = sfFalse;
    char *file_name = open_input(window, sprites, cursor, (*images)->image);

    if (!file_name || file_name[0] == 0 || get_size(file_name) == 0 ||
        confirmation(window, sprites, cursor, (*images)->image) == -1)
        return;
    clear_image_list(images);
    (*images) = NULL;
    add_image_list(images, set_board_image());
    add_image_list(images, sfImage_createFromFile(file_name));
}
