#pragma once

#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

using namespace std;

// Template quan ly dung chung cho Movie, Showtime, Room, Account, Booking...
template <typename T>
class Manager {
protected:
    string fileName;
    vector<T> items;

public:
    explicit Manager(const string& file = "") : fileName(file) {}
    virtual ~Manager() = default;

    const vector<T>& getItems() const { return items; }
    vector<T>& getItems() { return items; }
    size_t size() const { return items.size(); }

    void add(const T& item) { items.push_back(item); }

    template <typename Predicate>
    vector<T> filter(Predicate predicate) const {
        vector<T> result;
        for (const T& item : items) {
            if (predicate(item)) {
                result.push_back(item);
            }
        }
        return result;
    }

    virtual bool load() = 0;
    virtual bool save() const = 0;
    virtual const T* findById(const string& id) const = 0;
};
