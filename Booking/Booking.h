#pragma once
#include "../Ticket/Ticket.h"
#include <vector>
class Booking
{private:
    string maBooking;
    string tenKhachHang;
    vector<Ticket*> danhSachVe;
public:
    Booking(string ma, string ten);
    void themVe(Ticket* ve);
    double tinhTongTien();
    void xuatHoaDon();
    ~Booking();
};