#include "Showtime.h"
#include <iostream>

// Hàm in thông tin chi tiết
void Showtime::displayShowtimeInfo() const {
    cout << "== LICH CHIEU: " << showtimeId << " ==" << endl;
    cout << "Thoi gian: " << startTime << endl;
    
    // Rất quan trọng: Luôn kiểm tra con trỏ có null (rỗng) hay không trước khi gọi hàm
    // Nếu không kiểm tra, chương trình sẽ bị crash (lỗi văng ứng dụng) nếu con trỏ rỗng
    if (movie != nullptr) {
        movie->displayMovieInfo(); // Dùng toán tử '->' để gọi hàm từ con trỏ
    }
    if (room != nullptr) {
        cout << "Phong chieu: " << room->getRoomId() << endl;
    }
}