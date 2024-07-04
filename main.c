/*
** EPITECH PROJECT, 2024
** my_hunter.c
** File description:
** my hunter game
*/

#include "my.h"

int usage(void)
{
    my_putstr("USAAAAGE\n");
    return 0;
}

int main(int ac, char **av)
{
    if (ac > 2)
        return 84;
    if (ac == 2 && my_strcmp(av[1], "-h") == 0)
        return usage();
    return paint_launcher();
}
