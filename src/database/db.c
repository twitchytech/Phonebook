#include "../../include/app.h"

static contact_t default_contacts[] = {
    {
        .name    = "Ryan",
        .surname = "Owens",
        .email   = "default@default.com",
        .phone   = "+109 112 4301",
        .address = "1234 Elm Street, Springfield, MA 01103",
    },
    {
        .name    = "Julia",
        .surname = "Ellis",
        .email   = "j.ellis@randatmail.com",
        .phone   = "+871 530 8168",
        .address = "567 Willow Avenue, Pleasantville, NY 10570",
    },
    {
        .name    = "Caroline",
        .surname = "Hunt",
        .email   = "c.hunt@randatmail.com",
        .phone   = "+451 964 6781",
        .address = "789 Maple Lane, Rivertown, CA 90210",
    },
    {
        .name    = "Walter",
        .surname = "Nelson",
        .email   = "w.nelson@randatmail.com",
        .phone   = "+674 523 6149",
        .address = "456 Oak Drive, Meadowville, TX 75001",
    },
    {
        .name    = "Mary",
        .surname = "Crawford",
        .email   = "m.crawford@randatmail.com",
        .phone   = "+954 200 8072",
        .address = "234 Birch Road, Lakeside, FL 32073",
    },
    {
        .name    = "Jared",
        .surname = "Douglas",
        .email   = "j.douglas@randatmail.com",
        .phone   = "+872 698 0149",
        .address = "678 Pine Street, Mountainview, WA 98101",
    },
    {
        .name    = "Alexia",
        .surname = "Richardson",
        .email   = "a.richardson@randatmail.com",
        .phone   = "+811 121 5251",
        .address = "901 Spruce Court, Woodville, NC 27858",
    },
    {
        .name    = "William",
        .surname = "Hamilton",
        .email   = "w.hamilton@randatmail.com",
        .phone   = "+743 711 5457",
        .address = "567 Magnolia Avenue, Brookside, NV 89501",
    },
    {
        .name    = "Clark",
        .surname = "Casey",
        .email   = "c.casey@randatmail.com",
        .phone   = "+212 331 1973",
        .address = "890 Cedar Avenue, Harbor City, OR 97201",
    },
    {
        .name    = "Savana",
        .surname = "Moore",
        .email   = "s.moore@randatmail.com",
        .phone   = "+990 271 7037",
        .address = "345 Redwood Lane, Sunnyside, AZ 85701",
    }
};


//? Creates database if it doesn't exist and add default contact details
int setup_db() {
    if (access(DBFILEPATH, F_OK) == 0) {
        return SUCCESS;
    }

    FILE *db = fopen(DBFILEPATH, WRITEMODE);
    if (db == NULL) {
        return ERR_DBOPEN;
    }

    size_t count = sizeof(default_contacts)/sizeof(default_contacts[0]);
    for (size_t i = 0; i < count; i++) {
        insert_contact(&default_contacts[i], db);
    }

    fclose(db);
    return SUCCESS;
}


//? Function to insert contact data to the database file
void insert_contact(contact_t *contact, FILE *fptr) {
    fprintf(fptr, "%s | %s | %s | %s | %s\n", contact->name,
        contact->surname, contact->email,
        contact->phone, contact->address);
}


//? Function to overwrite database file with
int overwrite_db(pdb_t list[], size_t count) {
    FILE *fptr = fopen(DBFILEPATH, WRITEMODE);
    if (fptr == NULL) {
        return ERR_DBWRITE;
    }
    
    for (size_t i = 0; i < count; i++) {
        insert_contact(&list[i].column, fptr);
    }
    fclose(fptr);
    return SUCCESS;
}


