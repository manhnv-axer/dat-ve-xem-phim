#pragma once
#include <string>
#include <iostream>

using namespace std; // Khai báo dùng chung để bỏ std:: ở dưới

class Seat {
private:
    string row;      // Hàng ghế (Ví dụ: A, B, C)
    int number;      // Số ghế trong hàng (Ví dụ: 1, 2, 3)
    bool isBooked;   // Trạng thái ghế: true (đã đặt), false (còn trống)

public:
    // Hàm khởi tạo (Constructor) có tham số mặc định. 
    // Nếu tạo đối tượng mà không truyền giá trị, nó sẽ mặc định là ghế A1.
    Seat(string r = "A", int num = 1);

    // --- GETTERS (Tính đóng gói) ---
    // Từ khóa 'const' ở cuối hàm báo cho trình biên dịch biết: 
    // Hàm này chỉ đọc dữ liệu, tuyệt đối không làm thay đổi thuộc tính của class.
    string getSeatName() const; 
    bool getStatus() const;
    
    // --- NGHIỆP VỤ ---
    // Hàm thực hiện hành động đặt ghế. Trả về true nếu đặt thành công.
    bool bookSeat();
    
    // Hàm in trạng thái ghế ra màn hình
    void displaySeat() const;
};