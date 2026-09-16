#include <iostream>

#include "Booking/Booking.h"
#include "StandardTicket/StandardTicket.h"
#include "VIPTicket/VIPTicket.h"

using namespace std;

int main()
{
    Booking booking;

    cout << "===== NHAP THONG TIN DAT VE =====" << endl;

    booking.nhapThongTin();

    // =========================
    // VE THUONG
    // =========================

    Ticket* ve1 = new StandardTicket(
        "V001",        // Ma ve
        "M001",        // MovieID
        "B001",        // BookingID
        "R001",        // CinemaRoomID
        "A01",         // SeatID
        "ST001",       // ShowtimeID
        "CONCERT A",   // Ten su kien
        100000         // Gia
    );

    // =========================
    // VE VIP
    // =========================

    Ticket* ve2 = new VIPTicket(
        "V002",        // Ma ve
        "M001",        // MovieID
        "B001",        // BookingID
        "R001",        // CinemaRoomID
        "VIP01",       // SeatID
        "ST001",       // ShowtimeID
        "CONCERT A",   // Ten su kien
        100000,        // Gia
        50000          // Phu phi VIP
    );

    // Them ve vao booking
    booking.themVe(ve1);
    booking.themVe(ve2);

    // Xuat hoa don
    booking.xuatHoaDon();

    // Hien thi lich su dat ve
    Booking::hienThiLichSu();

    return 0;
}