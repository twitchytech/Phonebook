#include "../../include/app.h"


//? Function that allows the user to add a new contact to the phonebook.
void add_contact(void) {
    int c = YES;
    contact_t new_contact;

    pdb_t contact_list[MAX_CONTACT];
    int contact_count = load_db(contact_list);
    if (contact_count <= 0) {
        log_error(get_errMsg(contact_count));
        return;
    }
    
    do {
        print_banner("PHONEBOOK | ADD NEW CONTACT");

        int ret = get_contact(&new_contact);
        if (ret) {
            log_error(get_errMsg(ret));
            continue;
        }
        
        if (is_duplicate(contact_list, new_contact.phone, contact_count)) {
            log_error(get_errMsg(ERR_DUPLICATE));
            continue;
        }

        contact_list[contact_count].row_id = contact_count;
        add_new_row(contact_list, &new_contact, contact_list[contact_count].row_id);
        
        contact_count += 1;
        c = get_conf("Do yo want to add another contact? [Y/N] : ");
    } while (c == YES);

    overwrite_db(contact_list, contact_count);

    menu();
}


//? Function that allows the user to edit contact details from the phonebook.
void modify_contact(void) {
    int c = YES;
    contact_t new_contact;

    pdb_t contact_list[MAX_CONTACT];
    int count = load_db(contact_list);
    if (count < 0) {
        log_error(get_errMsg(count));
        return;
    }
    
    do {
        print_banner("PHONEBOOK | MODIFY CONTACTS");

        char phone[NAME_SIZE];
        printf("\n\t [$] Search for the contact you want to modify (search by phone) : ");
        get_line(phone, sizeof(phone), stdin);

        int id = -1, found = 0;
        for (int i = 0; i < count; i++) {
            if (compare_phone(contact_list[i].column.phone, phone)) {
                found = 1;
                id = contact_list[i].row_id;
                break;
            }
        }
        
        if (found) {
            printf("\n\t [?] Enter new data of the contact you want to modify.\n");

            int ret = get_contact(&new_contact);
            if (ret) {
                log_error(get_errMsg(ret));
                continue;
            }
            
            if (is_duplicate(contact_list, new_contact.phone, count)) {
                log_error(get_errMsg(ERR_DUPLICATE));
                continue;
            }
            modify_row(contact_list, &new_contact, id);
        }
        else {
            printf("\n\t Contact record not found.\n");
        }
        
        c = get_conf("\n\t Do you want to perform another search? [Y/N] : ");

    } while (c == YES);

    overwrite_db(contact_list, count);

    menu(); //* Redirects to the main menu.
}


//? Function to displays a list of all contacts in the phonebook.
void display_contacts(void) {
    print_banner("PHONEBOOK | CONTACT LIST");

    pdb_t contact_list[MAX_CONTACT];
    int count = load_db(contact_list);
    if (count <= 0) {
        log_error(get_errMsg(count));
        return;
    }

    print_all(contact_list, count);
    printf("\n\t [$] Press any key to go back to the main menu : ");
    get_char();
    menu();
}


