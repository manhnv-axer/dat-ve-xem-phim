#include "CinemaRoomManager.h"
#include <algorithm>

#include <fstream>
#include <sstream>

using namespace std;

CinemaRoomManager::CinemaRoomManager(const string& file) : Manager<CinemaRoom>(file) {
    load();
}

string CinemaRoomManager::trim(const string& value) {
    const size_t first = value.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }
    const size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

int CinemaRoomManager::nextId() const {
    int maximum = 0;
    for (const CinemaRoom& room : items) {
        try {
            if (room.getRoomId().rfind("ROOM", 0) == 0) {
                maximum = max(maximum, stoi(room.getRoomId().substr(4)));
            } else if (room.getRoomId().size() > 1 && room.getRoomId()[0] == 'R') {
                maximum = max(maximum, stoi(room.getRoomId().substr(1)));
            }
        } catch (...) {
        }
    }
    return maximum + 1;
}

bool CinemaRoomManager::load() {
    items.clear();
    ifstream input(fileName);
    if (!input) {
        return true;
    }

    string line;
    while (getline(input, line)) {
        stringstream stream(line);
        string id, name, rows, cols, seatData;
        getline(stream, id, '|');
        getline(stream, name, '|');
        getline(stream, rows, '|');
        getline(stream, cols, '|');
        getline(stream, seatData, '|');

        if (id.empty() || id == "ID") {
            continue;
        }

        try {
            CinemaRoom room(trim(id), trim(name), stoi(trim(rows)), stoi(trim(cols)));
            stringstream seatStream(seatData);
            string seatRecord;
            while (getline(seatStream, seatRecord, ';')) {
                if (seatRecord.empty()) {
                    continue;
                }
                stringstream record(seatRecord);
                string seatId, vip, maintenance;
                getline(record, seatId, ',');
                getline(record, vip, ',');
                getline(record, maintenance, ',');
                Seat* seat = room.getSeatById(trim(seatId));
                if (seat != nullptr) {
                    seat->setVIP(trim(vip) == "1");
                    seat->setMaintenance(trim(maintenance) == "1");
                }
            }
            items.push_back(room);
        } catch (...) {
        }
    }
    return true;
}

bool CinemaRoomManager::save() const {
    ofstream output(fileName);
    if (!output) {
        return false;
    }

    for (const CinemaRoom& room : items) {
        output << room.getRoomId() << '|'
               << room.getRoomName() << '|'
               << room.getRowCount() << '|'
               << room.getColCount() << '|';

        bool first = true;
        for (const Seat& seat : room.getSeats()) {
            if (!first) {
                output << ';';
            }
            first = false;
            output << seat.getSeatId() << ','
                   << (seat.isVIP() ? 1 : 0) << ','
                   << (seat.isMaintenance() ? 1 : 0);
        }
        output << '\n';
    }
    return true;
}

const CinemaRoom* CinemaRoomManager::findById(const string& id) const {
    for (const CinemaRoom& room : items) {
        if (room.getRoomId() == id) {
            return &room;
        }
    }
    return nullptr;
}

CinemaRoom* CinemaRoomManager::findMutable(const string& id) {
    for (CinemaRoom& room : items) {
        if (room.getRoomId() == id) {
            return &room;
        }
    }
    return nullptr;
}

bool CinemaRoomManager::createRoom(const string& name, int rows, int cols,
                                    string& newId, string& errorMessage) {
    if (rows < 1 || cols < 1 || rows > 26 || cols > 30) {
        errorMessage = "So dong/cot khong hop le (dong 1-26, cot 1-30).";
        return false;
    }

    newId = "ROOM" + to_string(nextId());
    items.emplace_back(newId, name, rows, cols);
    if (!save()) {
        items.pop_back();
        errorMessage = "Khong ghi duoc data/rooms.txt.";
        return false;
    }
    return true;
}

bool CinemaRoomManager::updateRoom(const string& id, const string& name,
                                    int rows, int cols, string& errorMessage) {
    CinemaRoom* room = findMutable(id);
    if (room == nullptr) {
        errorMessage = "Khong tim thay phong.";
        return false;
    }
    room->setName(name);
    room->setDimensions(rows, cols);
    if (!save()) {
        errorMessage = "Khong ghi duoc data/rooms.txt.";
        return false;
    }
    return true;
}

bool CinemaRoomManager::setSeatVIP(const string& roomId, const string& seatId,
                                    bool value, string& errorMessage) {
    CinemaRoom* room = findMutable(roomId);
    if (room == nullptr || room->getSeatById(seatId) == nullptr) {
        errorMessage = "Phong hoac ghe khong ton tai.";
        return false;
    }
    room->setVIP(seatId, value);
    return save();
}

bool CinemaRoomManager::setSeatMaintenance(const string& roomId,
                                            const string& seatId, bool value,
                                            string& errorMessage) {
    CinemaRoom* room = findMutable(roomId);
    if (room == nullptr || room->getSeatById(seatId) == nullptr) {
        errorMessage = "Phong hoac ghe khong ton tai.";
        return false;
    }
    room->setMaintenance(seatId, value);
    return save();
}

bool CinemaRoomManager::deleteRoom(const string& id, string& errorMessage) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getRoomId() == id) {
            items.erase(it);
            return save();
        }
    }
    errorMessage = "Khong tim thay phong.";
    return false;
}

vector<string> CinemaRoomManager::getSeatIds(const string& roomId) const {
    const CinemaRoom* room = findById(roomId);
    vector<string> result;
    if (room == nullptr) {
        return result;
    }
    for (const Seat& seat : room->getSeats()) {
        result.push_back(seat.getSeatId());
    }
    return result;
}
