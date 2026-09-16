#include "VIPTicket.h"

VIPTicket::VIPTicket(
    string ma,
    string movie,
    string booking,
    string cinemaRoom,
    string seat,
    string showtime,
    string ten,
    double gia,
    double phuPhi)
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
    this->phuPhi = phuPhi;
}

double VIPTicket::tinhGia()
{
    return giaCoBan + phuPhi;
}

void VIPTicket::xuat()
{
    cout << "\n===== VE VIP =====" << endl;

    Ticket::xuat();

    cout << "Gia co ban: " << giaCoBan << endl;
    cout << "Phu phi VIP: " << phuPhi << endl;
    cout << "Gia ve: " << tinhGia() << endl;
}