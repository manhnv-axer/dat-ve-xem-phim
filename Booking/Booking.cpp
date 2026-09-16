#include "Booking.h"
#include <iostream>

using namespace std;

// Khoi tao lich su
vector<Booking*> Booking::lichSuDatVe;

Booking::Booking()
{
    maBooking = "";
    tenKhachHang = "";
}

void Booking::nhapThongTin()
{
    cout << "Nhap ma booking: ";
    cin >> maBooking;

    cin.ignore();

    cout << "Nhap ten khach hang: ";
    getline(cin, tenKhachHang);

    // Them booking vao lich su
    lichSuDatVe.push_back(this);
}

void Booking::themVe(Ticket* ve)
{
    danhSachVe.push_back(ve);
}

double Booking::tinhTongTien()
{
    double tong = 0;

    for (Ticket* ve : danhSachVe)
    {
        tong += ve->tinhGia();
    }

    return tong;
}

void Booking::xuatHoaDon()
{
    cout << "\n==================================" << endl;
    cout << "          HOA DON DAT VE" << endl;
    cout << "==================================" << endl;

    cout << "Ma booking: " << maBooking << endl;
    cout << "Khach hang: " << tenKhachHang << endl;

    cout << "\nDANH SACH VE:" << endl;

    for (Ticket* ve : danhSachVe)
    {
        ve->xuat();
    }

    cout << "\n==================================" << endl;
    cout << "TONG TIEN: " << tinhTongTien() << " VND" << endl;
    cout << "==================================" << endl;
}

void Booking::hienThiLichSu()
{
    cout << "\n========================================" << endl;
    cout << "          LICH SU DAT VE" << endl;
    cout << "========================================" << endl;

    if (lichSuDatVe.empty())
    {
        cout << "Chua co lich su dat ve!" << endl;
        return;
    }

    for (int i = 0; i < lichSuDatVe.size(); i++)
    {
        cout << "\nLan dat ve: " << i + 1 << endl;

        cout << "Ma booking: "
             << lichSuDatVe[i]->maBooking << endl;

        cout << "Khach hang: "
             << lichSuDatVe[i]->tenKhachHang << endl;

        cout << "So luong ve: "
             << lichSuDatVe[i]->danhSachVe.size() << endl;

        cout << "Tong tien: "
             << lichSuDatVe[i]->tinhTongTien()
             << " VND" << endl;

        cout << "----------------------------------------" << endl;
    }
}

Booking::~Booking()
{
    for (Ticket* ve : danhSachVe)
    {
        delete ve;
    }
}