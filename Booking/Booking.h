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

    // Lịch sử đặt vé
    static vector<Booking*> lichSuDatVe;

public:
    Booking();

    void nhapThongTin();

    void themVe(Ticket* ve);

    double tinhTongTien();

    void xuatHoaDon();

    // Hiển thị lịch sử đặt vé
    static void hienThiLichSu();

    ~Booking();
};