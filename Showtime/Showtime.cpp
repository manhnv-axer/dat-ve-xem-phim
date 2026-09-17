#include "Showtime.h"

#include <iomanip>
#include <iostream>

using namespace std;

Showtime::Showtime(const string& id, const string& movieIdValue,
                   const string& roomIdValue, const string& date,
                   const string& time, double price, const string& statusValue)
    : showtimeId(id), movieId(movieIdValue), roomId(roomIdValue),
      showDate(date), startTime(time), basePrice(price), status(statusValue) {}

string Showtime::getShowtimeId() const { return showtimeId; }
string Showtime::getMovieId() const { return movieId; }
string Showtime::getRoomId() const { return roomId; }
string Showtime::getShowDate() const { return showDate; }
string Showtime::getStartTime() const { return startTime; }
double Showtime::getBasePrice() const { return basePrice; }
string Showtime::getStatus() const { return status; }

void Showtime::setMovieId(const string& value) { movieId = value; }
void Showtime::setRoomId(const string& value) { roomId = value; }
void Showtime::setShowDate(const string& value) { showDate = value; }
void Showtime::setStartTime(const string& value) { startTime = value; }
void Showtime::setBasePrice(double value) { basePrice = value; }
void Showtime::setStatus(const string& value) { status = value; }

void Showtime::displayShowtime() const {
    cout << showtimeId << " | Phim: " << movieId
         << " | Phong: " << roomId
         << " | " << showDate << ' ' << startTime
         << " | " << fixed << setprecision(0) << basePrice << " VND"
         << " | " << status << '\n';
}
