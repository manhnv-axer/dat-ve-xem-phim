#pragma once
#include "../Movie/MovieManager.h"
#include "../Showtime/ShowtimeManager.h"
#include "../Ticket/Ticket.h" // Nạp thư viện Vé vào
#include <iostream>
#include <vector>

using namespace std;

class Menu {
private:
    MovieManager movieMgr;
    ShowtimeManager showtimeMgr;

    void showCustomerMenu();
    void showAdminMenu();
    
    // --- Các hàm phụ trợ cho luồng giao diện mới ---
    void displayAndSelectMovie(vector<Movie>& movies);
    void bookingFlow(Movie selectedMovie);
    void showTicketHistory(string username = "");
public:
    Menu();
    void run(); 
};