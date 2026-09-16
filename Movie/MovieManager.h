#pragma once
#include "../Core/DataManager.h"
#include "Movie.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

class MovieManager : public DataManager<Movie> {
private:
    // Tự động xóa khoảng trắng thừa ở đầu và cuối
    string trim(string s) {
        int start = 0;
        while (start < s.length() && s[start] == ' ') start++;
        int end = s.length() - 1;
        while (end >= 0 && s[end] == ' ') end--;
        if (start > end) return "";
        return s.substr(start, end - start + 1);
    }

    string toLower(string s) {
        string res = s;
        for (int i = 0; i < res.length(); i++) {
            res[i] = tolower(res[i]);
        }
        return res;
    }

public:
    MovieManager() : DataManager<Movie>("data/movies.txt") {}

    void loadFromFile() override {
        ifstream file(fileName);
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, title, genre, durationStr, ageStr, status;
            
            getline(ss, id, '|');
            getline(ss, title, '|');
            getline(ss, genre, '|');
            getline(ss, durationStr, '|');
            getline(ss, ageStr, '|');
            getline(ss, status, '|'); 

            if (!id.empty()) {
                int duration = stoi(durationStr);
                int age = stoi(ageStr);
                if (status.empty()) status = "Dang chieu"; 
                
                Movie m(trim(id), trim(title), duration, trim(genre), age, trim(status));
                add(m);
            }
        }
        file.close();
    }

    void saveToFile() override {
        ofstream file(fileName);
        if (!file.is_open()) return;

        for (const auto& m : dataList) {
            file << m.getMovieId() << "|" << m.getTitle() << "|" << m.getGenre() << "|" 
                 << m.getDuration() << "|" << m.getAgeLimit() << "|" << m.getStatus() << "\n";
        }
        file.close();
    }

    vector<Movie> searchMoviesByTitle(string keyword) {
        vector<Movie> result;
        string keyLower = toLower(trim(keyword)); 
        for (const auto& m : dataList) {
            if (toLower(m.getTitle()).find(keyLower) != string::npos) {
                result.push_back(m);
            }
        }
        return result;
    }

    vector<Movie> searchMoviesByGenre(string keyword) {
        vector<Movie> result;
        string keyLower = toLower(trim(keyword)); 
        for (const auto& m : dataList) {
            if (toLower(m.getGenre()).find(keyLower) != string::npos) {
                result.push_back(m);
            }
        }
        return result;
    }

    vector<Movie> getMoviesByStatus(string statusFilter) {
        vector<Movie> result;
        for (const auto& m : dataList) {
            if (m.getStatus() == statusFilter) {
                result.push_back(m);
            }
        }
        return result;
    }

    void updateMovieStatus(string id, string newStatus) {
        for (auto& m : dataList) {
            if (m.getMovieId() == id) {
                m.setStatus(newStatus);
                cout << ">> Cap nhat trang thai thanh cong!" << endl;
                return;
            }
        }
        cout << ">> Khong tim thay ma phim: " << id << endl;
    }

    void deleteMovie(string id) {
        for (auto it = dataList.begin(); it != dataList.end(); ++it) {
            if (it->getMovieId() == id) {
                dataList.erase(it);
                cout << ">> Xoa phim thanh cong!" << endl;
                return;
            }
        }
        cout << ">> Khong tim thay ma phim: " << id << endl;
    }
};