#include "User.h"

using namespace std;

User::User() : id(""), name(""), phone(""), email("") {}

User::User(const string& idValue, const string& nameValue,
           const string& phoneValue, const string& emailValue)
    : id(idValue), name(nameValue), phone(phoneValue), email(emailValue) {}

string User::getId() const { return id; }
string User::getName() const { return name; }
string User::getPhone() const { return phone; }
string User::getEmail() const { return email; }

void User::setName(const string& value) { name = value; }
void User::setPhone(const string& value) { phone = value; }
void User::setEmail(const string& value) { email = value; }
