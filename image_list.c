/*
** EPITECH PROJECT, 2024
** image_list.c
** File description:
** list managment functions
*/

#include "my.h"

void go_back_image(image_list_t **images)
{
    image_list_t *node = (*images);

    if (node != NULL && node->next == NULL)
        return;
    (*images) = node->next;
    sfImage_destroy(node->image);
    free(node);
    node = (*images);
}

void add_image_list(image_list_t **list, sfImage *image)
{
    image_list_t *new = malloc(sizeof(image_list_t));
    image_list_t *list_nodes = (*list);
    sfImage *new_image = sfImage_copy(image);

    new->image = new_image;
    new->next = list_nodes;
    (*list) = new;
}

void clear_image_list(image_list_t **list)
{
    image_list_t *node = (*list);
    image_list_t *tmp = NULL;

    while (node != NULL) {
        tmp = node;
        node = node->next;
        sfImage_destroy(tmp->image);
        free(tmp);
    }
}
