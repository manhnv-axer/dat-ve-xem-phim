#include "Customer.h"

#include <iostream>

using namespace std;

Customer::Customer() : User(), loyaltyPoints(0) {}

Customer::Customer(const string& idValue, const string& nameValue,
                   const string& phoneValue, const string& emailValue,
                   int points)
    : User(idValue, nameValue, phoneValue, emailValue),
      loyaltyPoints(points < 0 ? 0 : points) {}

int Customer::getLoyaltyPoints() const { return loyaltyPoints; }
void Customer::setLoyaltyPoints(int points) {
    loyaltyPoints = points < 0 ? 0 : points;
}

void Customer::addPoints(int points) {
    if (points > 0) {
        loyaltyPoints += points;
    }
}

string Customer::getType() const { return "Customer"; }

void Customer::displayInfo() const {
    cout << "ID: " << id
         << " | Ho ten: " << name
         << " | SDT: " << phone
         << " | Email: " << email
         << " | Diem: " << loyaltyPoints << '\n';
}
