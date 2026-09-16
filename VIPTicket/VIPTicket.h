#pragma once
#include "../Ticket/Ticket.h"
class VIPTicket : public Ticket
{private:
    double phuPhi;
public:
    VIPTicket(
        string ma,
        string ten,
        string ghe,
        double gia,
        double phuPhi);
    double tinhGia() override;
    void xuat() override;
};