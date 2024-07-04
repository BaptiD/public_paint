/*
** EPITECH PROJECT, 2024
** event_menu_file.c
** File description:
** managing event
*/

#include "my.h"

void display_folder_files(sfRenderWindow *window, sfText *text,
    char **folder_files)
{
    if (!folder_files)
        return;
    for (int k = 0; folder_files[k] != NULL && k < 8; k++) {
        sfText_setPosition(text, (sfVector2f){300, 450 + (k * 30)});
        sfText_setString(text, folder_files[k]);
        sfRenderWindow_drawText(window, text, NULL);
    }
    sfText_setPosition(text, (sfVector2f){725, 523});
}
