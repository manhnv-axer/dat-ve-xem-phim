#include "Seat.h"

// Sử dụng Danh sách khởi tạo (Initializer list) ':' để gán giá trị nhanh cho thuộc tính
// isBooked luôn khởi tạo là false (ghế mới tạo mặc định là trống)
Seat::Seat(string r, int num) : row(r), number(num), isBooked(false) {}

// Hàm ghép hàng và số lại thành tên ghế (Ví dụ: Hàng "A" + số 1 => "A1")
// Sử dụng to_string để ép kiểu số nguyên (int) sang chuỗi (string)
string Seat::getSeatName() const {
    return row + to_string(number);
}

// Trả về trạng thái của ghế (có ai đặt chưa)
bool Seat::getStatus() const {
    return isBooked;
}

// Hàm xử lý logic đặt ghế
bool Seat::bookSeat() {
    if (!isBooked) {       // Nếu ghế chưa bị đặt (!false -> true)
        isBooked = true;   // Chuyển trạng thái thành đã đặt
        return true;       // Báo cáo đặt thành công
    }
    return false; // Nếu isBooked là true rồi thì trả về false (đặt thất bại)
}

// Hàm hiển thị dạng text. [A1:O] là trống, [A1:X] là đã đặt
void Seat::displaySeat() const {
    cout << "[" << getSeatName() << (isBooked ? ":X" : ":O") << "] ";
}