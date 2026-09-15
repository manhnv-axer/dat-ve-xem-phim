#pragma once
#include "../Core/DataManager.h"
#include "Showtime.h"
#include <fstream>
#include <iostream>

using namespace std;

class ShowtimeManager : public DataManager<Showtime> {
public:
    ShowtimeManager() : DataManager<Showtime>("showtimes.txt") {}

    void loadFromFile() override {
        ifstream file(fileName);
        if (!file.is_open()) return;

        string id, movieId, roomId, date, time;
        double price;
        
        // Đọc liên tục các khoảng trắng cho đến hết file
        while (file >> id >> movieId >> roomId >> date >> time >> price) {
            // Tạm thời truyền nullptr cho Movie và Room vì chúng ta sẽ liên kết chúng sau
            Showtime st(id, date, time, price, nullptr, nullptr);
            add(st);
        }
        file.close();
    }
    void saveToFile() override {
        ofstream file(fileName);
        if (!file.is_open()) return;

        // Định dạng ghi: MãSuất MãPhim MãPhòng Ngày Giờ Giá
        for (const auto& st : dataList) {
            // Tạm thời ghi dữ liệu cơ bản (Các mã liên kết sẽ xử lý sâu hơn ở phần sau)
            file << st.getShowtimeId() << " " 
                 << "M01" << " "       // Tạm để cứng mã phim
                 << "ROOM01" << " "    // Tạm để cứng mã phòng
                 << st.getShowDate() << " " 
                 << st.getStartTime() << " " 
                 << st.getBasePrice() << "\n";
        }
        file.close();
    }
};