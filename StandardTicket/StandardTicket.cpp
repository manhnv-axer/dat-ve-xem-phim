#include "StandardTicket.h"

StandardTicket::StandardTicket(
    string ma,
    string movie,
    string booking,
    string cinemaRoom,
    string seat,
    string showtime,
    string ten,
    double gia)
    : Ticket(
        ma,
        movie,
        booking,
        cinemaRoom,
        seat,
        showtime,
        ten,
        gia)
{
}

double StandardTicket::tinhGia()
{
    return giaCoBan;
}

void StandardTicket::xuat()
{
    cout << "\n===== VE THUONG =====" << endl;

    Ticket::xuat();

    cout << "Gia co ban: " << giaCoBan << endl;
    cout << "Gia ve: " << tinhGia() << endl;
}