#  Personal Expense Tracker in C

A **console-based Personal Expense Tracker** built in the C programming language to help users record, manage, and analyze their daily, weekly, and monthly expenses. This project supports **multiple users**, **login/registration**, **monthly summary reports**, and even **ASCII-based visualizations** for category-wise spending.

This is a great project to demonstrate your understanding of **file handling**, **structs**, **functions**, **user authentication**, and basic **data analysis in C**.

---

##  Table of Contents

- [Features](#-features)
- [Screenshots](#-screenshots)
- [How It Works](#-how-it-works)

---

##  Features

-  **User Registration & Login System**
  - Allows new users to create an account
  - Secure login with password check

-  **Add, View, Delete Expenses**
  - Store expenses with category, date, and amount
  - Display data in tabular format

-  **Monthly Summary Reports**
  - Automatically filters expenses based on month and year
  - Shows total amount spent in a month

-  **File Encryption (Basic XOR-based)**
  - Encrypts and decrypts sensitive data stored in files

-  **Category-wise Visualization in ASCII**
  - Displays spending distribution with text-based bars for categories

-  **Persistent File Storage**
  - Saves user data and expense logs into user-specific files

---

##  Screenshots (Console Output)

<img width="472" height="551" alt="expense_tracker_sample output" src="https://github.com/user-attachments/assets/549b32b7-5eb9-4226-82e5-ebd38afe623c" />


---

## ⚙️ How It Works

- The app starts by asking users to **login or register**
- After successful login, users can **add expenses** by entering:
  - Amount
  - Date
  - Category (e.g., Food, Travel, Shopping)
  - Note (optional)
- The data is stored in a text file (`expenses_username.txt`)
- Users can:
  - View all past expenses
  - Delete individual entries
  - View monthly reports with total spend
  - See category distribution as visual bar graphs

---




