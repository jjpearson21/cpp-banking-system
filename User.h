#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

enum class Role
{
    Customer,
    Worker,
    Admin
};

class User
{
private:
    string username;
    string password;
    string email;
    bool isLocked;
    int loginAttempts;
    Role role;
    size_t passwordHash;

public:
    User();
    User(string username, string rawPassword, string email, Role role);

    bool checkPassword(string rawInput) const;
    void setPassword(string newPassword);
    void setRole(Role r);
    Role getRole() const;
    string getUsername() const;
    string getEmail() const;
    void lock();
    bool isAccountLocked() const;
    void resetLoginAttempts();
    string getPassword() const;
    size_t getPasswordHash() const;
    void setPasswordHash(size_t hash);
    void setLock(bool lockStatus);
};

#endif