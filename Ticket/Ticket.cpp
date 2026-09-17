#include "Ticket.h"

using namespace std;

Ticket::Ticket(
    const string& id,
    const string& showtime,
    const string& seat,
    double price
)
    : ticketId(id),
      showtimeId(showtime),
      seatId(seat),
      basePrice(price)
{
}

string Ticket::getTicketId() const
{
    return ticketId;
}

string Ticket::getShowtimeId() const
{
    return showtimeId;
}

string Ticket::getSeatId() const
{
    return seatId;
}

double Ticket::getBasePrice() const
{
    return basePrice;
}