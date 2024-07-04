/*
** EPITECH PROJECT, 2023
** my_getnbr
** File description:
** return a number from a string
*/
#include "my.h"

static int is_end_nb(char const *str, int i)
{
    if (str[i + 1] < 48 || str[i + 1] > 57) {
        return 1;
    }
    return 0;
}

static int func(char const *str, int i, int is_end)
{
    if (str[i] >= 48 && str[i] <= 57) {
        if (str[i - 1] == '-') {
            return 3;
        }
        is_end = is_end_nb(str, i);
    }
    return is_end;
}

int nb_is_neg(char const *str)
{
    int i = 0;
    int is_end = 0;

    while (str[i] != '\0' && is_end != 1) {
        is_end = func(str, i, is_end);
        i += 1;
    }
    return 0;
}

int length_nb(char const *str)
{
    int i = 0;
    int number = 0;
    int is_end = 0;

    while (str[i] != '\0' && is_end != 1) {
        if (is_end == 3) {
            return 1;
        }
        if (str[i] >= 48 && str[i] <= 57) {
            number += 1;
            is_end = is_end_nb(str, i);
        }
        i += 1;
    }
    return number;
}

char *nb_in_tab(char const *str, char *number)
{
    int i = 0;
    int length = 0;
    int is_end = 0;

    while (str[i] != '\0' && is_end != 1) {
        if (str[i] >= 48 && str[i] <= 57) {
            number[length] = str[i];
            length += 1;
            is_end = is_end_nb(str, i);
        }
        i += 1;
    }
    return number;
}

int my_getnbr(char const *str)
{
    int long_nb = length_nb(str);
    char all_nb[long_nb];
    char *number = nb_in_tab(str, all_nb);
    int i = 0;
    int nb = 0;
    int chiffre;
    int is_neg = nb_is_neg(str);

    while (long_nb != 0) {
        chiffre = number[i] - 48;
        nb *= 10;
        nb += chiffre;
        long_nb -= 1;
        i += 1;
    }
    if (is_neg == 1) {
        nb = nb * - 1;
        return nb;
    }
    return nb;
}
