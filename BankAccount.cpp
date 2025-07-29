#include "BankAccount.h"
#include "User.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

BankAccount::BankAccount(string name, string accountNumber, double balance, string ownerUsername)
    : name(name), accountNumber(accountNumber), balance(balance), ownerUsername(ownerUsername) {}

string getCurrentTimestamp()
{
    time_t now = time(0);
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buffer);
}

void BankAccount::deposit(double amount)
{
    if (amount > 0)
    {
        balance += amount;

        // Record the transaction
        history.push_back({"Deposit", amount, balance, getCurrentTimestamp()});
    }
    else
    {
        cout << "Invalid deposit amount." << endl;
    }
}

bool BankAccount::withdraw(double amount)
{
    if (amount > 0 && amount <= balance)
    {
        balance -= amount;

        // Record the transaction
        history.push_back({"Withdraw", amount, balance, getCurrentTimestamp()});
        return true;
    }
    else
    {
        cout << "Invalid deposit amount." << endl;
    }
    return false;
}

void BankAccount::display() const
{
    cout << "Name: " << name << ", Account #: " << accountNumber << ", Balance: $" << balance << endl;
}

string BankAccount::getAccountNumber() const
{
    return accountNumber;
}

string BankAccount::getName() const
{
    return name;
}

double BankAccount::getBalance() const
{
    return balance;
}

string BankAccount::getOwnerUsername() const
{
    return ownerUsername;
}

void BankAccount::displayTransactionHistory() const
{
    if (history.empty())
    {
        cout << "No transactions for this account." << endl;
        return;
    }

    cout << "\n--- Transaction History for Account: " << accountNumber << " ---\n";
    for (const auto &t : history)
    {
        cout << t.timestamp << " | " << t.type
             << " | Amount: $" << t.amount
             << " | Balance: $" << t.resultingBalance << endl;
    }
}