//? Function that allows the user to search for a contact from the phonebook by (phone number).
void browse_contacts() {
    int c = NO;
    
    pdb_t contact_list[MAX_CONTACT];
    int count = load_db(contact_list);
    if (count < 0) {
        log_error(get_errMsg(count));
        return;
    }

    do {
        int found = 0;
        print_banner("PHONEBOOK | SEARCH CONTACTS");

        char phone[NAME_SIZE];
        printf("\n\t [$] Searc for the contact by phone : ");
        get_line(phone, sizeof(phone), stdin);

        for (int i = 0; i < count; i++) {
            if (compare_phone(contact_list[i].column.phone, phone)) {
                print_contact(contact_list[i].row_id, &contact_list[i].column);
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("\n\t Contact record not found.\n");
        }
        c = get_conf("\n\t Do you want to perform another search? [Y/N] : ");
    } while (c == YES);
    menu();
}


//? Function to delete a contact from the phonebook database
void delete_contact(void) {
    pdb_t contact_list[MAX_CONTACT];
    int count = load_db(contact_list);
    if (count < 0) {
        log_error(get_errMsg(count));
        return;
    }

    int found = 0;
    print_banner("PHONEBOOK | DELETE CONTACTS");
    
    char phone[BUFF_SIZE];
    printf("\n\t [$] Search for contact you want to delete (by phone) : ");
    get_line(phone, sizeof(phone), stdin);
    
    FILE *fptr = fopen(DBFILEPATH, WRITEMODE);
    if (fptr == NULL) {
        log_error(get_errMsg(ERR_DBOPEN));
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (compare_phone(contact_list[i].column.phone, phone)) {
            print_contact(contact_list[i].row_id, &contact_list[i].column);
            found = 1;
            continue;
        }
        insert_contact(&contact_list[i].column, fptr);
    }
    fclose(fptr);

    if (!found) {
        log_error(get_errMsg(ERR_NOTFOUND));
    }
    else {
        printf("\n\t [$] Contact deleted successfully.");
    }
    
    printf("\n\t Press any key to go back to the main menu : ");
    get_char();
    menu();
}

//? Function to print given contact details
void print_contact(int id, contact_t *contact) {
    printf("\n\t[%02i].", id + 1);
    printf("\n\t   NAME     :  %s, %s", contact->surname, contact->name);
    printf("\n\t   EMAIL    :  %s", contact->email);
    printf("\n\t   PHONE    :  %s", contact->phone);
    printf("\n\t   ADDRESS  :  %s", contact->address);

    printf("\n\n");
}

//? Function to handle login process for the phonebook app
void login(void) {
    int check;

    print_banner("AUTHORIZED USER'S ONLY");

    admin_t admin;
    do {
        printf("\n\t Enter your username : ");
        get_line(admin.username, NAME_SIZE, stdin);
        printf("\n\t Enter your password : ");
        get_pass(admin.password);

        check = (strcmp(admin.username, "admin") == 0) && (strcmp(admin.password, "admin") == 0);
        if (!check) {
            log_error(get_errMsg(ERR_INVCREDS));
        }
    } while (!check);
    menu();
}

//? Function to display the main menu of the phonebook app
void menu(void) {
    print_banner("PHONEBOOK DIRECTORY | MAIN MENU");
    //printf("\n\t\t MAIN MENU ");
    printf("\n\t [1]. ADD NEW CONTACT \t[2]. EDIT CONTACT   \t[3]. LIST CONTACTS  "
           "\n\t [4]. BROWSE CONTACTS \t[5]. DELETE CONTACT \t[6]. EXIT PROGRAM   ");

    int check = 0;
    //* Display the menu and handle user choices.
    do {
        switch (get_char()) {
            case CREATE :
                add_contact();
                break;
            case MODIFY :
                modify_contact();
                break;
            case DISPLAY :
                display_contacts();
                break;
            case BROWSE :
                browse_contacts();
                break;
            case REMOVE :
                delete_contact();
                break;
            case EXIT :
                exit_program(EXIT_SUCCESS);
                break;
            default :
                check = -1;
        }
    } while (check == -1);
}


//? Function to get new contact details from user
int get_contact (contact_t *person) {
    memset(person, 0, sizeof(contact_t));

    instructions();
    
    printf("\n\t [$] FIRSTNAME :  ");
    int ret = get_field(person->name, NAME_SIZE);
    if (ret) return ret;
    
    printf("\n\t [$] LASTNAME  :  ");
    ret = get_field(person->surname, NAME_SIZE);
    if (ret) return ret;

    printf("\n\t [$] EMAIL     :  ");
    ret = get_field(person->email, BUFF_SIZE);
    if (ret) return ret;

    printf("\n\t [$] PHONE     :  ");
    ret = get_field(person->phone, BUFF_SIZE);
    if (ret) return ret;
    
    printf("\n\t [$] ADDRESS   :  ");
    ret = get_field(person->address, ADDR_SIZE);
    if (ret) return ret;
    
    return SUCCESS;
}
