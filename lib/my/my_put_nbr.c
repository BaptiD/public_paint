/*
** EPITECH PROJECT, 2023
** my_put_nbr
** File description:
** display number given
*/
#include "my.h"

static int longueur(int nb)
{
    int longe = 0;

    while (nb != 0) {
        nb = nb / 10;
        longe = longe + 1;
    }
    return (longe);
}

static int puissance_dix_int(int j)
{
    int nb = 1;

    for (; j > 1; j--) {
        nb *= 10;
    }
    return (nb);
}

static void pri(int length, int nb, int memorie)
{
    int long_nb;
    int chiffre;

    while (length != 0) {
        long_nb = puissance_dix_int(length);
        chiffre = nb / long_nb;
        nb -= chiffre * long_nb;
        my_putchar(chiffre + 48);
        length -= 1;
    }
}

int my_put_nbr(int nb)
{
    int length = longueur(nb);
    int memorie = 0;

    if (nb == -2147483648) {
        memorie = 1;
        nb += 1;
    }
    if (nb < 0) {
        nb = -nb;
    } else if (nb == 0) {
        my_putchar('0');
        return 0;
    }
    pri(length, nb, memorie);
    return 0;
}
