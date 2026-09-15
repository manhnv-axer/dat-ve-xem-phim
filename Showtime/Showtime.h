#pragma once
#include <string>
#include "../Movie/Movie.h"
#include "../Room/CinemaRoom.h"

using namespace std;

class Showtime {
private:
    string showtimeId;  // Mã lịch chiếu (VD: ST01)
    string showDate;    // Ngày chiếu (VD: 2026-09-20)
    string startTime;   // Giờ chiếu (VD: "18:00 20/10/2023")
    double basePrice;   // Giá vé cơ bản (VD: 80000)
    
    // MỐI QUAN HỆ KẾT HỢP (Aggregation): 
    // Lịch chiếu trỏ tới Phim và Phòng chứ không trực tiếp tạo ra chúng.
    // Dùng con trỏ (*) vì Phim và Phòng được quản lý ở nơi khác, lịch chiếu chỉ lấy ra dùng.
    Movie* movie; 
    CinemaRoom* room; 

public:
    // Constructor nhận vào con trỏ của Movie và CinemaRoom
    Showtime(string id, string date, string time, double price, Movie* m, CinemaRoom* r)
        : showtimeId(id), showDate(date), startTime(time), basePrice(price), movie(m), room(r) {}
        
    string getShowtimeId() const { return showtimeId; }
    string getShowDate() const { return showDate; }
    string getStartTime() const { return startTime; } // Đã sửa 'StartTime' thành 'startTime'
    double getBasePrice() const { return basePrice; }
    
    // In thông tin tổng hợp của 1 lịch chiếu
    void displayShowtimeInfo() const;
};