#include "Movie.h"

// Hàm khởi tạo (Constructor)
Movie::Movie(string id, string t, int d, string g, int age, string s)
    : movieId(id), title(t), duration(d), genre(g), ageLimit(age), status(s) {}

// Các hàm Getter lấy thông tin
string Movie::getMovieId() const { return movieId; }
string Movie::getTitle() const { return title; }
int Movie::getDuration() const { return duration; }
string Movie::getGenre() const { return genre; }
int Movie::getAgeLimit() const { return ageLimit; }
string Movie::getStatus() const { return status; }

// Hàm Setter cập nhật trạng thái
void Movie::setStatus(string s) { status = s; }

// Hàm in thông tin phim
void Movie::displayMovieInfo() const {
    cout << "Phim: " << title << " | The loai: " << genre 
         << " | Thoi luong: " << duration << " phut | Trang thai: " << status << endl;
}