#include "AccountManager.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

using namespace std;

AccountManager::AccountManager(const string& file) : Manager<Account>(file) {
    load();
}

string AccountManager::trim(const string& value) {
    const size_t first = value.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }
    const size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

vector<string> AccountManager::split(const string& line) {
    vector<string> fields;
    string field;
    stringstream stream(line);
    while (getline(stream, field, '|')) {
        fields.push_back(trim(field));
    }
    return fields;
}

string AccountManager::lower(string value) {
    transform(value.begin(), value.end(), value.begin(),
              [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return value;
}

string AccountManager::normalizeRole(const string& value) {
    const string role = lower(trim(value));
    if (role == "admin" || role == "manager" || role == "quanly") {
        return "Manager";
    }
    if (role == "staff" || role == "nhanvien") {
        return "Staff";
    }
    return "Customer";
}

void AccountManager::ensureDefaultManager() {
    for (const Account& account : items) {
        if (isManager(account)) {
            return;
        }
    }

    items.push_back({"U01", "admin", "admin123", "Manager",
                     "Administrator", "0900000000", "admin@cinema.local", true});
    save();
}

bool AccountManager::load() {
    items.clear();
    ifstream input(fileName);

    if (!input) {
        ensureDefaultManager();
        return true;
    }

    string line;
    while (getline(input, line)) {
        if (trim(line).empty() || trim(line)[0] == '#') {
            continue;
        }

        vector<string> fields = split(line);
        if (fields.size() < 6 || fields[0] == "ID") {
            continue;
        }

        Account account;
        account.id = fields[0];
        account.username = fields[1];
        account.password = fields[2];
        account.role = normalizeRole(fields[3]);
        account.fullName = fields[4];
        account.phone = fields[5];
        account.email = fields.size() >= 7 ? fields[6] : "";
        account.active = true;

        if (fields.size() >= 8) {
            account.active = lower(fields[7]) != "locked";
        }

        items.push_back(account);
    }

    ensureDefaultManager();
    save();
    return true;
}

bool AccountManager::save() const {
    ofstream output(fileName);
    if (!output) {
        return false;
    }

    output << "ID|Username|Password|Role|FullName|Phone|Email|Status\n";
    for (const Account& account : items) {
        output << account.id << '|'
               << account.username << '|'
               << account.password << '|'
               << account.role << '|'
               << account.fullName << '|'
               << account.phone << '|'
               << account.email << '|'
               << (account.active ? "Active" : "Locked") << '\n';
    }
    return true;
}

const Account* AccountManager::findById(const string& id) const {
    for (const Account& account : items) {
        if (account.id == id) {
            return &account;
        }
    }
    return nullptr;
}

Role AccountManager::getRole(const Account& account) {
    if (account.role == "Manager" || account.role == "Admin") {
        return Role::Manager;
    }
    if (account.role == "Staff") {
        return Role::Staff;
    }
    return Role::Customer;
}

bool AccountManager::isManager(const Account& account) {
    return getRole(account) == Role::Manager;
}

bool AccountManager::isStaff(const Account& account) {
    return getRole(account) == Role::Staff;
}

bool AccountManager::isCustomer(const Account& account) {
    return getRole(account) == Role::Customer;
}

const Account* AccountManager::authenticate(const string& username,
                                             const string& password) const {
    for (const Account& account : items) {
        if (account.username == username && account.password == password) {
            return &account;
        }
    }
    return nullptr;
}

bool AccountManager::registerCustomer(const string& username,
                                      const string& password,
                                      const string& fullName,
                                      const string& phone,
                                      const string& email,
                                      string& errorMessage) {
    if (username.empty() || password.empty() || fullName.empty() || phone.empty()) {
        errorMessage = "Thong tin bat buoc khong duoc de trong.";
        return false;
    }

    for (const Account& account : items) {
        if (account.username == username) {
            errorMessage = "Username da ton tai.";
            return false;
        }
    }

    int maxNumber = 0;
    for (const Account& account : items) {
        if (account.id.size() > 1 && account.id[0] == 'C') {
            try {
                maxNumber = max(maxNumber, stoi(account.id.substr(1)));
            } catch (...) {
            }
        }
    }

    items.push_back({"C" + to_string(maxNumber + 1), username, password,
                     "Customer", fullName, phone, email, true});

    if (!save()) {
        items.pop_back();
        errorMessage = "Khong ghi duoc data/users.txt.";
        return false;
    }
    return true;
}

bool AccountManager::createStaff(const string& username,
                                  const string& password,
                                  const string& fullName,
                                  const string& phone,
                                  const string& email,
                                  string& errorMessage) {
    if (username.empty() || password.empty() || fullName.empty() || phone.empty()) {
        errorMessage = "Thong tin Staff khong duoc de trong.";
        return false;
    }

    for (const Account& account : items) {
        if (account.username == username) {
            errorMessage = "Username da ton tai.";
            return false;
        }
    }

    int maxNumber = 0;
    for (const Account& account : items) {
        if (account.id.size() > 1 && account.id[0] == 'S') {
            try {
                maxNumber = max(maxNumber, stoi(account.id.substr(1)));
            } catch (...) {
            }
        }
    }

    items.push_back({"S" + to_string(maxNumber + 1), username, password,
                     "Staff", fullName, phone, email, true});

    if (!save()) {
        items.pop_back();
        errorMessage = "Khong ghi duoc data/users.txt.";
        return false;
    }
    return true;
}

bool AccountManager::setStaffStatus(const string& staffId, bool active,
                                    string& errorMessage) {
    for (Account& account : items) {
        if (account.id == staffId) {
            if (!isStaff(account)) {
                errorMessage = "Chi duoc khoa/mo khoa tai khoan Staff.";
                return false;
            }
            account.active = active;
            if (!save()) {
                errorMessage = "Khong ghi duoc data/users.txt.";
                return false;
            }
            return true;
        }
    }

    errorMessage = "Khong tim thay Staff.";
    return false;
}

vector<Account> AccountManager::getStaff() const {
    return filter([](const Account& account) {
        return isStaff(account);
    });
}

vector<Account> AccountManager::searchCustomers(const string& keyword) const {
    const string key = lower(trim(keyword));
    return filter([&](const Account& account) {
        if (!isCustomer(account)) {
            return false;
        }
        if (key.empty()) {
            return true;
        }
        return lower(account.id).find(key) != string::npos ||
               lower(account.username).find(key) != string::npos ||
               lower(account.fullName).find(key) != string::npos ||
               lower(account.phone).find(key) != string::npos;
    });
}

vector<Account> AccountManager::getCustomers() const {
    return filter([](const Account& account) {
        return isCustomer(account);
    });
}

bool AccountManager::updateCustomer(const string& id, const string& name,
                                     const string& phone, const string& email,
                                     string& errorMessage) {
    for (Account& account : items) {
        if (account.id == id) {
            if (!isCustomer(account)) {
                errorMessage = "Tai khoan khong phai Customer.";
                return false;
            }
            account.fullName = name;
            account.phone = phone;
            account.email = email;
            return save();
        }
    }
    errorMessage = "Khong tim thay Customer.";
    return false;
}

bool AccountManager::deleteCustomer(const string& id, string& errorMessage) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->id == id) {
            if (!isCustomer(*it)) {
                errorMessage = "Chi duoc xoa Customer.";
                return false;
            }
            items.erase(it);
            return save();
        }
    }
    errorMessage = "Khong tim thay Customer.";
    return false;
}

Staff AccountManager::toStaff(const Account& account) const {
    return Staff(account.id, account.fullName, account.phone, account.email,
                 "Nhan vien ban ve", 0);
}

Customer AccountManager::toCustomer(const Account& account) const {
    return Customer(account.id, account.fullName, account.phone, account.email, 0);
}
