#pragma once

#include <string>

using namespace std;

class Showtime {
private:
    string showtimeId;
    string movieId;
    string roomId;
    string showDate;
    string startTime;
    double basePrice;
    string status;

public:
    Showtime(const string& id = "", const string& movieId = "",
             const string& roomId = "", const string& date = "",
             const string& time = "", double price = 0,
             const string& status = "Dang chieu");

    string getShowtimeId() const;
    string getMovieId() const;
    string getRoomId() const;
    string getShowDate() const;
    string getStartTime() const;
    double getBasePrice() const;
    string getStatus() const;

    void setMovieId(const string& value);
    void setRoomId(const string& value);
    void setShowDate(const string& value);
    void setStartTime(const string& value);
    void setBasePrice(double value);
    void setStatus(const string& value);

    void displayShowtime() const;
};
