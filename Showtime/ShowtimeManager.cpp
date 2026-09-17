#include "ShowtimeManager.h"

#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

ShowtimeManager::ShowtimeManager(const string& file) : Manager<Showtime>(file) {
    load();
}

string ShowtimeManager::trim(const string& value) {
    const size_t first = value.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }
    const size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

int ShowtimeManager::nextId() const {
    int maximum = 0;
    for (const Showtime& showtime : items) {
        if (showtime.getShowtimeId().size() > 2 && showtime.getShowtimeId().substr(0, 2) == "ST") {
            try {
                maximum = max(maximum, stoi(showtime.getShowtimeId().substr(2)));
            } catch (...) {
            }
        }
    }
    return maximum + 1;
}

bool ShowtimeManager::load() {
    items.clear();
    ifstream input(fileName);
    if (!input) {
        return true;
    }

    string line;
    while (getline(input, line)) {
        stringstream stream(line);
        string id, movieId, roomId, date, time, price, status;
        getline(stream, id, '|');
        getline(stream, movieId, '|');
        getline(stream, roomId, '|');
        getline(stream, date, '|');
        getline(stream, time, '|');
        getline(stream, price, '|');
        getline(stream, status, '|');

        if (id.empty() || id == "ID") {
            continue;
        }

        try {
            items.emplace_back(trim(id), trim(movieId), trim(roomId), trim(date),
                               trim(time), stod(trim(price)),
                               status.empty() ? "Dang chieu" : trim(status));
        } catch (...) {
        }
    }
    return true;
}

bool ShowtimeManager::save() const {
    ofstream output(fileName);
    if (!output) {
        return false;
    }

    for (const Showtime& showtime : items) {
        output << showtime.getShowtimeId() << '|'
               << showtime.getMovieId() << '|'
               << showtime.getRoomId() << '|'
               << showtime.getShowDate() << '|'
               << showtime.getStartTime() << '|'
               << showtime.getBasePrice() << '|'
               << showtime.getStatus() << '\n';
    }
    return true;
}

const Showtime* ShowtimeManager::findById(const string& id) const {
    for (const Showtime& showtime : items) {
        if (showtime.getShowtimeId() == id) {
            return &showtime;
        }
    }
    return nullptr;
}

bool ShowtimeManager::addShowtime(const Showtime& showtime, string& errorMessage) {
    if (findById(showtime.getShowtimeId()) != nullptr) {
        errorMessage = "Ma suat chieu da ton tai.";
        return false;
    }
    items.push_back(showtime);
    if (!save()) {
        items.pop_back();
        errorMessage = "Khong ghi duoc data/showtimes.txt.";
        return false;
    }
    return true;
}

bool ShowtimeManager::updateShowtime(const string& id, const string& movieId,
                                     const string& roomId, const string& date,
                                     const string& time, double price,
                                     string& errorMessage) {
    for (Showtime& showtime : items) {
        if (showtime.getShowtimeId() == id) {
            showtime.setMovieId(movieId);
            showtime.setRoomId(roomId);
            showtime.setShowDate(date);
            showtime.setStartTime(time);
            showtime.setBasePrice(price);
            if (!save()) {
                errorMessage = "Khong ghi duoc data/showtimes.txt.";
                return false;
            }
            return true;
        }
    }
    errorMessage = "Khong tim thay suat chieu.";
    return false;
}

bool ShowtimeManager::cancelShowtime(const string& id, string& errorMessage) {
    for (Showtime& showtime : items) {
        if (showtime.getShowtimeId() == id) {
            showtime.setStatus("Da huy");
            return save();
        }
    }
    errorMessage = "Khong tim thay suat chieu.";
    return false;
}

bool ShowtimeManager::deleteShowtime(const string& id, string& errorMessage) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getShowtimeId() == id) {
            items.erase(it);
            if (!save()) {
                errorMessage = "Khong ghi duoc data/showtimes.txt.";
                return false;
            }
            return true;
        }
    }
    errorMessage = "Khong tim thay suat chieu.";
    return false;
}

vector<Showtime> ShowtimeManager::getByMovieId(const string& movieId) const {
    return filter([&](const Showtime& showtime) {
        return showtime.getMovieId() == movieId && showtime.getStatus() != "Da huy";
    });
}

vector<Showtime> ShowtimeManager::getActiveShowtimes() const {
    return filter([](const Showtime& showtime) {
        return showtime.getStatus() != "Da huy";
    });
}
