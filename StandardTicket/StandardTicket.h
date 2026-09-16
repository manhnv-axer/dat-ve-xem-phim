#pragma once

#include "../Ticket/Ticket.h"

class StandardTicket : public Ticket
{
public:
    StandardTicket(string ma, string ten, string ghe, double gia);

    double tinhGia() override;

    void xuat() override;
};