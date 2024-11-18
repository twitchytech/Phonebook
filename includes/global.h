#ifndef GLOBAL_H
#define GLOBAL_H
#pragma once

#define READMODE      "r"
#define WRITEMODE     "w"
#define APPENDMODE    "a"
#define READWRITEMODE "a+"


typedef enum FLAGS {
    VALUE_ERROR     = -0x00000001,
    INVALID_CHAR    = -0x00000002,
    INVALID_WORD    = -0x00000003,
} flags_t;

typedef enum options {
    CREATE   = 0x00000000,
    MODIFY   = 0x00000001,
    DISPLAY  = 0x00000002,
    BROWSE   = 0x00000003,
    DELETE   = 0x00000004,
    EXIT     = 0x00000005,
    QUIT     = 0x00000003,
} opt_t;

typedef enum CONSTANTS {
    ID_SIZE         =  0x00000008,
    NAME_SIZE       =  0x00000020,
    PASS_SIZE       =  0x00000020,
    BUFF_SIZE       =  0x00000020,
    MAXX_BUFF       =  0x00000080,
    LINE_SIZE       =  0x00001000,

    Y               =  0x00000059,
    N               =  0x0000004E,
} const_t;

typedef enum CONTROL_KEYS {
    KEY_UP          = 0x00000041,  //? 'A'
    KEY_DOWN        = 0x00000042,  //? 'B'
    KEY_LEFT        = 0x00000044,  //? 'D'
    KEY_RIGHT       = 0x00000043,  //? 'C'
    KEY_ESC         = 0x0000001b,  //? Escape Key
    LEFT_SQB        = 0x0000005b,  //? Left Square Bracket '['

    ENTER_KEY       = 0x0000000A,
    DELIMITER       = 0x0000003B,
    BACKSPACE_KEY   = 0x0000007F,
} ctrl_t;

typedef enum TEXT_STYLES {
    RAW        = -0x00000001,
    DIM        =  0x00000002,
    BOLD       =  0x00000001,
    HIDDEN     =  0x00000008,
    INVERT     =  0x00000007,
    ITALIC     =  0x00000003,
    UNDERLINE  =  0x00000004,
    RESET_ATTR =  0x00000000,
} styles_t;

#endif //GLOBAL_H
