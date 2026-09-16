#pragma once

#include "../Ticket/Ticket.h"

class StandardTicket : public Ticket
{
public:
    StandardTicket(
        string ma,
        string movie,
        string booking,
        string cinemaRoom,
        string seat,
        string showtime,
        string ten,
        double gia
    );

    double tinhGia() override;

    void xuat() override;
};