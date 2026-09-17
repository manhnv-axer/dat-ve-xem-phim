#pragma once

#include <iostream>
#include <string>

using namespace std;

class Movie {
private:
    string movieId;
    string title;
    int duration;
    string genre;
    int ageLimit;
    string status;

public:
    Movie(const string& id = "", const string& title = "", int duration = 0,
          const string& genre = "", int ageLimit = 0,
          const string& status = "Dang chieu");

    string getMovieId() const;
    string getTitle() const;
    int getDuration() const;
    string getGenre() const;
    int getAgeLimit() const;
    string getStatus() const;

    void setTitle(const string& value);
    void setDuration(int value);
    void setGenre(const string& value);
    void setAgeLimit(int value);
    void setStatus(const string& value);

    void displayMovieInfo() const;

    // Qua tai toan tu << de in thong tin phim truc tiep.
    friend ostream& operator<<(ostream& os, const Movie& movie);
};
