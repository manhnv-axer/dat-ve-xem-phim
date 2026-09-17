#pragma once

#include "../Manager.h"
#include "../Customer/Customer.h"
#include "../Staff/Staff.h"

#include <string>
#include <vector>

using namespace std;

enum class Role {
    Manager,
    Staff,
    Customer
};

struct Account {
    string id;
    string username;
    string password;
    string role;
    string fullName;
    string phone;
    string email;
    bool active;
};

class AccountManager : public Manager<Account> {
private:
    static string trim(const string& value);
    static vector<string> split(const string& line);
    static string normalizeRole(const string& value);
    static string lower(string value);
    void ensureDefaultManager();

public:
    explicit AccountManager(const string& file = "data/users.txt");

    bool load() override;
    bool save() const override;
    const Account* findById(const string& id) const override;

    static Role getRole(const Account& account);
    static bool isManager(const Account& account);
    static bool isStaff(const Account& account);
    static bool isCustomer(const Account& account);
    static bool validUsername(const string& value);
    static bool validPassword(const string& value);
    static bool validPhone(const string& value);
    static bool validEmail(const string& value);
    bool usernameExists(const string& username) const;

    const Account* authenticate(const string& username, const string& password) const;

    bool registerCustomer(const string& username, const string& password,
                          const string& fullName, const string& phone,
                          const string& email, string& errorMessage);

    bool createStaff(const string& username, const string& password,
                     const string& fullName, const string& phone,
                     const string& email, string& errorMessage);

    bool setStaffStatus(const string& staffId, bool active, string& errorMessage);
    vector<Account> getStaff() const;
    vector<Account> searchCustomers(const string& keyword) const;
    vector<Account> getCustomers() const;
    bool updateCustomer(const string& id, const string& name,
                        const string& phone, const string& email,
                        string& errorMessage);
    bool deleteCustomer(const string& id, string& errorMessage);

    // Chi chuyen Account thanh doi tuong OOP phu hop voi role.
    Staff toStaff(const Account& account) const;
    Customer toCustomer(const Account& account) const;
};
