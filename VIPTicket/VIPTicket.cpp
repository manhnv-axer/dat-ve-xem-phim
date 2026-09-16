#include "VIPTicket.h"

VIPTicket::VIPTicket(
    string ma,
    string ten,
    string ghe,
    double gia,
    double phuPhi)
    : Ticket(ma, ten, ghe, gia)
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