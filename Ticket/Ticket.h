#pragma once

#include <iostream>
#include <string>
using namespace std;

class Ticket
{
protected:
    string maVe;

    // Thong tin ID
    string movieID;
    string bookingID;
    string cinemaRoomID;
    string seatID;
    string showtimeID;

    string tenSuKien;
    double giaCoBan;

public:
    Ticket(
        string ma,
        string movie,
        string booking,
        string cinemaRoom,
        string seat,
        string showtime,
        string ten,
        double gia
    );

    virtual ~Ticket();

    virtual double tinhGia() = 0;

    virtual void xuat();
};