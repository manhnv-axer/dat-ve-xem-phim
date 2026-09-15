#pragma once
#include <string>
#include <iostream>

using namespace std;

class Movie {
private:
    string movieId;  // Mã phim (VD: M01)
    string title;    // Tên phim (VD: Avengers)
    int duration;    // Thời lượng tính bằng phút
    string genre;    // Thể loại (Hành động, Hài...)
    int ageLimit;   // Độ tuổi cho phép
public:
    // Hàm khởi tạo đầy đủ tham số để tạo ra một bộ phim hoàn chỉnh
    Movie(string id, string t, int d, string g, int age) 
        : movieId(id), title(t), duration(d), genre(g), ageLimit(age) {}

    int getAgeLimit() const { return ageLimit; }

    // Getters để lấy thông tin phim khi cần in ra vé
    string getTitle() const;
    int getDuration() const;
    string getMovieId() const { return movieId; }
    string getGenre() const { return genre; }
    // Hàm in thông tin chi tiết của phim
    void displayMovieInfo() const;
};