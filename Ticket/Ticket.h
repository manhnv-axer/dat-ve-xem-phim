#pragma once

#include <iostream>
#include <string>
using namespace std;

class Ticket
{
protected:
    string maVe;
    string tenSuKien;
    string soGhe;
    double giaCoBan;

public:
    Ticket(string ma, string ten, string ghe, double gia);

    virtual ~Ticket();

    virtual double tinhGia() = 0;

    virtual void xuat();
};    
