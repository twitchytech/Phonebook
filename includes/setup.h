#ifndef DB_H
#define DB_H
#pragma once

#include "utilities.h"

#define TMPDBPATH  "../data/tmp.dat"
#define DBFILEPATH "../data/database.dat"

bool init_default();
bool get_contact(contact_t *, FILE *);
void parse_line(const char *, contact_t *);
bool finalize_changes(const char *, const char *);
bool delete_by_phone(FILE *, FILE *, const char *);
bool search_by_phone(FILE *, const char *, contact_t *);
bool modify_line(FILE *, FILE *, const char *, const contact_t *);

int get_arrow_key(int);
int highlight_line(int, int, int);

void delay(uint32_t);
void display_loader(const char *);
void print(const char *,...) __attribute__((format(printf, 1, 2)));
void mvprint(int, const char *,...) __attribute__((format(printf, 2, 3)));
void print_menu(size_t, size_t, char [][ID_SIZE], char [][BUFF_SIZE]);

#endif //DB_H
