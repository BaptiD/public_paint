##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## compile my lib
##

FILES 	=	./my/my_getnbr.c	\
		./my/my_putchar.c	\
		./my/my_put_nbr.c	\
		./my/my_putstr.c	\
		./my/my_strlen.c	\
		./my/my_nb_args_array.c	\
		./my/my_str_to_word_arr.c	\
		./my/my_putstr_arr.c	\
		./my/my_strcmp.c	\
		./my/my_strcat_auto.c \
		./my/my_strcpy.c \
		./my/my_str_addchar.c	\

LIB	=	$(FILES:.c=.o)

CPPFLAGS 	=	-I ../include

NAME_LIB	=	libmy.a

all:	init

init:	$(LIB)
	ar rc $(NAME_LIB) $(LIB)

clean:
	rm -f $(LIB)

fclean:	clean
	rm -f $(NAME_LIB)

re: fclean all
