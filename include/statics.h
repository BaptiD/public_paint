/*
** EPITECH PROJECT, 2024
** paint
** File description:
** statics.h
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>

#ifndef _STATICS_FILE
    #define _STATICS_FILE

//FPS
static const int FPS = 80;

//Window size when default
static const double WIN_SIZE[] = {1920, 1080};

//Board size when default
static const double BOARD_MARG[] = {240, 35};
static const double BOARD_SIZE[] = {1920, 1080};

static const int MAX_SIZE = 250;

static const int TYPE_MAX = 7;

//ENUMS
// sprites
enum sprites {
    BACKGROUND = 0,
    FILE_BUTTON = 1,
    OPT_BUTTON = 2,
    WIN_BUTTON = 3,
    NEW_FILE = 4,
    OPEN_FILE = 5,
    SAVE_FILE = 6,
    LOGIN = 7,
    SIZE_BAR = 8,
    SIZE_BALL = 9,
    BUCKET = 10,
    CLOSE = 11,
    SIZE_WIN = 12,
    SAVE_POPUP = 13,
    SELECTOR = 14,
    CROSS = 15,
    CONFIRM = 16,
    INPUT_POPUP = 17,
    WARN_EXT = 18,
    BLK_BCK = 19,
    SIZE_SELECT = 20,
    PTR_BUTTON = 21,
    PEN_BUTTON = 22,
    ERS_BUTTON = 23,
    FIL_BUTTON = 24,
    PCK_BUTTON = 25,
    LIN_BUTTON = 26,
    SQR_BUTTON = 27,
    CRC_BUTTON = 28,
    OPEN_INPUT = 29,
    HELP_BUTTON = 30,
    USR_GUIDE = 31,
    GUIDE_POPUP = 32,
    GUIDE_CROSS = 33,
    PALET_COLOR = 34,
    LOGIN_POPUP = 35,
    ERASER_PNG = 36,
    CANCEL = 37,
    CONFIRM_POPUP = 38,
    SQR_SHAPE = 39,
    CRC_SHAPE = 40
};

static const int MENUS[] = {
    FILE_BUTTON,
    OPT_BUTTON,
    WIN_BUTTON,
    HELP_BUTTON
};

enum menus {
    FILE,
    OPTIONS,
    WINDOW,
    HELP
};

static const int SHAPES[] = {
    CRC_SHAPE,
    SQR_SHAPE
};

static const int NB_MENUS = sizeof(MENUS) / sizeof(int);

static const int MODES[] = {
    PTR_BUTTON,
    PEN_BUTTON,
    ERS_BUTTON,
    FIL_BUTTON,
    PCK_BUTTON,
    LIN_BUTTON,
    SQR_BUTTON,
    CRC_BUTTON,
};

static const int NB_MODES = sizeof(MODES) / sizeof(int);

// cursor type
enum type {
    MOUSE = 0,
    PAINTER = 1,
    ERASER = 2,
    FILLER = 3,
    PICKER = 4,
    LINE = 5,
    SQUARE = 6,
    CIRCLE = 7,
};

//Images paths
static const char *IMG_PATH[] = {
    "./assets/Background.png",
    "./assets/menu/File_button.png",
    "./assets/menu/Options_button.png",
    "./assets/menu/Window_button.png",
    "./assets/menu/New_File.png",
    "./assets/menu/Open_File.png",
    "./assets/menu/Save_File.png",
    "./assets/menu/Login.png",
    "./assets/modes/White_bar.png",
    "./assets/modes/White_ball.png",
    "./assets/cursors/bucket.png",
    "./assets/menu/Close.png",
    "./assets/menu/Resize_Win.png",
    "./assets/popup/Save_popup.png",
    "./assets/popup/Selector.png",
    "./assets/popup/Cross.png",
    "./assets/popup/Confirmed.png",
    "./assets/popup/Input_save_popup.png",
    "./assets/popup/Warning_extension.png",
    "./assets/Black_bck.png",
    "./assets/modes/size_selector.png", //if any new sprite, insert here
    "./assets/modes/pointer_button.png",
    "./assets/modes/pencil_button.png",
    "./assets/modes/eraser_button.png",
    "./assets/modes/bucket_button.png",
    "./assets/modes/pipette_button.png",
    "./assets/modes/Line_button.png",
    "./assets/modes/Square_button.png",
    "./assets/modes/Circle_button.png",
    "./assets/popup/Input_open_popup.png",
    "./assets/menu/Help_button.png",
    "./assets/menu/User_guide.png",
    "./assets/popup/guide_popup.png",
    "./assets/popup/Cross.png",
    "./assets/modes/color_palet.png",
    "./assets/popup/Login_popup.png",
    "./assets/cursors/eraser.png",
    "./assets/popup/cancel.png",
    "./assets/popup/confirmation_popup.png",
    "./assets/modes/Square_button.png",
    "./assets/modes/Circle_button.png"
};

static const int SIZE_TAB = sizeof(IMG_PATH) / sizeof(char *);

//Image real size
static const int IMG_SIZE[][3] = {
    {1920, 1080},
    {56, 35},
    {93, 35},
    {91, 35},
    {300, 30},
    {300, 30}, //5
    {300, 30},
    {300, 30},
    {128, 1},
    {21, 21},
    {200, 200},
    {300, 30}, //15
    {300, 30},
    {600, 363},
    {15, 15},
    {23, 23},
    {285, 41},  //20
    {600, 363},
    {308, 27},
    {1920, 1080},
    {240, 260},
    {40, 40},
    {40, 40},
    {40, 40},
    {40, 40},
    {40, 40},
    {40, 40},
    {40, 40},
    {40, 40},
    {1000, 363},
    {60, 35},
    {300, 30},
    {933, 581},
    {23, 23},
    {234, 199},
    {600, 363},
    {34, 34},
    {285, 41},
    {600, 363},
    {40, 40},
    {40, 40}
};

//Image desired size
static const sfVector2f RESIZE[] = {
    {1920, 1080},
    {56, 35},
    {93, 35},
    {91, 35},
    {300, 30},
    {300, 30},
    {300, 30},
    {300, 30},
    {128, 1},
    {21, 21},
    {20, 20},
    {300, 30},
    {300, 30},
    {600, 363},
    {15, 15},
    {23, 23},
    {285, 41},
    {600, 363},
    {308, 27},
    {1920, 1080},
    {240, 260},
    {40, 40},
    {40, 40},
    {40, 40},
    {40, 40},
    {40, 40},
    {40, 40},
    {40, 40},
    {40, 40},
    {1000, 363},
    {60, 35},
    {300, 30},
    {933, 581},
    {23, 23},
    {234, 199},
    {600, 363},
    {20, 20},
    {285, 41},
    {600, 363},
    {40, 40},
    {40, 40}
};

//sprite position
static const sfVector2f POSITION[] = {
    {0, 0},
    {0, 0},
    {56, 0},
    {149, 0},
    {0, 35},
    {0, 65},
    {0, 95},
    {56, 35},
    {87, 937},
    {78, 927},
    {0, 0},
    {149, 35},
    {149, 65},
    {660, 358},
    {0, 0},
    {1223, 372},
    {817, 649},
    {660, 358},
    {805, 449},
    {0, 0},
    {0, 815},
    {20, 55},
    {73, 55},
    {126, 55},
    {179, 55},
    {20, 108},
    {73, 108},
    {126, 108},
    {179, 108},
    {260, 358},
    {240, 0},
    {240, 35},
    {493, 249},
    {1384, 299},
    {3, 350},
    {660, 358},
    {0, 0},
    {817, 560},
    {660, 358},
    {108, 839},
    {171, 839}
};

//menus positions
static const sfVector2f MENU_POSITION[] = {
    {0, 35},
    {56, 35},
    {149, 35},
    {240, 35}
};

//menus sizes
static const sfVector2f MENU_SIZE[] = {
    {300, 90},
    {300, 30},
    {300, 60},
    {300, 30}
};

//buttons colors
static const sfColor MENU_COLORS[] = {
    {255, 255, 255, 255}, //full color
    {255, 255, 255, 127}, //half color
    {120, 120, 120, 255} //selected cursor
};

#endif
