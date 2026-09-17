#pragma once

#include "../InputHandler/InputHandler.h"
#include "../../AccountManager/AccountManager.h"
#include "../../Booking/BookingManager.h"
#include "../../Movie/MovieManager.h"
#include "../../Room/CinemaRoomManager.h"
#include "../../Showtime/ShowtimeManager.h"
#include "../../Roles/Manager.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

class Menu
{
private:
    AccountManager accountManager;
    MovieManager movieManager;
    ShowtimeManager showtimeManager;
    CinemaRoomManager roomManager;
    BookingManager bookingManager;
    InputHandler input;

    void loginMenu();
    void customerMenu(const Account& account);

    void staffMenu(const Account& account);
    void staffAccountMenu();

    void managerMenu(const Account& account);
    void customerManagementMenu();

    void movieMenu();
    void showtimeMenu();
    void roomMenu();

    void bookingAtCounter(const Account& operatorAccount);
    void bookingOnline(const Account& customer);
    void bookingHistory(const string& customerId);
    void cancelBooking(const string& customerId, bool managerOrStaff);

    int chooseMovieForBooking();
    int chooseShowtimeForMovie(const string& movieId);

    void lookupMoviesAndShowtimes();

    void statisticsMenu();

    void printMovies(const vector<Movie>& movies) const;
    void printShowtimes(const vector<Showtime>& showtimes) const;
    void printRooms() const;

    void pause() const;
    string upper(string value) const;
    string trimSeatInput(string value) const;
    string roleText(Role role) const;

public:
    void run();
};
