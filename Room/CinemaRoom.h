#pragma once

#include "Seat.h"

#include <string>
#include <vector>

using namespace std;

class CinemaRoom {
private:
    string roomId;
    string roomName;
    int rowCount;
    int colCount;
    vector<Seat> seats;

    void buildSeats();

public:
    CinemaRoom(const string& id = "", const string& name = "",
                int rows = 1, int cols = 1);

    string getRoomId() const;
    string getRoomName() const;
    int getRowCount() const;
    int getColCount() const;
    const vector<Seat>& getSeats() const;
    vector<Seat>& getSeats();

    Seat* getSeatById(const string& seatId);
    const Seat* getSeatById(const string& seatId) const;

    void setName(const string& value);
    void setDimensions(int rows, int cols);
    void setVIP(const string& seatId, bool value);
    void setMaintenance(const string& seatId, bool value);
    void displaySeatLayout(const vector<string>& bookedSeats = {}) const;
};
