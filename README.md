# 💰 JP's C++ Banking System

A robust and interactive **command-line banking application** built in C++ that supports user authentication, role-based access, file persistence, and administrative account control. This project demonstrates a modular and secure design using object-oriented principles.

---

## 🚀 Features

- 🔐 **User Registration & Login** (with hashed passwords)
- 👥 **Role-Based Access Control**
  - `Customer` – regular banking user
  - `Worker` – staff-level access
  - `Admin` – full administrative privileges
- 💳 **Account Management**
  - Create Checking or Savings accounts
  - Deposit & Withdraw funds
- 📄 **Persistent Data**
  - Saves and loads data using `users.txt` and `accounts.txt`
- 👨‍💼 **Admin Panel**
  - View all users
  - Lock/Unlock user accounts
  - Change user roles
  - View all bank accounts
- 🧾 **Transaction History** (basic structure)

---

## 🛠️ Technologies Used

- C++17
- File I/O (`fstream`)
- Object-Oriented Design
- SHA-like password hashing (simulated using `std::hash`)

---

## 📂 Folder Structure

BankingSystem/
├── main.cpp
├── Bank.cpp / Bank.h
├── User.cpp / User.h
├── BankAccount.cpp / BankAccount.h
├── users.txt
├── accounts.txt
└── README.md

---

## 🧪 How to Compile & Run

### Compile:
```bash
g++ main.cpp Bank.cpp User.cpp BankAccount.cpp -o bank_app

Run:

./bank_app

## 📌 Example Admin Actions
When logged in as an admin, you'll have access to:

Viewing all users and their roles

Locking/unlocking accounts

Changing user roles

Viewing all bank accounts

---

🔒 Planned Improvements
Save transaction history to a separate file

GUI version using Qt

Enhanced password hashing (e.g., bcrypt)

Password recovery options

Input validation and cleaner UI output

---

🙌 Acknowledgements
Created by Jared Pearson
Built as a portfolio project to demonstrate practical C++ software development.


---

Let me know if you want me to:
- Include GitHub badges (build, license, etc.)
- Add screenshots of the program in action
- Add a logo/banner image for your project  
- Tailor it for Qt/GUI when you start that version
