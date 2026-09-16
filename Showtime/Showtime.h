#pragma once
#include <string>
#include <iostream>

using namespace std;

class Showtime {
private:
    string showtimeId;
    string movieId;  
    string roomId;   
    string showDate;
    string startTime;
    double basePrice;

public:
    Showtime(string sId = "", string mId = "", string rId = "", string date = "", string time = "", double price = 0);

    string getShowtimeId() const;
    string getMovieId() const;
    string getRoomId() const;
    string getShowDate() const;
    string getStartTime() const;
    double getBasePrice() const;

    void displayShowtime() const;
};