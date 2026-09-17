#pragma once

#include "../Manager.h"
#include "CinemaRoom.h"

#include <string>
#include <vector>

using namespace std;

class CinemaRoomManager : public Manager<CinemaRoom> {
private:
    static string trim(const string& value);
    int nextId() const;

public:
    explicit CinemaRoomManager(const string& file = "data/rooms.txt");

    bool load() override;
    bool save() const override;
    const CinemaRoom* findById(const string& id) const override;
    CinemaRoom* findMutable(const string& id);

    bool createRoom(const string& name, int rows, int cols, string& newId,
                    string& errorMessage);
    bool updateRoom(const string& id, const string& name,
                    int rows, int cols, string& errorMessage);
    bool setSeatVIP(const string& roomId, const string& seatId,
                    bool value, string& errorMessage);
    bool setSeatMaintenance(const string& roomId, const string& seatId,
                            bool value, string& errorMessage);
    bool deleteRoom(const string& id, string& errorMessage);

    vector<string> getSeatIds(const string& roomId) const;
};
