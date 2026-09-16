#include "../StandardTicket/StandardTicket.h"
StandardTicket::StandardTicket(
    string ma,
    string ten,
    string ghe,
    double gia)
    : Ticket(ma, ten, ghe, gia)
{}
double StandardTicket::tinhGia()
{return giaCoBan;}
void StandardTicket::xuat()
{cout << "\n===== VE THUONG =====" << endl;
Ticket::xuat();
cout << "Gia ve: " << tinhGia() << endl;
}