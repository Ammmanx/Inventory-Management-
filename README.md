# 📦 Inventory Management System
> A terminal-based multi-user inventory management application written in C.

---

## 🗂️ Overview

This project is a **file-based inventory management system** built in C. It supports multiple users with individual login credentials, each having their own isolated inventory stored as a CSV file. Users can add, view, search, edit, and delete items from their personal inventory — all from a clean terminal interface.

---

## ✨ Features

- 🔐 **User Authentication** — Login and registration with masked password input
- 📋 **Personal Inventories** — Each user gets their own isolated CSV inventory file
- ➕ **Add Items** — Record item ID, name, and quantity
- 👁️ **View Items** — Display all inventory in a formatted table
- 🔍 **Search Items** — Search by item ID with full details
- ✏️ **Edit Items** — Update ID, name, or quantity of any item
- 🗑️ **Delete Items** — Remove items with a confirmation prompt
- 🛡️ **Input Validation** — Buffer-safe inputs and duplicate ID checks

---

## 📁 Project Structure

```
├── 1_main.c          # Entry point — starts the login flow
├── 2_login.c         # Login/Signup menu
├── 3_sign_in.c       # Credential verification against id.csv
├── 4_register.c      # New user registration
├── 5_main_screen.c   # Main menu (Add / View / Search / Exit)
├── add_item.c        # Add new inventory item
├── view_items.c      # Display all items in a table
├── search_item.c     # Search item by ID; leads to edit/delete
├── edit_items.c      # Edit an existing item's field
├── delete_item.c     # Delete an item with confirmation
├── file_create.c     # Creates a new user inventory CSV file
├── password.c        # Masked password input using getch()
├── inventory.h       # Header file — all function declarations
├── id.csv            # User credentials store (auto-created)
└── data_base/        # Folder containing per-user inventory CSVs
```

---

## 🚀 Getting Started

### Prerequisites

- GCC compiler (MinGW on Windows recommended)
- Windows OS — the project uses `<conio.h>` and `getch()` for masked password input

### Compilation

Compile all `.c` files together:

```bash
gcc 1_main.c 2_login.c 3_sign_in.c 4_register.c 5_main_screen.c \
    add_item.c view_items.c search_item.c edit_items.c delete_item.c \
    file_create.c password.c -o inventory.exe
```

### Run

```bash
./inventory.exe
```

---

## 🗄️ Data Storage

| File | Purpose |
|------|---------|
| `id.csv` | Stores all usernames and passwords in `username,password` format |
| `data_base/<username>_inventory.csv` | Per-user inventory with columns: `Item_ID, Item_Name, Item_Quantity` |

> ⚠️ Make sure the `data_base/` directory exists before running, or the program will fail to create user files.

```bash
mkdir data_base
```

---

## 🔄 Application Flow

```
main()
  └── login()
        ├── sign_in()  →  main_screen()
        └── reg()      →  main_screen()
                              ├── add_item()
                              ├── view_item()  →  search_item()
                              └── search_item()
                                    ├── edit_item()
                                    └── delete_item()
```

---

## ⚠️ Known Limitations

- Uses `<conio.h>` — **Windows only** (not portable to Linux/macOS without modification)
- Passwords are stored in **plain text** in `id.csv` — not suitable for production use
- Recursive calls to `main_screen()` and `add_item()` can cause **stack buildup** on very long sessions
- No support for spaces in item names or IDs (uses `scanf("%s", ...)`)

---

## 🛣️ Roadmap / Future Improvements

- [ ] Replace plain-text passwords with hashed storage
- [ ] Replace `<conio.h>` with a portable input solution
- [ ] Replace recursion with loops in navigation functions
- [ ] Add support for item names with spaces
- [ ] Connect to a proper database (MySQL/SQLite)
- [ ] Add low-stock alerts and reporting features

---

## 👨‍💻 Author

Built as a learning project in C programming, focusing on file I/O, struct-free data management, and modular code organization.

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
