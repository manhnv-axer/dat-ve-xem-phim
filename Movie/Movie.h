#pragma once
#include <string>
#include <iostream>

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
    Movie(string id = "", string t = "", int d = 0, string g = "", int age = 0, string s = "");

    string getMovieId() const;
    string getTitle() const;
    int getDuration() const;
    string getGenre() const;
    int getAgeLimit() const;
    string getStatus() const;

    void setStatus(string s);
    void displayMovieInfo() const;
};