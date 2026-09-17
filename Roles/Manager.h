#pragma once

#include "../Staff/Staff.h"

using namespace std;

namespace Roles {

// Manager nghiep vu la lop con cua Staff.
// Quyen quan ly duoc thuc thi tai lop service/menu, Staff khong co API quan ly Staff.
class Manager : public Staff {
public:
    Manager();
    Manager(const string& id, const string& name,
            const string& phone, const string& email = "");

    string getType() const override;
    void displayInfo() const override;

    bool canManageStaff() const;
    bool canManageMovies() const;
    bool canManageShowtimes() const;
};

} // namespace Roles
