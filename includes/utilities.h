#ifndef UTILITIES_H
#define UTILITIES_H
#pragma once

#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <strings.h>
#include <stdbool.h>
#include <termios.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/select.h>


#include "global.h"

#define CTRL_K(key) ((key) & 0x1f)

typedef struct ADMIN {
    char username[NAME_SIZE];
    char password[PASS_SIZE];
} admin_t;

typedef struct contacts {
    char id[ID_SIZE];
    char name[NAME_SIZE];
    char surname[NAME_SIZE];

    char email[BUFF_SIZE];
    char phone[BUFF_SIZE];
    char address[MAXX_BUFF];
} contact_t;

void clr();
void menu();
void login();
void add_contact();
void list_contact();
void edit_contact();
void search_contact();
void delete_contact();
void exit_program(int);

void del_char(size_t);
void printline(contact_t *);
void print_banner(const char *);
void SetCursorPosition(short, short);
void rewrite_line(contact_t *, contact_t *, char *, size_t, char *, FILE*, FILE*, char);

int cgetch(void);
int getline_id(FILE*);
int get_conf(const char *);
int check_duplicate(const char *, FILE *);
int findline(contact_t *, char *, size_t, char *, FILE*);

char *quote(const char *);
char *stristr(char *, const char *);

size_t get_pass(const char *, char *);
ssize_t input(const char *, char *, size_t);

#endif // UTILITIES_H
