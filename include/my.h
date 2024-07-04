/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** includes
*/
#include <unistd.h>
#include <stdlib.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>

#include "structures.h"
#include "statics.h"

#ifndef MY_H_
    #define MY_H_

/* PROJECT FUNCTION */
int paint_launcher(void);

//////////// BOARD ////////////

/* board/setup_board.c */
sfImage *set_board_image(void);
void draw_board(sfImage *board_image, sfRenderWindow *window);

/* board/board_action.c */
void board_action(sfImage *board, sfRenderWindow *window, action_t *cursor,
    sprite_t *sprites);
void draw_only_on_board(int x, int y, sfImage *board, action_t *cursor);

/* board/bucket.c */
void draw_inside_form(sfImage *board, action_t *cursor, sfVector2i pos,
    sfColor color);
int search_for_pixels(sfColor color, sfVector2i pos, bucket_t *fill,
    sfImage *board);
sfBool is_in_board(int x, int y);

/* board/draw_rect.c */
int draw_rect_in_board(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, sfImage *board);

/* board/draw_line.c */
void draw_line_in_board(sfImage *board, sfVector2i pos, action_t *cursor);

/* board/draw_circle.c */
int draw_circle_in_board(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, sfImage *board);

/* board/preview_color.c */
void preview_color_click(sfImage *board, action_t *cursor,
    sfRenderWindow *window);
void display_preview(sfRenderWindow *window, action_t *cursor);

/* board/types_parameters/earaser_options.c */
void display_eraser_opt(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor);

/* board/types_parameters/pencil_options.c */
void display_pencil_opt(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor);

/* board/types_parameters/bucket_options.c */
void display_bucket_opt(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor);

/* board/types_parameters/picker_options.c */
void display_picker_opt(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor);

/* board/types_parameters/circle_options.c */
void display_circle_opt(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor);

///////////////////////////////


//////////// EVENT ////////////

/* event/manage.c */
void event_listener(sfRenderWindow *window, image_list_t **images,
    action_t *cursor, sprite_t *sprites);
void change_size(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, image_list_t **images);
int is_in_size_selec(sfVector2i pos, sprite_t *sprites);

/* event/shortcut/manage_events.c */
void shortcut_event(action_t *cursor);

/* event/shortcut/change_type.c */
void change_type(action_t *cursor);

/* event/buttons/manage_buttons.c */
void manage_hover(sfRenderWindow *window, sprite_t *sprites, action_t *cursor);
void manage_hitbox(sfRenderWindow *window, sprite_t *sprites, action_t *curso);
int is_in_hitbox(sfVector2i pos, int index);
void popup_save_file(sfRenderWindow *, sprite_t *, action_t *, sfImage *);
char *save_input(sfRenderWindow *, sprite_t *, action_t *, sfImage *);
char *open_input(sfRenderWindow *, sprite_t *, action_t *, sfImage *);
char *login_input(sfRenderWindow *, sprite_t *, action_t *, sfImage *);
void guide_popup(sfRenderWindow *, sprite_t *, action_t *, sfImage *);
int confirmation(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, sfImage *board);
/* event/save_file.c */
sfBool save_image_as_file(char *usrname, int format, sfImage *board,
    char *filename);

/* event/import_file.c */
void open_file_from_import(sfRenderWindow *, sprite_t *, action_t *,
    image_list_t **);

/* event/new_file.c */
void create_new_file(sfRenderWindow *window, sprite_t *sprites,
    action_t *cursor, image_list_t **images);

/* event/menus */
void file_menu(sfRenderWindow *, action_t *, sprite_t *, image_list_t **);
void options_menu(sfRenderWindow *, action_t *, sprite_t *, sfImage *);
void window_menu(sfRenderWindow *, action_t *, sprite_t *, sfImage *);
void help_menu(sfRenderWindow *, action_t *, sprite_t *, sfImage *);
sfText *init_text(sfFont *font);
char *add_chars(char *filename);

////////////////////////////////


//////////// SPRITE ////////////

/* sprite/display.c */
void display_ui(sfRenderWindow *window, sprite_t *sprites, action_t *cursor);

/* sprites/init.c */
sprite_t *init_spritesarray(void);

/* sprites/destroy.c */
void destroy_sprites(sprite_t *sprites);

//////////////////////////////


//////////// OTHER ////////////

/* list_manage/image_list.c */
void add_image_list(image_list_t **list, sfImage *image);
void clear_image_list(image_list_t **list);
void go_back_image(image_list_t **images);
/* utils.c */
sfIntRect get_rect(int index, int offset);

/* cursor.c */
action_t *set_cursor(void);
void display_custom_cursor(action_t *cursor, sfRenderWindow *window,
    sprite_t *sprites);

/* get_every_file_images */
char **get_images_files_name(char const *filepath);
void free_arr(char **arr);
void display_folder_files(sfRenderWindow *window, sfText *text,
    char **folder_files);
//////////////////////////////

/*  LIB FUNCTIONS   */
void my_putchar(char c);
void my_putstr(char const *str);
int my_getnbr(char const *str);
int my_put_nbr(int nb);
int my_strlen(char const *str);
int nb_args_array(char **av);
char **my_str_to_word_arr(char const *str, char c);
void my_putstr_arr(char **array);
int my_strcmp(char *str1, char *str2);
char *my_strcat_auto(char *dest, char *str, int opt);
char *my_strcpy(char *dest, char *src);
char *my_str_addchar(char *str, char c, int opt);
char *my_str_delchar(char *str, int opt);

#endif
