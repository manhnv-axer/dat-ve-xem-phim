#include "CinemaRoom.h"
#include <iostream>

// Khi khởi tạo phòng chiếu, ta gọi luôn hàm initializeSeats() để tự động lấp đầy ghế
CinemaRoom::CinemaRoom(string id, int rows, int seatsPR) 
    : roomId(id), totalRows(rows), seatsPerRow(seatsPR) {
    initializeSeats();
}

// Thuật toán sinh tên ghế tự động (A1, A2... B1, B2...)
void CinemaRoom::initializeSeats() {
    for (int i = 0; i < totalRows; ++i) {
        // Dùng mã ASCII để đổi số thành chữ cái. 
        // i = 0 -> 'A' + 0 = 'A'. i = 1 -> 'A' + 1 = 'B'
        string rowName(1, 'A' + i); 
        
        for (int j = 1; j <= seatsPerRow; ++j) {
            // Tạo đối tượng Seat mới và đẩy vào mảng vector
            seats.push_back(Seat(rowName, j)); 
        }
    }
}

string CinemaRoom::getRoomId() const { return roomId; }

// Vòng lặp in sơ đồ phòng chiếu
void CinemaRoom::displayRoomMap() const {
    cout << "--- So do phong chieu " << roomId << " ---" << endl;
    int count = 0;
    // Dùng vòng lặp for-each (C++11 trở lên) duyệt qua mảng ghế
    // 'const auto&' giúp duyệt nhanh mà không cần copy dữ liệu (tiết kiệm bộ nhớ)
    for (const auto& seat : seats) {
        seat.displaySeat();
        count++;
        // Xuống dòng khi in đủ số ghế của một hàng
        if (count % seatsPerRow == 0) cout << endl;
    }
}