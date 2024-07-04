##
## EPITECH PROJECT, 2024
## makefile
## File description:
## noice
##

## FILES SOURCES
MAIN	=	main.c								\

SRC	=	paint.c									\
		cursor.c 								\
		image_list.c 							\
		get_every_file_images.c 				\
		sprites/init.c							\
		sprites/destroy.c						\
		sprites/displays.c						\
		board/setup_board.c 					\
		board/board_action.c 					\
		board/bucket.c 							\
		board/preview_color.c 					\
		board/draw_line.c 						\
		board/draw_circle.c        				\
		board/types_parameters/eraser_options.c \
		board/types_parameters/pencil_options.c \
		board/types_parameters/bucket_options.c \
		board/types_parameters/picker_options.c \
		board/types_parameters/circle_options.c \
		event/manage_events.c 					\
		event/import_file.c 					\
		event/save_file.c 						\
		event/new_file.c 						\
		event/shortcut/change_type.c 			\
		event/buttons/manage_buttons.c			\
		event/menus/file_menu.c					\
		event/menus/help_menu.c					\
		event/menus/options_menu.c				\
		event/menus/window_menu.c				\
		event/popup/save_popup.c				\
		event/popup/save_input.c				\
		event/popup/guide_popup.c				\
		event/popup/input_popup_compl.c			\
		event/size_cursor.c						\
		utils.c									\
		event/popup/open_input.c				\
		event/popup/login_input.c				\
		event/popup/confirm_popup.c				\
		board/draw_rect.c						\
		event/popup/display_folder_files.c		\

## NORMAL COMPILATION OBJECTS
OBJ	=	$(SRC:.c=.o) $(MAIN:.c=.o)
NAME	=	my_paint

## COMMON FLAGS
CPPFLAGS =	-I include
LDLIBS	=	-Llib -lmy -lcsfml-graphics -lcsfml-window -lcsfml-system -lm

## UNIT-TESTS
TESTS   =       -lcriterion --coverage
TEST_NAME =     unit_tests
I 	=	$(CPPFLAGS)
TESTS_FILES =   tests/test.c

## NORMAL MAIN COMPILATION
all: $(NAME)

$(NAME):	$(OBJ)
		$(MAKE) -C lib -j
		$(CC) -o $(NAME) $(OBJ) $(LDLIBS)

re:     fclean all

## DEBUG FLAG FOR VALGRIND
debug: CPPFLAGS += -g3
debug: re

## UNIT-TESTS COMPILATION
tests_run: CPPFLAGS += --coverage
tests_run: fclean
	$(MAKE) -C lib -j
	$(CC) -o $(TEST_NAME) $(TESTS_FILES) $(SRC) $(LDLIBS) $(TESTS) $(I)
	./$(TEST_NAME)

## CLEANING RULES
clean:
	$(MAKE) clean -C lib
	$(RM) -f *.gcno *.gcda
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) fclean -C lib
	$(RM) $(TEST_NAME)
	$(RM) $(NAME)
