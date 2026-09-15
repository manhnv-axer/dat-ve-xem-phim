#pragma once
#include "../Core/DataManager.h"
#include "Movie.h"
#include <fstream>  // Thư viện thao tác file
#include <sstream>  // Thư viện tách chuỗi
#include <iostream>

using namespace std;

class MovieManager : public DataManager<Movie> {
public:
    // Kế thừa và truyền tên file mặc định là movies.txt vào DataManager
    MovieManager() : DataManager<Movie>("movies.txt") {}

    // GHI ĐÈ (Override) hàm đọc file
    void loadFromFile() override {
        ifstream file(fileName);
        if (!file.is_open()) return;

        string line;
        // Đọc từng dòng trong file txt
        while (getline(file, line)) {
            stringstream ss(line);
            string id, title, genre, durationStr, ageStr;
            
            // Cắt chuỗi theo dấu '|'
            getline(ss, id, '|');
            getline(ss, title, '|');
            getline(ss, genre, '|');
            getline(ss, durationStr, '|');
            getline(ss, ageStr, '|');

            if (!id.empty()) {
                // Ép kiểu chuỗi về số nguyên (int)
                int duration = stoi(durationStr);
                int age = stoi(ageStr);
                
                // Tạo đối tượng Movie và thêm vào mảng
                Movie m(id, title, duration, genre, age);
                add(m);
            }
        }
        file.close();
    }
    // GHI ĐÈ (Override) hàm lưu file
    void saveToFile() override {
        ofstream file(fileName);
        if (!file.is_open()) return;

        // Quét toàn bộ phim và ghi vào file theo định dạng: Mã|Tên|Thểloại|ThờiLượng|Tuổi
        for (const auto& m : dataList) {
            file << m.getMovieId() << "|" 
                 << m.getTitle() << "|" 
                 << m.getGenre() << "|" 
                 << m.getDuration() << "|" 
                 << m.getAgeLimit() << "\n";
        }
        file.close();
    }
};