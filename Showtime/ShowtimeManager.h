#pragma once

#include "../Manager.h"
#include "Showtime.h"

#include <string>
#include <vector>

using namespace std;

class ShowtimeManager : public Manager<Showtime> {
private:
    static string trim(const string& value);
    int nextId() const;

public:
    explicit ShowtimeManager(const string& file = "data/showtimes.txt");

    bool load() override;
    bool save() const override;
    const Showtime* findById(const string& id) const override;

    bool addShowtime(const Showtime& showtime, string& errorMessage);
    bool updateShowtime(const string& id, const string& movieId,
                        const string& roomId, const string& date,
                        const string& time, double price,
                        string& errorMessage);
    bool cancelShowtime(const string& id, string& errorMessage);
    bool deleteShowtime(const string& id, string& errorMessage);

    vector<Showtime> getByMovieId(const string& movieId) const;
    vector<Showtime> getActiveShowtimes() const;
};
