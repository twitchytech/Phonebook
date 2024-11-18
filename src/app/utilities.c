#include "../../include/app.h"


//? Function to get password from user
ssize_t get_pass(char *passwd) {
    if (passwd == NULL) {
        return ERR_NULPARAM;
    }

    int c;
    size_t len = 0;
    while ((c = cgetch()) != '\n' && c != '\r' && len < PASS_SIZE - 1) {
        if (c == '\b' && len > 0) {
            putchar('\b');
            putchar(' ');
            putchar('\b');
            len -= 1;
        }
        else if (c != '\b') {
            passwd[len] = (char)c;
            putchar('*');
            len += 1;
        }
        if (c == CTRL_C_KEY) {
            exit_program(EXIT_FAILURE);
        }
        
    }
    passwd[len] = '\0';
    return len;
}


//? Function to read data from 'stdin' or from a file
ssize_t get_line(char *line, size_t bytes, FILE *stream) {
    if (line == NULL || bytes < 1) {
        return ERR_NULPARAM;
    }

    int ch;
    size_t len = 0;
    
    while (len < bytes - 1 && (ch = fgetc(stream)) != EOF && ch != '\n') {
        line[len++] = (char)ch;
    }

    if (len == 0) {
        return (ch == EOF) ? EOF : ERR_DBREAD;
    }

    line[len] = '\0';
    return len;
}


//? Function to get input corresponding field from user
int get_field(char *field, size_t len) {
    ssize_t ret = get_line(field, len, stdin);
    if (ret == EOF)
        exit_program(EXIT_FAILURE);

    if (ret < EOF)
        return ret;
    
    //* Check if input contain file delimiter
    for (ssize_t i = 0; i < ret; i++) {
        if (field[i] == '|')
            return ERR_INVCHAR;
    }
    return SUCCESS;
}


//? Function to print all contacts on the database structure
void print_all(pdb_t *contacts, size_t count) {
    for (size_t i = 0; i < count; i++) {
        print_contact(contacts[i].row_id, &contacts[i].column);
    }
    
}


//? Function to check if the given phnoe has a duplicate
int is_duplicate(const pdb_t list[], const char *phone, size_t count) {
    for (size_t i = 0; i < count; i++) {
        if (compare_phone(list[i].column.phone, phone)) {
            return ERR_DUPLICATE;
        }
    }
    return SUCCESS;
}

//? Function to remove non-digits from the string
void prepare_phone(char *str) {
    char *src = str;
    char *dst = str;

    while (*src) {
        if (isdigit((unsigned char)*src)) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

//? Function to check if given phone numbers are the same
int compare_phone(const char *phone1, const char *phone2) {
    char tmp_phone1[strlen(phone1)];
    char tmp_phone2[strlen(phone2)];

    strncpy(tmp_phone1, phone1, strlen(phone1));
    strncpy(tmp_phone2, phone2, strlen(phone2));

    prepare_phone(tmp_phone1);
    prepare_phone(tmp_phone2);

    return strcmp(tmp_phone1, tmp_phone2) == 0;
}


//? Function to print page banner
void print_banner(const char *text) {
    printf("\033c");
    fprintf(stdout, "\n\t <{}{}{}{}{}{}{} %s {}{}{}{}{}{}{}>\n", text);
    fflush(stdout);
}


//? Funtion to prompt user for confirmation, returns [Y/N]
int get_conf(const char *prompt) {
    if (prompt) {
        printf("\n\t %s", prompt);
    }

    do {
        int c = toupper(cgetch());
        if (c == YES || c == NO) {
            return c;
        }
    } while (1);
}

void instructions(void) {
    printf("\n\t [*] Entry must not contain the '|' character");
    printf("\n\t [*] Email addresses can contain: ");
    printf("\n\t\t 1.) AlphaNumeric Characters"
           "\n\t\t 2.) Special Characters '@', '.', '-', '_' ");
    printf("\n\t [*] Phone Number can only have digits, space & '+ ( ) -'\n");
}

//? Prints error message corresponding to the error code
void log_error(const char *error) {
    fprintf(stderr, "\n\t [!] ERROR : %s", error);
    get_char();
}

//? Returns error message based on the return value
const char *get_errMsg(const int code) {
    switch (code) {
        case ERR_ENOMEM :
            return "Out of memory.";
        case ERR_NOFILE :
            return "Database file not found.";
        case ERR_NODATA :
            return "No data available.";

        case ERR_DBOPEN :
            return "Database open error.";
        case ERR_DBREAD :
            return "Database read error.";
        case ERR_DBWRITE :
            return "Database write error.";

        case ERR_ARRSIZE :
            return "Invalid array size.";
        case ERR_IOERROR :
            return "I/O error.";
        case ERR_BUFSIZE :
            return "Buffer size exceeded.";

        case ERR_DUPLICATE :
            return "Duplicate entry.";
        case ERR_NULPARAM :
            return "Null input parameter.";
        case ERR_NOTFOUND :
            return "Contact data not found.";
        case ERR_PARSER_FAILED :
            return "Failed to parse contact.";

        case ERR_INVKEY :
            return "Invalid key.";
        case ERR_INVCHAR :
            return "Input string contains invalid characters.";
        case ERR_INVCREDS :
            return "Invalid credentials, Incorrect Username/Password.";
        default :
            return "An unknown error has occurred.";
    }
}


int cgetch(void){
    #ifdef _WIN32
        return getch();
    #else
        //* On non-Windows systems, set the terminal to non-canonical mode to get a character.
        struct termios old_tio, new_tio;

        tcgetattr(STDIN_FILENO, &old_tio);
        new_tio = old_tio;
        new_tio.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

        const int c = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
        return c;
    #endif
}

int get_char(void) {
    int c = cgetch();
    if (c == CTRL_C_KEY) {
        exit_program(EXIT_FAILURE);
    }
    return c - '0';
}

void exit_program(const int code) {
    switch (code) {
        case EXIT_SUCCESS :
            exit(EXIT_SUCCESS);
        default:
            printf("\n\t [!] PROGRAM ABRUPTLY TERMINATED");
            exit(EXIT_FAILURE);
    }
}
