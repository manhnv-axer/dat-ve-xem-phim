#include "Movie.h"

string Movie::getTitle() const { return title; }
int Movie::getDuration() const { return duration; }

// In thông tin định dạng sẵn ra màn hình console
void Movie::displayMovieInfo() const {
    cout << "Phim: " << title << " | The loai: " << genre 
         << " | Thoi luong: " << duration << " phut" << endl;
}