#pragma once

#include "../Ticket/Ticket.h"

class VIPTicket : public Ticket
{
private:
    double phuPhi;

public:
    VIPTicket(
        string ma,
        string movie,
        string booking,
        string cinemaRoom,
        string seat,
        string showtime,
        string ten,
        double gia,
        double phuPhi
    );

    double tinhGia() override;

    void xuat() override;
};