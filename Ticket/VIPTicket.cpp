#include "VIPTicket.h"

#include <iomanip>
#include <iostream>
#include <memory>

using namespace std;

VIPTicket::VIPTicket(
    const string& id,
    const string& showtime,
    const string& seat,
    double price,
    const string& perks
)
    : Ticket(id, showtime, seat, price),
      extraPerks(perks)
{
}

string VIPTicket::getType() const
{
    return "VIP";
}

double VIPTicket::getPrice() const
{
    return basePrice * 1.5;
}

unique_ptr<Ticket> VIPTicket::clone() const
{
    return make_unique<VIPTicket>(*this);
}

void VIPTicket::displayTicket() const
{
    cout << "[VIP] "
         << ticketId
         << " | Ghe: " << seatId
         << " | Gia: "
         << fixed << setprecision(0)
         << getPrice()
         << " VND"
         << " | " << extraPerks
         << '\n';
}

string VIPTicket::getExtraPerks() const
{
    return extraPerks;
}