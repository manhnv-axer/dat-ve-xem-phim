#include "Manager.h"

#include <iostream>

using namespace std;

Roles::Manager::Manager() : Staff() {
    setPosition("Quan ly");
}

Roles::Manager::Manager(const string& idValue, const string& nameValue,
                 const string& phoneValue, const string& emailValue)
    : Staff(idValue, nameValue, phoneValue, emailValue, "Quan ly", 0) {}

string Roles::Manager::getType() const { return "Manager"; }

void Roles::Manager::displayInfo() const {
    cout << "[MANAGER] ";
    Staff::displayInfo();
}

bool Roles::Manager::canManageStaff() const { return true; }
bool Roles::Manager::canManageMovies() const { return true; }
bool Roles::Manager::canManageShowtimes() const { return true; }
