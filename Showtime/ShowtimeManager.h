#pragma once
#include "../Core/DataManager.h"
#include "Showtime.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

class ShowtimeManager : public DataManager<Showtime> {
public:
    ShowtimeManager() : DataManager<Showtime>("data/showtimes.txt") {}

    void loadFromFile() override {
        ifstream file(fileName);
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string sId, mId, rId, date, time, priceStr;
            
            // Cắt chuỗi theo dấu '|'
            getline(ss, sId, '|');
            getline(ss, mId, '|');
            getline(ss, rId, '|');
            getline(ss, date, '|');
            getline(ss, time, '|');
            getline(ss, priceStr, '|');

            if (!sId.empty()) {
                double price = stod(priceStr);
                Showtime st(sId, mId, rId, date, time, price);
                add(st);
            }
        }
        file.close();
    }

    void saveToFile() override {
        ofstream file(fileName);
        if (!file.is_open()) return;

        for (const auto& st : dataList) {
            file << st.getShowtimeId() << "|" 
                 << st.getMovieId() << "|" 
                 << st.getRoomId() << "|" 
                 << st.getShowDate() << "|" 
                 << st.getStartTime() << "|" 
                 << st.getBasePrice() << "\n";
        }
        file.close();
    }

    // --- HÀM MỚI QUAN TRỌNG: Lọc suất chiếu theo Phim ---
    vector<Showtime> getShowtimesByMovieId(string mId) {
        vector<Showtime> result;
        for (const auto& st : dataList) {
            if (st.getMovieId() == mId) {
                result.push_back(st);
            }
        }
        return result;
    }
};