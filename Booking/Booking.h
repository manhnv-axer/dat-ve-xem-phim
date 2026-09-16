#pragma once

#include "../Ticket/Ticket.h"
#include <vector>
#include <string>

using namespace std;

class Booking
{
private:
    string maBooking;
    string tenKhachHang;

    vector<Ticket*> danhSachVe;

    // Lich su dat ve
    static vector<Booking*> lichSuDatVe;

public:
    Booking();

    void nhapThongTin();

    void themVe(Ticket* ve);

    double tinhTongTien();

    void xuatHoaDon();

    static void hienThiLichSu();

    ~Booking();
};