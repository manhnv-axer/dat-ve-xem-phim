#pragma once
#include <vector>
#include <string>

using namespace std;

// Cú pháp khai báo Lớp khuôn mẫu (Template) 
template <class T>
class DataManager {
protected:
    vector<T> dataList; // Danh sách chứa đối tượng (Movie hoặc Showtime)
    string fileName;    // Tên file txt tương ứng

public:
    DataManager(string file) : fileName(file) {}

    // Hàm thêm 1 đối tượng vào danh sách
    void add(T item) {
        dataList.push_back(item);
    }

    // Lấy toàn bộ danh sách
    vector<T>& getAll() {
        return dataList;
    }

    // Hàm ảo thuần túy (Pure Virtual) bắt buộc các lớp con phải tự định nghĩa
    virtual void loadFromFile() = 0;
    virtual void saveToFile() = 0;
};