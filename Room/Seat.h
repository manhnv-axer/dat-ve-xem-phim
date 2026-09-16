#pragma once
#include <string>

using namespace std;

class Seat {
private:
    string seatId; // VD: "A1", "B2"
    bool isVIP;    // true nếu là ghế VIP
    bool isBooked; // true nếu đã đặt

public:
    Seat(string id = "", bool vip = false, bool booked = false);

    string getSeatId() const;
    bool getIsVIP() const;
    bool getIsBooked() const;
    
    void setBooked(bool booked);
};