//? Function to read data from the database and store it file to the db tble structure
int load_db(pdb_t table[]) {
    FILE *fptr = fopen(DBFILEPATH, READMODE);
    if (fptr == NULL) {
        return ERR_DBREAD;
    }
    int ret = 0;
    int count = 0;
    char data[LINE_SIZE];

    while ((ret = get_line(data, sizeof(data), fptr)) != EOF) {
        if (ret > 0) {
            ret = parse_contact(data, &table[count].column);
            if (ret) {
                fclose(fptr);
                return ret;
            }
            table[count].row_id = count;
            count += 1;
        }
    }
    
    fclose(fptr);
    return count;
}


//? Function to add contact to new row in the database table structure
void add_new_row(pdb_t contact_list[], contact_t *contact, size_t index) {
    if (index >= MAX_CONTACT) {
        printf("Error: Index out of bounds.\n");
        return;
    }

    snprintf(contact_list[index].column.name, NAME_SIZE, "%s", contact->name);
    snprintf(contact_list[index].column.surname, NAME_SIZE, "%s", contact->surname);
    snprintf(contact_list[index].column.email, BUFF_SIZE, "%s", contact->email);
    snprintf(contact_list[index].column.phone, BUFF_SIZE, "%s", contact->phone);
    snprintf(contact_list[index].column.address, ADDR_SIZE, "%s", contact->address);

    contact_list[index].row_id = index;
}


//? Function to modify a row from the database table structure
void modify_row(pdb_t table[], contact_t *row, const int row_id) {
    snprintf(table[row_id].column.name, NAME_SIZE, "%s", row->name);
    snprintf(table[row_id].column.surname, NAME_SIZE, "%s", row->surname);
    snprintf(table[row_id].column.email, BUFF_SIZE, "%s", row->email);
    snprintf(table[row_id].column.phone, BUFF_SIZE, "%s", row->phone);
    snprintf(table[row_id].column.address, ADDR_SIZE, "%s", row->address);
}


//? Function to extract contact data from the line array and parse to the contact_t structure
int parse_contact(const char *line, contact_t *contact) {
    if (line == NULL || contact == NULL) {
        return ERR_NULPARAM;
    }
    char buffer[LINE_SIZE];
    snprintf(buffer, sizeof(buffer), "%s", line);

    //* Extract FirstName
    char *start = buffer;
    char *end = strstr(start, DELIM);
    if (end == NULL) {
        return ERR_PARSER_FAILED;
    }
    size_t length = end - start;
    if (length >= NAME_SIZE) {
        return ERR_BUFSIZE;
    }
    snprintf(contact->name, NAME_SIZE, "%.*s", (int)length, start);

    size_t delim_size = strlen(DELIM);

    //* Extract LastName
    start = end + delim_size;
    end = strstr(start, DELIM);
    if (end == NULL) {
        return ERR_PARSER_FAILED;
    }
    length = end - start;
    if (length >= NAME_SIZE) {
        return ERR_BUFSIZE;
    }
    snprintf(contact->surname, NAME_SIZE, "%.*s", (int)length, start);

    //* Extract Email
    start = end + delim_size;
    end = strstr(start, DELIM);
    if (end == NULL) {
        return ERR_PARSER_FAILED;
    }
    length = end - start;
    if (length >= BUFF_SIZE) {
        return ERR_BUFSIZE;
    }
    snprintf(contact->email, BUFF_SIZE, "%.*s", (int)length, start);

    //* Extract Phone
    start = end + delim_size;
    end = strstr(start, DELIM);
    if (end == NULL) {
        return ERR_PARSER_FAILED;
    }
    length = end - start;
    if (length >= BUFF_SIZE) {
        return ERR_BUFSIZE;
    }
    snprintf(contact->phone, BUFF_SIZE, "%.*s", (int)length, start);

    //* Extract Address
    start = end + delim_size;
    length = strlen(start);
    if (length >= ADDR_SIZE) {
        return ERR_BUFSIZE;
    }
    snprintf(contact->address, ADDR_SIZE, "%.*s", (int)length, start);

    return SUCCESS;
}
