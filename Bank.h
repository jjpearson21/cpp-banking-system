#ifndef BANK_H
#define BANK_H

#include "BankAccount.h"
#include "User.h"
#include <string>
#include <vector>
using namespace std;

class Bank
{
private:
    vector<BankAccount> accounts;
    int nextAccountNumber = 1000;

    string generateAccountNumber();

    vector<User> users;
    User *currentUser = nullptr;

public:
    void createAccount(string name, double initialDeposit = 0.0);
    void depositToAccount(string accountNumber, double amount);
    void withdrawFromAccount(string accountNumber, double amount);
    void displayAllAccounts() const;
    BankAccount *findAccount(const string &accountNumber);

    bool registerUser(const string &username, const string &password, const string &email, Role role);
    bool loginUser(const string &username, const string &password);
    void logoutUser();
    User *getCurrentUser();

    void saveData(const string &userFile, const string &accountFile) const;
    void loadData(const string &userFile, const string &accountFile);

    void viewTransactionHistory(const string &accountNumber);

    // === ADMIN FUNCTIONS ===
    void viewAllUsers() const;                                 // List all users
    bool lockUserAccount(const string &username);              // Lock a user's account
    bool unlockUserAccount(const string &username);            // Unlock a user's account
    bool changeUserRole(const string &username, Role newRole); // Promote/demote users
    bool isAdmin() const;
};

#endif