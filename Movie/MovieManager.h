#pragma once

#include "../Manager.h"
#include "Movie.h"

#include <string>
#include <vector>

using namespace std;

class MovieManager : public Manager<Movie> {
private:
    static string trim(const string& value);
    static string lower(string value);
    int nextId() const;

public:
    explicit MovieManager(const string& file = "data/movies.txt");

    bool load() override;
    bool save() const override;
    const Movie* findById(const string& id) const override;

    bool addMovie(const Movie& movie, string& errorMessage);
    bool updateMovie(const string& id, const string& title,
                     int duration, const string& genre, int ageLimit,
                     string& errorMessage);
    bool deleteMovie(const string& id, string& errorMessage);
    bool setStatus(const string& id, const string& status, string& errorMessage);

    vector<Movie> searchByTitle(const string& keyword) const;
    vector<Movie> searchByGenre(const string& keyword) const;
    vector<Movie> getByStatus(const string& status) const;
};
