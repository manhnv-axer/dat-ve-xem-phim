#pragma once

#include <string>

using namespace std;

// Lop User la lop co so truu tuong vi co phuong thuc ao thuan tuy.
// Day la abstract class thu nhat cua he thong.
class User {
protected:
    string id;
    string name;
    string phone;
    string email;

public:
    User();
    User(const string& id, const string& name,
         const string& phone, const string& email = "");
    virtual ~User() = default;

    string getId() const;
    string getName() const;
    string getPhone() const;
    string getEmail() const;

    void setName(const string& value);
    void setPhone(const string& value);
    void setEmail(const string& value);

    virtual string getType() const = 0;
    virtual void displayInfo() const = 0;
};
