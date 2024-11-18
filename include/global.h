#ifndef GLOBAL_H
#define GLOBAL_H

typedef enum FLAGS {
    SUCCESS         =  0x00000000,
    ERR_ENOMEM      = -0x00000002,
    ERR_NOFILE      = -0x00000003,
    ERR_NODATA      = -0x00000004,
    
    ERR_DBOPEN      = -0x00000005,
    ERR_DBREAD      = -0x00000006,
    ERR_DBWRITE     = -0x00000007,

    ERR_ARRSIZE     = -0x00000008,
    ERR_IOERROR     = -0x00000009,
    ERR_BUFSIZE     = -0x0000000A,
    ERR_DUPLICATE   = -0x0000000B,
    ERR_NULPARAM    = -0x0000000C,
    ERR_NOTFOUND    = -0x0000000D,

    ERR_INVKEY      = -0x0000000F,
    ERR_INVCHAR     = -0x00000010,
    ERR_INVCREDS    = -0x00000011,
    ERR_PARSER_FAILED= -0x0000000E,
} flags_t;


typedef enum options {
    CREATE   = 0x00000001,
    MODIFY   = 0x00000002,
    DISPLAY  = 0x00000003,
    BROWSE   = 0x00000004,
    REMOVE   = 0x00000005,
    EXIT     = 0x00000006,
} opt_t;

typedef enum CONSTANTS {
    ID_SIZE         =  0x0000000A,
    NAME_SIZE       =  0x00000020,
    PASS_SIZE       =  0x00000020,
    ADDR_SIZE       =  0x00000040,
    BUFF_SIZE       =  0x00000020,
    MINN_BUFF       =  0x00000080,
    MAXX_BUFF       =  0x00000100,
    LINE_SIZE       =  0x00000200,
    YES             =  0x00000059,
    NO              =  0x0000004E,
    MAX_CONTACT     =  0x000003E8
} const_t;


#define DELIM " | "
#define READMODE   "r"
#define WRITEMODE  "w"
#define APPENDMODE "w+"
#define CTRL_C_KEY ('C' & 0x1F)
#define DBFILEPATH "data/database.dat"

#endif // !GLOBAL_H
