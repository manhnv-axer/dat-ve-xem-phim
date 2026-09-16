#include "Showtime.h"

Showtime::Showtime(string sId, string mId, string rId, string date, string time, double price)
    : showtimeId(sId), movieId(mId), roomId(rId), showDate(date), startTime(time), basePrice(price) {}

string Showtime::getShowtimeId() const { return showtimeId; }
string Showtime::getMovieId() const { return movieId; }
string Showtime::getRoomId() const { return roomId; }
string Showtime::getShowDate() const { return showDate; }
string Showtime::getStartTime() const { return startTime; }
double Showtime::getBasePrice() const { return basePrice; }

void Showtime::displayShowtime() const {
    cout << "Ma suat: " << showtimeId << " | Ngay: " << showDate 
         << " | Gio: " << startTime << " | Phong: " << roomId 
         << " | Gia ve co ban: " << basePrice << " VND" << endl;
}