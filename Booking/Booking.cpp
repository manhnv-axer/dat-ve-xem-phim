#include "Booking.h"
Booking::Booking()
{maBooking = "";
tenKhachHang = "";}
void Booking::nhapThongTin()
{cout << "Nhap ma booking: ";
cin >> maBooking;
cin.ignore();
cout << "Nhap ten khach hang: ";
getline(cin, tenKhachHang);}
void Booking::themVe(Ticket* ve)
{danhSachVe.push_back(ve);}
double Booking::tinhTongTien()
{double tong = 0;
for (Ticket* ve : danhSachVe)
    {tong += ve->tinhGia();}
return tong;}
void Booking::xuatHoaDon()
{   cout << "\n==================================" << endl;
    cout << "          HOA DON DAT VE" << endl;
    cout << "==================================" << endl;
    cout << "Ma booking: " << maBooking << endl;
    cout << "Khach hang: " << tenKhachHang << endl;
    cout << "\nDANH SACH VE:" << endl;
    for (Ticket* ve : danhSachVe)
    { ve->xuat(); }
    cout << "\n==================================" << endl;
    cout << "TONG TIEN: " << tinhTongTien() << " VND" << endl;
    cout << "==================================" << endl;}
Booking::~Booking()
{for (Ticket* ve : danhSachVe)
    {delete ve; }
}