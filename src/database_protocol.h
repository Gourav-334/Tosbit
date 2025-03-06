/*
 * Database Protocol Header
 * Defines common structures and constants used by both client and server
 */

#ifndef DATABASE_PROTOCOL_H
#define DATABASE_PROTOCOL_H

/* Command types */
#define CMD_MAKE_DB      1
#define CMD_MAKE_TABLE   2
#define CMD_OPEN_DB      3
#define CMD_SHOW_STRUCT  4
#define CMD_SHOW_ALL_DB  5
#define CMD_SHOW_TABLES  6

/* Response types */
#define RESP_SUCCESS     0
#define RESP_ERROR       1

/* Maximum lengths */
#define MAX_DB_NAME      64
#define MAX_TABLE_NAME   64
#define MAX_COLUMN_NAME  32
#define MAX_TYPE_NAME    16
#define MAX_COLUMNS      16

/* Data types */
#define TYPE_INT         1
#define TYPE_VARCHAR     2
#define TYPE_TEXT        3
#define TYPE_BOOLEAN     4
#define TYPE_FLOAT       5

/* Protocol structures */
struct command_header {
    unsigned char type;      /* Command type */
    unsigned short length;   /* Length of following data */
};

struct response_header {
    unsigned char type;      /* Response type */
    unsigned short length;   /* Length of following data */
};

struct column_def {
    char name[MAX_COLUMN_NAME];
    unsigned char type;
    unsigned short length;   /* For VARCHAR */
};

struct table_def {
    char name[MAX_TABLE_NAME];
    unsigned char num_columns;
    struct column_def columns[MAX_COLUMNS];
};

#endif /* DATABASE_PROTOCOL_H */
