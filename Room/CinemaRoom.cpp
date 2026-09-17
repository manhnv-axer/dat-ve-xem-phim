#include "CinemaRoom.h"

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>

using namespace std;

CinemaRoom::CinemaRoom(const string& id, const string& name, int rows, int cols)
    : roomId(id), roomName(name), rowCount(max(1, rows)), colCount(max(1, cols)) {
    buildSeats();
}

void CinemaRoom::buildSeats() {
    seats.clear();
    for (int row = 0; row < rowCount; ++row) {
        char rowName = static_cast<char>('A' + row);
        for (int col = 0; col < colCount; ++col) {
            seats.emplace_back(string(1, rowName) + to_string(col), false, false);
        }
    }
}

string CinemaRoom::getRoomId() const { return roomId; }
string CinemaRoom::getRoomName() const { return roomName; }
int CinemaRoom::getRowCount() const { return rowCount; }
int CinemaRoom::getColCount() const { return colCount; }
const vector<Seat>& CinemaRoom::getSeats() const { return seats; }
vector<Seat>& CinemaRoom::getSeats() { return seats; }

Seat* CinemaRoom::getSeatById(const string& seatId) {
    for (Seat& seat : seats) {
        if (seat.getSeatId() == seatId) {
            return &seat;
        }
    }
    return nullptr;
}

const Seat* CinemaRoom::getSeatById(const string& seatId) const {
    for (const Seat& seat : seats) {
        if (seat.getSeatId() == seatId) {
            return &seat;
        }
    }
    return nullptr;
}

void CinemaRoom::setName(const string& value) { roomName = value; }

void CinemaRoom::setDimensions(int rows, int cols) {
    if (rows < 1 || cols < 1) {
        return;
    }

    vector<Seat> oldSeats = seats;
    const int oldRows = rowCount;
    const int oldCols = colCount;

    rowCount = rows;
    colCount = cols;
    buildSeats();

    // Khi thay doi kich thuoc, giu lai VIP/Bao tri cua cac ghe van con ton tai.
    for (int row = 0; row < min(oldRows, rowCount); ++row) {
        for (int col = 0; col < min(oldCols, colCount); ++col) {
            const size_t oldIndex = static_cast<size_t>(row * oldCols + col);
            const size_t newIndex = static_cast<size_t>(row * colCount + col);
            seats[newIndex].setVIP(oldSeats[oldIndex].isVIP());
            seats[newIndex].setMaintenance(oldSeats[oldIndex].isMaintenance());
        }
    }
}

void CinemaRoom::setVIP(const string& seatId, bool value) {
    Seat* seat = getSeatById(seatId);
    if (seat != nullptr) {
        seat->setVIP(value);
    }
}

void CinemaRoom::setMaintenance(const string& seatId, bool value) {
    Seat* seat = getSeatById(seatId);
    if (seat != nullptr) {
        seat->setMaintenance(value);
    }
}

void CinemaRoom::displaySeatLayout(const vector<string>& bookedSeats) const {
    cout << "\nPhong " << roomId << " - " << roomName
         << " (" << rowCount << " x " << colCount << ")\n";
    cout << "                  MAN HINH\n\n";

    cout << "     ";
    for (int col = 0; col < colCount; ++col) {
        cout << setw(4) << col;
    }
    cout << '\n';

    auto isBooked = [&](const string& id) {
        return find(bookedSeats.begin(), bookedSeats.end(), id) != bookedSeats.end();
    };

    for (int row = 0; row < rowCount; ++row) {
        char rowName = static_cast<char>('A' + row);
        cout << ' ' << rowName << "   ";
        for (int col = 0; col < colCount; ++col) {
            const Seat& seat = seats[row * colCount + col];
            string symbol = "[ ]";
            if (seat.isMaintenance()) {
                symbol = "[M]";
            } else if (isBooked(seat.getSeatId())) {
                symbol = "[X]";
            } else if (seat.isVIP()) {
                symbol = "[V]";
            }
            cout << setw(4) << symbol;
        }
        cout << '\n';
    }

    cout << "\n[ ] Trong | [V] VIP | [X] Da dat | [M] Bao tri\n";
}
