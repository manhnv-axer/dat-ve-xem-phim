#pragma once

#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Lop co so truu tuong cho cac loai ve.
// Day la abstract class thu hai cua he thong.
class Ticket
{
protected:
    string ticketId;
    string showtimeId;
    string seatId;
    double basePrice;

public:
    Ticket(
        const string& id = "",
        const string& showtime = "",
        const string& seat = "",
        double price = 0
    );

    virtual ~Ticket() = default;

    string getTicketId() const;
    string getShowtimeId() const;
    string getSeatId() const;
    double getBasePrice() const;

    // Cac ham ao thuan tuy bat buoc lop con phai cai dat.
    virtual string getType() const = 0;
    virtual double getPrice() const = 0;
    virtual unique_ptr<Ticket> clone() const = 0;
    virtual void displayTicket() const = 0;
};