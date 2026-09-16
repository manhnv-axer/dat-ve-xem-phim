#include "CinemaRoom.h"
#include <iostream>
#include <iomanip> // Thư viện để căn lề setw()

CinemaRoom::CinemaRoom(string id, string name) : roomId(id), roomName(name) {
    char rows[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}; // 8 hàng
    for (int i = 0; i < 8; i++) {
        for (int j = 1; j <= 12; j++) { // 12 cột
            string seatId = string(1, rows[i]) + to_string(j); // Gộp chữ và số (VD: A1)
            
            // Thiết lập dải ghế VIP nằm ở hàng D, E, F (từ cột 3 đến 10)
            bool isVip = (i >= 3 && i <= 5 && j >= 3 && j <= 10);
            
            seats.push_back(Seat(seatId, isVip, false));
        }
    }
}

string CinemaRoom::getRoomId() const { return roomId; }
string CinemaRoom::getRoomName() const { return roomName; }
vector<Seat>& CinemaRoom::getSeats() { return seats; }

Seat* CinemaRoom::getSeatById(string seatId) {
    for (auto& seat : seats) {
        if (seat.getSeatId() == seatId) return &seat;
    }
    return nullptr;
}

void CinemaRoom::displayRoomMap() const {
    cout << "\n=======================================================" << endl;
    cout << "                [[ MAN HINH CHIEU ]]                   " << endl;
    cout << "=======================================================\n" << endl;
    
    // In thanh ngang số cột (1 đến 12) căn đều khoảng trắng
    cout << "      ";
    for (int j = 1; j <= 12; j++) {
        cout << setw(3) << j << " ";
    }
    cout << endl;

    int index = 0;
    char rows[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    for (int i = 0; i < 8; i++) {
        cout << " " << rows[i] << "  "; // In tên hàng và khoảng cách cố định
        for (int j = 1; j <= 12; j++) {
            if (seats[index].getIsBooked()) {
                cout << "[X] ";
            } else if (seats[index].getIsVIP()) {
                cout << "[V] ";
            } else {
                cout << "[ ] ";
            }
            index++;
        }
        cout << endl;
    }
    
    cout << "\n-------------------------------------------------------" << endl;
    cout << "  Chu thich: [ ] Trong (Thuong) | [V] VIP | [X] Da Dat   " << endl;
    cout << "-------------------------------------------------------" << endl;
}