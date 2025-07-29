#include "Bank.h"
#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

bool Bank::isAdmin() const
{
    return currentUser && currentUser->getRole() == Role::Admin;
}

string Bank::generateAccountNumber()
{
    return "ACC" + to_string(nextAccountNumber++);
}

void Bank::createAccount(string name, double initialDeposit)
{
    string accNum = generateAccountNumber();
    BankAccount newAcc(name, accNum, initialDeposit, currentUser->getUsername());
    accounts.push_back(newAcc);
    cout << "Account create! Account Number: " << accNum << endl;
}

void Bank::depositToAccount(string accountNumber, double amount)
{
    BankAccount *acc = findAccount(accountNumber);
    if (acc)
    {
        if (acc->getOwnerUsername() != currentUser->getUsername() && currentUser->getRole() != Role::Admin)
        {
            cout << "Access denied: You do not own this account." << endl;
            return;
        }

        acc->deposit(amount);
        cout << "Deposit successful! New Balance: $" << acc->getBalance() << endl;
    }
    else
    {
        cout << "Account not found." << endl;
    }
}

void Bank::withdrawFromAccount(string accountNumber, double amount)
{
    BankAccount *acc = findAccount(accountNumber);
    if (acc)
    {
        if (acc->getOwnerUsername() != currentUser->getUsername() &&
            currentUser->getRole() != Role::Admin)
        {
            cout << "Access denied: You do not own this account." << endl;
            return;
        }

        if (acc->withdraw(amount))
        {
            cout << "Withdrawal successful! New Balance: $" << acc->getBalance() << endl;
        }
        else
        {
            cout << "Insufficient funds." << endl;
        }
    }
    else
    {
        cout << "Account not found." << endl;
    }
}

void Bank::displayAllAccounts() const
{
    if (accounts.empty())
    {
        cout << "No accounts to display" << endl;
        return;
    }

    if (!currentUser)
    {
        cout << "No user is currently logged in." << endl;
        return;
    }

    bool hasAccounts = false;

    cout << "\n--- ";
    if (currentUser->getRole() == Role::Admin)
    {
        cout << "All Bank Accounts ---\n"
             << endl;
        for (const auto &acc : accounts)
        {
            acc.display();
            hasAccounts = true;
        }
    }
    else
    {
        cout << "Your Bank Accounts ---\n"
             << endl;
        for (const auto &acc : accounts)
        {
            if (acc.getOwnerUsername() == currentUser->getUsername())
            {
                acc.display();
                hasAccounts = true;
            }
        }

        if (!hasAccounts)
        {
            cout << "You have no accounts." << endl;
        }
    }
}

BankAccount *Bank::findAccount(const string &accountNumber)
{
    for (auto &acc : accounts)
    {
        if (acc.getAccountNumber() == accountNumber)
        {
            return &acc;
        }
    }
    return nullptr;
}

bool Bank::registerUser(const string &username, const string &password, const string &email, Role role)
{
    // check for duplicate username
    for (const auto &user : users)
    {
        if (user.getUsername() == username)
        {
            return false; // username already taken
        }
    }

    // create and add new user
    User newUser(username, password, email, role);
    users.push_back(newUser);
    return true;
}

bool Bank::loginUser(const string &username, const string &password)
{
    for (const auto &user : users)
    {
        if (user.getUsername() == username && user.checkPassword(password))
        {
            currentUser = const_cast<User *>(&user);
            return true; // login successful
        }
    }
    return false; // No match found
}

void Bank::logoutUser()
{
    currentUser = nullptr;
    cout << "Successfully logged out." << endl;
}

User *Bank::getCurrentUser()
{
    return currentUser;
}

void Bank::saveData(const string &userFile, const string &accountFile) const
{
    // Save Users
    ofstream uFile(userFile);
    if (!uFile)
    {
        cout << "Error opening " << userFile << " for writing." << endl;
        return;
    }

    for (const auto &user : users)
    {
        uFile << user.getUsername() << '\n'
              << user.getEmail() << '\n'
              << user.getPasswordHash() << '\n'
              << static_cast<int>(user.getRole()) << '\n'
              << user.isAccountLocked() << '\n';
    }
    uFile.close();

    // Save accounts
    ofstream aFile(accountFile);
    if (!aFile)
    {
        cout << "Error opening " << accountFile << " for writing.\n";
        return;
    }

    for (const auto &acc : accounts)
    {
        aFile << acc.getAccountNumber() << '\n'
              << acc.getName() << '\n'
              << acc.getBalance() << '\n'
              << acc.getOwnerUsername() << '\n';
    }
    aFile.close();

    cout << "Data saved successfully.\n";
}

void Bank::loadData(const string &userFile, const string &accountFile)
{
    ifstream uFile(userFile);
    if (!uFile)
    {
        cout << "No saved users found.\n";
    }
    else
    {
        users.clear();
        string username, email;
        size_t passwordHash;
        int roleInt;
        bool locked;

        while (uFile >> username >> email >> passwordHash >> roleInt >> locked)
        {
            User loadedUser(username, "", email, static_cast<Role>(roleInt));
            loadedUser.setPasswordHash(passwordHash);
            if (locked)
                loadedUser.lock();

            users.push_back(loadedUser);
        }
        uFile.close();
        cout << "Users loaded successfully.\n";
    }

    ifstream aFile(accountFile);
    if (!aFile)
    {
        cout << "No saved accounts found.\n";
    }
    else
    {
        accounts.clear();
        string name, accountNumber, ownerUsername;
        double balance;

        while (aFile >> name >> accountNumber >> balance >> ownerUsername)
        {
            accounts.push_back(BankAccount(name, accountNumber, balance, ownerUsername));
        }
        aFile.close();
        cout << "Accounts loaded successfully.\n";
    }
}

void Bank::viewTransactionHistory(const string &accountNumber)
{
    BankAccount *acc = findAccount(accountNumber);
    if (acc)
    {
        acc->displayTransactionHistory();
    }
    else
    {
        cout << "Account not found." << endl;
    }
}

void Bank::viewAllUsers() const
{
    if (!currentUser || currentUser->getRole() != Role::Admin)
    {
        cout << "Access denied. Admins only.\n";
        return;
    }

    cout << "\n--- Registered Users ---\n";
    for (const auto &user : users)
    {
        cout << "Username: " << user.getUsername()
             << ", Email: " << user.getEmail()
             << ", Role: " << static_cast<int>(user.getRole())
             << ", Locked: " << (user.isAccountLocked() ? "Yes" : "No")
             << endl;
    }
}

bool Bank::lockUserAccount(const string &username)
{
    if (!isAdmin())
        return false;

    for (auto &user : users)
    {
        if (user.getUsername() == username)
        {
            user.lock();
            cout << username << " has been locked.\n";
            return true;
        }
    }
    cout << "User not found.\n";
    return false;
}

bool Bank::unlockUserAccount(const string &username)
{
    if (!isAdmin())
        return false;

    for (auto &user : users)
    {
        if (user.getUsername() == username)
        {
            user.setLock(false);
            cout << username << " has been unlocked.\n";
            return true;
        }
    }
    cout << "User not found.\n";
    return false;
}

bool Bank::changeUserRole(const string &username, Role newRole)
{
    if (!isAdmin())
        return false;

    for (auto &user : users)
    {
        if (user.getUsername() == username)
        {
            user.setRole(newRole);
            cout << username << "'s role updated.\n";
            return true;
        }
    }
    cout << "User not found.\n";
    return false;
}
