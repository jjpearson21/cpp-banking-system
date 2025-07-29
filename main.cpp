#include "BankAccount.h"
#include "Bank.h"
#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

void showMainMenu()
{
    cout << "\n=== Welcome to JP's Bank ===" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter Choice: ";
}

void showBankMenu(User *currentUser)
{
    cout << "\n=== Bank Menu ===" << endl;
    cout << "1. Create New Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. View Transaction History" << endl;
    cout << "5. View Accounts" << endl;
    cout << "6. Logout" << endl;
    cout << "Enter Choice: ";
}

void showAdminMenu()
{
    cout << "\n=== ADMIN MENU ===" << endl;
    cout << "1. View All Users" << endl;
    cout << "2. Unlock User Account" << endl;
    cout << "3. Lock User Account" << endl;
    cout << "4. Change User Role" << endl;
    cout << "5. View All Bank Accounts" << endl;
    cout << "6. Logout" << endl;
    cout << "Enter Choice: " << endl;
}

int main()
{
    Bank JPBank;
    int choice;

    JPBank.loadData("users.txt", "accounts.txt");

    while (true)
    {
        system("cls");
        showMainMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            // Register
            string username, password, email;
            int roleChoice;
            system("cls");
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
            cout << "Enter email: ";
            getline(cin, email);
            cout << "Role? (1 = Customer, 2 = Worker, 3 = Admin): ";
            cin >> roleChoice;
            cin.ignore();

            Role role = Role::Customer;
            if (roleChoice == 2)
                role = Role::Worker;
            else if (roleChoice == 3)
                role = Role::Admin;

            if (JPBank.registerUser(username, password, email, role))
                cout << "Registration successful!\n";
            else
                cout << "Username already taken.\n";
        }
        else if (choice == 2)
        {
            // Login
            string username, password;
            system("cls");
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);

            if (JPBank.loginUser(username, password))
            {
                system("cls");
                cout << "Login successful!\n";

                int bankChoice;
                do
                {
                    system("cls");
                    showBankMenu(JPBank.getCurrentUser());

                    // If the logged-in user is an admin, show admin menu
                    if (JPBank.isAdmin())
                    {
                        system("cls");
                        showAdminMenu();
                    }

                    cin >> bankChoice;
                    cin.ignore();

                    if (JPBank.isAdmin() && bankChoice >= 1 && bankChoice <= 5)
                    {
                        // Admin menu actions
                        switch (bankChoice)
                        {
                        case 1:
                            system("cls");
                            JPBank.viewAllUsers();
                            break;
                        case 2:
                        {
                            system("cls");
                            string targetUser;
                            cout << "Enter username to unlock: ";
                            cin >> targetUser;
                            JPBank.lockUserAccount(targetUser);
                            break;
                        }
                        case 3:
                        {
                            system("cls");
                            string targetUser;
                            cout << "Enter username to unlock: ";
                            cin >> targetUser;
                            JPBank.unlockUserAccount(targetUser);
                            break;
                        }
                        case 4:
                        {
                            system("cls");
                            string targetUser;
                            int roleChoice;
                            cout << "Enter username to change role: ";
                            cin >> targetUser;
                            cout << "New role (1 = Customer, 2 = Worker, 3 = Admin): ";
                            cin >> roleChoice;
                            JPBank.changeUserRole(targetUser, static_cast<Role>(roleChoice - 1));
                            break;
                        }
                        case 5:
                            system("cls");
                            JPBank.displayAllAccounts();
                            break;
                        case 6:
                            system("cls");
                            cout << "Logging out...\n";
                            break;
                        }
                    }
                    else
                    {
                        // Regular bank actions
                        switch (bankChoice)
                        {
                        case 1:
                        {
                            system("cls");
                            int accountChoice;
                            string accountType;
                            double deposit;
                            cout << "Is this a checkings (1) or savings account (2)? ";
                            cin >> accountChoice;
                            accountType = (accountChoice == 1) ? "Checkings" : "Savings";
                            cout << "Initial deposit: ";
                            cin >> deposit;
                            JPBank.createAccount(accountType, deposit);
                            break;
                        }
                        case 2:
                        {
                            system("cls");
                            string accNum;
                            double amount;
                            cout << "Enter account number: ";
                            cin >> accNum;
                            cout << "Deposit amount: ";
                            cin >> amount;
                            JPBank.depositToAccount(accNum, amount);
                            break;
                        }
                        case 3:
                        {
                            system("cls");
                            string accNum;
                            double amount;
                            cout << "Enter account number: ";
                            cin >> accNum;
                            cout << "Withdraw amount: ";
                            cin >> amount;
                            JPBank.withdrawFromAccount(accNum, amount);
                            break;
                        }
                        case 4:
                        {
                            system("cls");
                            string accNum;
                            cout << "Enter account number: ";
                            cin >> accNum;
                            JPBank.viewTransactionHistory(accNum);
                            break;
                        }
                        case 5:
                            system("cls");
                            JPBank.displayAllAccounts();
                            break;
                        case 6:
                            system("cls");
                            JPBank.logoutUser();
                            break;
                        default:
                            cout << "Invalid choice.\n";
                        }
                    }

                    system("pause");
                } while (bankChoice != 6 && (!JPBank.isAdmin() || bankChoice != 6));
            }
            else
            {
                system("cls");
                cout << "Login failed. Check your username or password.\n";
            }
        }
        else if (choice == 3)
        {
            system("cls");
            cout << "Goodbye!\n";
            break;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }

    JPBank.saveData("users.txt", "accounts.txt");

    return 0;
}