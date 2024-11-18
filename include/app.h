#ifndef APP_H
#define APP_H

#include <io.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <termios.h>
    #include <sys/ioctl.h>
    #include <sys/select.h>
#endif

#include "global.h"
#include <sys/types.h>

typedef struct PHONEBOOK_ENTRY {
    char name[NAME_SIZE];
    char surname[NAME_SIZE];
    char email[BUFF_SIZE];
    char phone[BUFF_SIZE];
    char address[ADDR_SIZE];
} contact_t;

typedef struct PHONEBOOK_DATABASE {
    unsigned row_id;
    contact_t column;
} pdb_t;

typedef struct ADMIN {
    char username[BUFF_SIZE];
    char password[BUFF_SIZE];
} admin_t;

ssize_t get_pass(char *);
ssize_t get_line(char *, size_t, FILE *);

int cgetch(void);
int setup_db(void);
int get_char(void);

int get_conf(const char *);
int get_contact (contact_t *);
int get_field(char *, size_t);

void instructions(void);
void log_error(const char *);
void print_banner(const char *);
const char* get_errMsg(const int);

int load_db(pdb_t []);
int overwrite_db(pdb_t [], size_t);
int parse_contact(const char *, contact_t *);
int compare_phone(const char *, const char *);
int is_duplicate(const pdb_t [], const char *, size_t);

void menu(void);
void login(void);
void add_contact(void);
void browse_contacts(void);
void display_contacts(void);
void exit_program(const int);
void print_contact(int, contact_t *);
void modify_row(pdb_t [], contact_t *, const int);


void prepare_phone(char *);
void print_all(pdb_t *, size_t);
void insert_contact(contact_t *, FILE *);
void add_new_row(pdb_t [], contact_t *, size_t);

#endif // !APP_H
