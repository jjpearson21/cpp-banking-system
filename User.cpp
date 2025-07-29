#include "User.h"
#include <iostream>
#include <functional>

using namespace std;

User::User() : username(""), password(""), email(""), role(Role::Customer), isLocked(false), loginAttempts(0) {}

User::User(string username, string rawPassword, string email, Role role)
    : username(username), email(email), role(role), isLocked(false), loginAttempts(0)
{
    setPassword(rawPassword);
}

bool User::checkPassword(string rawInput) const
{
    hash<string> hasher;
    return passwordHash == hasher(rawInput);
}

void User::setPassword(string newPassword)
{
    hash<string> hasher;
    passwordHash = hasher(newPassword);
}

Role User::getRole() const
{
    return role;
}

void User::setRole(Role r)
{
    role = r;
}

string User::getUsername() const
{
    return username;
}

string User::getEmail() const
{
    return email;
}

void User::lock()
{
    isLocked = true;
}

bool User::isAccountLocked() const
{
    return isLocked;
}

void User::resetLoginAttempts()
{
    loginAttempts = 0;
}

string User::getPassword() const
{
    return password;
}

size_t User::getPasswordHash() const
{
    return passwordHash;
}

void User::setPasswordHash(size_t hash)
{
    passwordHash = hash;
}

void User::setLock(bool lockStatus)
{
    isLocked = lockStatus;
}
