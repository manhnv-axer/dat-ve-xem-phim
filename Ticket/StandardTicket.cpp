#include "StandardTicket.h"

#include <iomanip>
#include <iostream>
#include <memory>

using namespace std;

StandardTicket::StandardTicket(
    const string& id,
    const string& showtime,
    const string& seat,
    double price
)
    : Ticket(id, showtime, seat, price)
{
}

string StandardTicket::getType() const
{
    return "Standard";
}

double StandardTicket::getPrice() const
{
    return basePrice;
}

unique_ptr<Ticket> StandardTicket::clone() const
{
    return make_unique<StandardTicket>(*this);
}

void StandardTicket::displayTicket() const
{
    cout << "[STANDARD] "
         << ticketId
         << " | Ghe: " << seatId
         << " | Gia: "
         << fixed << setprecision(0)
         << getPrice()
         << " VND\n";
}