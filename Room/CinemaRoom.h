#pragma once
#include <string>
#include <vector> // Thư viện STL để dùng mảng động vector
#include "Seat.h"

using namespace std;

class CinemaRoom {
private:
    string roomId;      // Tên/Mã phòng (VD: Room1, P01)
    int totalRows;      // Tổng số hàng ghế
    int seatsPerRow;    // Số ghế trên mỗi hàng
    
    // MỐI QUAN HỆ HỢP THÀNH (Composition): Phòng chiếu chứa và quản lý trực tiếp các Ghế.
    // Dùng vector để lưu danh sách đối tượng Seat.
    vector<Seat> seats; 

    // Hàm private: Chỉ dùng nội bộ trong class này để tự động tạo ghế khi khởi tạo phòng
    void initializeSeats(); 

public:
    // Khởi tạo phòng chiếu cần biết tên phòng, số hàng và số ghế/hàng
    CinemaRoom(string id, int rows, int seatsPR);

    string getRoomId() const;
    
    // In sơ đồ ghế ngồi của cả phòng ra màn hình
    void displayRoomMap() const;
};