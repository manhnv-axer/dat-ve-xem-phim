#include "Ticket.h"

Ticket::Ticket(string ma, string ten, string ghe, double gia)
{
    maVe = ma;
    tenSuKien = ten;
    soGhe = ghe;
    giaCoBan = gia;
}

Ticket::~Ticket()
{
}

void Ticket::xuat()
{
    cout << "Ma ve: " << maVe << endl;
    cout << "Su kien: " << tenSuKien << endl;
    cout << "So ghe: " << soGhe << endl;
}