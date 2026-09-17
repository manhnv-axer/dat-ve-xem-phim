#include "Staff.h"

#include <iostream>

using namespace std;

Staff::Staff() : User(), position("Nhan vien"), salary(0) {}

Staff::Staff(const string& idValue, const string& nameValue,
             const string& phoneValue, const string& emailValue,
             const string& positionValue, double salaryValue)
    : User(idValue, nameValue, phoneValue, emailValue),
      position(positionValue), salary(salaryValue < 0 ? 0 : salaryValue) {}

string Staff::getPosition() const { return position; }
double Staff::getSalary() const { return salary; }

void Staff::setPosition(const string& value) { position = value; }
void Staff::setSalary(double value) { salary = value < 0 ? 0 : value; }
void Staff::increaseSalary(double amount) {
    if (amount > 0) {
        salary += amount;
    }
}

string Staff::getType() const { return "Staff"; }

void Staff::displayInfo() const {
    cout << "ID: " << id
         << " | Ho ten: " << name
         << " | SDT: " << phone
         << " | Chuc vu: " << position
         << " | Luong: " << salary << '\n';
}
