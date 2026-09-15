#pragma once
#include "../Movie/MovieManager.h"
#include "../Showtime/ShowtimeManager.h"
#include <iostream>

using namespace std;

class Menu {
private:
    MovieManager movieMgr;
    ShowtimeManager showtimeMgr;

    // Các hàm giao diện chia theo phân quyền
    void showCustomerMenu();
    void showAdminMenu();

public:
    Menu();
    void run(); // Hàm vòng lặp chính của chương trình
};