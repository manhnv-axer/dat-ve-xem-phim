#include <iostream>
#include "Booking/Booking.h"
#include "StandardTicket/StandardTicket.h"
#include "VIPTicket/VIPTicket.h"
using namespace std;
int main()
{Booking booking;
cout << "===== NHAP THONG TIN DAT VE =====" << endl;
    booking.nhapThongTin();
    Ticket* ve1 = new StandardTicket(
        "V001",
        "CONCERT A",
        "A01",
        100000
    );
    Ticket* ve2 = new VIPTicket(
        "V002",
        "CONCERT A",
        "VIP01",
        100000,
        50000
    );
    booking.themVe(ve1);
    booking.themVe(ve2);
    booking.xuatHoaDon();
    return 0;
}