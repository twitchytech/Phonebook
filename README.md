# Phonebook Application

The Phonebook Application is a terminal-based contact management system that allows users to store, edit, list, search, and delete contact information in a file.

## Features

- **Add New Contact**: Add a new contact with details such as name, email, phone, and address.

- **Edit Contact**: Modify existing contact details.

- **List Contacts**: View a list of all stored contacts.

- **Search Contacts**: Find specific contacts by name.

- **Delete Contact**: Remove unwanted contacts.

## Prerequisites

- [GCC](https://gcc.gnu.org/) or any other C compiler for building the project.

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/msio808/Phonebook.git
   ```

   ```bash
   cd Phonebook
   ```

2. Build Program **`GCC`**:

   ```bash
   make
   ```
   
3. Run program **`GDB`**:
-  On Windows
   ```bash
   .\build\phonebook.exe
   ```
-  On Linux
   ```bash
   ./build/phonebook
   ```

## Usage

1. You will be prompted to log in with a predefined username and password. The default is "admin" for both.

2. Use the menu to navigate through the application's features.

## Function Descriptions

- **`add_contact()`**: Adds a new contact to the phonebook.

- **`edit_contact()`**: Edits an existing contact's details.

- **`list_contact()`**: Lists all contacts in the phonebook.

- **`search_contact()`**: Searches for a contact by name.

- **`delete_contact()`**: Deletes a contact from the phonebook.

- **`exit_program(int)`**: Exits the program.

## License

This project is licensed under the MIT License - see the [LICENSE](../LICENSE) file for details.