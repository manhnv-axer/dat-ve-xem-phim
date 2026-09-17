#pragma once

#include "../User/User.h"

using namespace std;

class Staff : public User {
private:
    string position;
    double salary;

public:
    Staff();
    Staff(const string& id, const string& name,
          const string& phone, const string& email,
          const string& position = "Nhan vien", double salary = 0);

    string getPosition() const;
    double getSalary() const;

    void setPosition(const string& value);
    void setSalary(double value);
    void increaseSalary(double amount);

    string getType() const override;
    void displayInfo() const override;
};
