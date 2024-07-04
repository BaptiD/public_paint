/*
** EPITECH PROJECT, 2023
** get_every_file_images.c
** File description:
** functions to get every images
*/

#include "my.h"
#include <dirent.h>
#include <unistd.h>

static int get_nb_files(char const *filepath)
{
    DIR *stream = opendir(filepath);
    int i = 0;

    while (readdir(stream) != NULL) {
        i += 1;
    }
    return i;
}

static char *get_str(char *name)
{
    int len = 0;
    char *file = NULL;

    len = my_strlen(name);
    file = malloc(sizeof(char) * (len + 1));
    for (int i = 0; name[i] != '\0'; ++i)
        file[i] = name[i];
    file[len] = '\0';
    return file;
}

static int is_same_str_index(char *name, char *format, int len)
{
    for (int i = 0; name[i + len] != '\0'; ++i)
        if (name[i + len] != format[i])
            return 1;
    return 0;
}

static int is_format(char *name)
{
    int len = my_strlen(name) - 1;

    if (len <= 3)
        return 1;
    if (is_same_str_index(name, ".png", len - 3) == 0)
        return 0;
    if (is_same_str_index(name, ".jpg", len - 3) == 0)
        return 0;
    if (is_same_str_index(name, ".bmp", len - 3) == 0)
        return 0;
    return 1;
}

void free_arr(char **arr)
{
    int i = 0;

    if (!arr)
        return;
    while (arr[i] != NULL) {
        free(arr[i]);
        i += 1;
    }
    free(arr);
}

static char **get_only_images(char **files, int nb_files)
{
    char **images = NULL;
    int index[nb_files];
    int nb_images = 0;

    for (int i = nb_files; i >= 0; --i) {
        if (is_format(files[i]) == 0) {
            index[nb_images] = i;
            nb_images += 1;
        }
    }
    if (nb_images <= 0)
        return NULL;
    index[nb_images] = -1;
    images = malloc(sizeof(char *) * (nb_images + 1));
    for (int i = 0; index[i] != -1; ++i)
        images[i] = get_str(files[index[i]]);
    images[nb_images] = NULL;
    free_arr(files);
    return images;
}

char **get_images_files_name(char const *filepath)
{
    int nb_files = get_nb_files(filepath);
    DIR *stream = opendir(filepath);
    char **files = malloc(sizeof(char *) * (nb_files + 1));
    struct dirent *dir = NULL;
    int i = 0;
    char **images = NULL;

    if (stream == NULL)
        return NULL;
    dir = readdir(stream);
    while (dir != NULL) {
        files[i] = get_str(dir->d_name);
        i += 1;
        dir = readdir(stream);
    }
    files[i] = NULL;
    images = get_only_images(files, nb_files - 1);
    closedir(stream);
    return images;
}
