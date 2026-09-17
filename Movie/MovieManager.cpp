#include "MovieManager.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

using namespace std;

MovieManager::MovieManager(const string& file) : Manager<Movie>(file) {
    load();
}

string MovieManager::trim(const string& value) {
    const size_t first = value.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }
    const size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

string MovieManager::lower(string value) {
    transform(value.begin(), value.end(), value.begin(),
              [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return value;
}

int MovieManager::nextId() const {
    int maximum = 0;
    for (const Movie& movie : items) {
        if (movie.getMovieId().size() > 1 && movie.getMovieId()[0] == 'M') {
            try {
                maximum = max(maximum, stoi(movie.getMovieId().substr(1)));
            } catch (...) {
            }
        }
    }
    return maximum + 1;
}

bool MovieManager::load() {
    items.clear();
    ifstream input(fileName);
    if (!input) {
        return true;
    }

    string line;
    while (getline(input, line)) {
        stringstream stream(line);
        string id, title, genre, duration, age, status;
        getline(stream, id, '|');
        getline(stream, title, '|');
        getline(stream, genre, '|');
        getline(stream, duration, '|');
        getline(stream, age, '|');
        getline(stream, status, '|');

        if (id.empty() || id == "ID") {
            continue;
        }

        try {
            items.emplace_back(trim(id), trim(title), stoi(trim(duration)),
                               trim(genre), stoi(trim(age)), trim(status));
        } catch (...) {
        }
    }
    return true;
}

bool MovieManager::save() const {
    ofstream output(fileName);
    if (!output) {
        return false;
    }

    for (const Movie& movie : items) {
        output << movie.getMovieId() << '|'
               << movie.getTitle() << '|'
               << movie.getGenre() << '|'
               << movie.getDuration() << '|'
               << movie.getAgeLimit() << '|'
               << movie.getStatus() << '\n';
    }
    return true;
}

const Movie* MovieManager::findById(const string& id) const {
    for (const Movie& movie : items) {
        if (movie.getMovieId() == id) {
            return &movie;
        }
    }
    return nullptr;
}

bool MovieManager::addMovie(const Movie& movie, string& errorMessage) {
    if (findById(movie.getMovieId()) != nullptr) {
        errorMessage = "Ma phim da ton tai.";
        return false;
    }
    items.push_back(movie);
    if (!save()) {
        items.pop_back();
        errorMessage = "Khong ghi duoc data/movies.txt.";
        return false;
    }
    return true;
}

bool MovieManager::updateMovie(const string& id, const string& title,
                               int duration, const string& genre, int ageLimit,
                               string& errorMessage) {
    Movie* target = nullptr;
    for (Movie& movie : items) {
        if (movie.getMovieId() == id) {
            target = &movie;
            break;
        }
    }
    if (target == nullptr) {
        errorMessage = "Khong tim thay phim.";
        return false;
    }

    target->setTitle(title);
    target->setDuration(duration);
    target->setGenre(genre);
    target->setAgeLimit(ageLimit);
    if (!save()) {
        errorMessage = "Khong ghi duoc data/movies.txt.";
        return false;
    }
    return true;
}

bool MovieManager::deleteMovie(const string& id, string& errorMessage) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getMovieId() == id) {
            items.erase(it);
            if (!save()) {
                errorMessage = "Khong ghi duoc data/movies.txt.";
                return false;
            }
            return true;
        }
    }
    errorMessage = "Khong tim thay phim.";
    return false;
}

bool MovieManager::setStatus(const string& id, const string& status,
                             string& errorMessage) {
    for (Movie& movie : items) {
        if (movie.getMovieId() == id) {
            movie.setStatus(status);
            return save();
        }
    }
    errorMessage = "Khong tim thay phim.";
    return false;
}

vector<Movie> MovieManager::searchByTitle(const string& keyword) const {
    const string key = lower(trim(keyword));
    return filter([&](const Movie& movie) {
        return lower(movie.getTitle()).find(key) != string::npos;
    });
}

vector<Movie> MovieManager::searchByGenre(const string& keyword) const {
    const string key = lower(trim(keyword));
    return filter([&](const Movie& movie) {
        return lower(movie.getGenre()).find(key) != string::npos;
    });
}

vector<Movie> MovieManager::getByStatus(const string& status) const {
    return filter([&](const Movie& movie) {
        return movie.getStatus() == status;
    });
}
