/*
** EPITECH PROJECT, 2024
** test
** File description:
** descs
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../include/my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(function, test1, .init = redirect_all_std)
{
    my_putstr("str\n");
    cr_assert_stdout_eq_str("str\n");
}

Test(function, test2)
{
    cr_assert_eq(1, 1);
}
