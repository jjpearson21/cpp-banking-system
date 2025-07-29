#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <vector>
using namespace std;

class BankAccount
{
    struct Transaction
    {
        string type;
        double amount;
        double resultingBalance;
        string timestamp;
    };

private:
    string name;
    string accountNumber;
    double balance;
    string ownerUsername;
    vector<Transaction> history;

public:
    BankAccount(string name, string accountNumber, double balance = 0.0, string ownerUsername = "");

    void deposit(double amount);
    bool withdraw(double amount);
    void display() const;

    string getAccountNumber() const;
    string getName() const;
    double getBalance() const;

    string getOwnerUsername() const;
    void displayTransactionHistory() const;
};

#endif