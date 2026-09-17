#pragma once

#include "Ticket.h"

using namespace std;

// Ve VIP ke thua tu Ticket.
class VIPTicket : public Ticket
{
private:
    string extraPerks;

public:
    VIPTicket(
        const string& id = "",
        const string& showtime = "",
        const string& seat = "",
        double price = 0,
        const string& perks = "Uu tien cho ngoi + combo"
    );

    string getType() const override;
    double getPrice() const override;

    unique_ptr<Ticket> clone() const override;

    void displayTicket() const override;

    string getExtraPerks() const;
};