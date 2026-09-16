#include "Ticket.h"

Ticket::Ticket(
    string ma,
    string movie,
    string booking,
    string cinemaRoom,
    string seat,
    string showtime,
    string ten,
    double gia)
{
    maVe = ma;

    movieID = movie;
    bookingID = booking;
    cinemaRoomID = cinemaRoom;
    seatID = seat;
    showtimeID = showtime;

    tenSuKien = ten;
    giaCoBan = gia;
}

Ticket::~Ticket()
{
}

void Ticket::xuat()
{
    cout << "Ma ve: " << maVe << endl;
    cout << "Movie ID: " << movieID << endl;
    cout << "Booking ID: " << bookingID << endl;
    cout << "Cinema Room ID: " << cinemaRoomID << endl;
    cout << "Seat ID: " << seatID << endl;
    cout << "Showtime ID: " << showtimeID << endl;
    cout << "Su kien: " << tenSuKien << endl;
}