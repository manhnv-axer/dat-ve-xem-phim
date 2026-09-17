#pragma once

#include "Ticket.h"

using namespace std;

// Ve thuong ke thua tu Ticket.
class StandardTicket : public Ticket
{
public:
    StandardTicket(
        const string& id = "",
        const string& showtime = "",
        const string& seat = "",
        double price = 0
    );

    string getType() const override;
    double getPrice() const override;

    unique_ptr<Ticket> clone() const override;

    void displayTicket() const override;
};