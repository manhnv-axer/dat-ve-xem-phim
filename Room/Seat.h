#pragma once

#include <string>

using namespace std;

class Seat {
private:
    string seatId;
    bool vip;
    bool maintenance;

public:
    Seat(const string& id = "", bool isVip = false, bool isMaintenance = false);

    string getSeatId() const;
    bool isVIP() const;
    bool isMaintenance() const;

    void setVIP(bool value);
    void setMaintenance(bool value);

    // Qua tai tu de so sanh hai ghe theo ma ghe.
    bool operator==(const Seat& other) const;
};
