#include "Movie.h"

#include <iostream>

using namespace std;

Movie::Movie(const string& id, const string& titleValue, int durationValue,
             const string& genreValue, int ageLimitValue,
             const string& statusValue)
    : movieId(id), title(titleValue), duration(durationValue),
      genre(genreValue), ageLimit(ageLimitValue), status(statusValue) {}

string Movie::getMovieId() const { return movieId; }
string Movie::getTitle() const { return title; }
int Movie::getDuration() const { return duration; }
string Movie::getGenre() const { return genre; }
int Movie::getAgeLimit() const { return ageLimit; }
string Movie::getStatus() const { return status; }

void Movie::setTitle(const string& value) { title = value; }
void Movie::setDuration(int value) { duration = value; }
void Movie::setGenre(const string& value) { genre = value; }
void Movie::setAgeLimit(int value) { ageLimit = value; }
void Movie::setStatus(const string& value) { status = value; }

void Movie::displayMovieInfo() const {
    cout << movieId << " | " << title
         << " | " << genre
         << " | " << duration << " phut"
         << " | P" << ageLimit
         << " | " << status << '\n';
}
