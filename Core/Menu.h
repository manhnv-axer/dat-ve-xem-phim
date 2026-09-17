#pragma once

#include "../AccountManager/AccountManager.h"
#include "../Booking/BookingManager.h"
#include "../Movie/MovieManager.h"
#include "../Room/CinemaRoomManager.h"
#include "../Showtime/ShowtimeManager.h"
#include "../Roles/Manager.h"

#include <string>
#include <vector>

using namespace std;

class Menu {
private:
    AccountManager accountManager;
    MovieManager movieManager;
    ShowtimeManager showtimeManager;
    CinemaRoomManager roomManager;
    BookingManager bookingManager;

    void loginMenu();
    void openAccountMenu(const Account& account);
    const Account* loadSession() const;
    bool saveSession(const Account& account) const;
    void clearSession() const;
    void customerMenu(const Account& account);
    void staffMenu(const Account& account);
    void managerMenu(const Account& account);

    void movieMenu();
    void showtimeMenu();
    void roomMenu();
    void staffAccountMenu();
    void customerManagementMenu();
    void bookingAtCounter(const Account& operatorAccount);
    void bookingOnline(const Account& customer);
    void lookupMoviesAndShowtimes();
    void bookingHistory(const string& customerId);
    void cancelBooking(const string& customerId, bool managerOrStaff);
    void statisticsMenu();
    int chooseMovieForBooking();
    int chooseShowtimeForMovie(const string& movieId);

    void printMovies(const vector<Movie>& movies) const;
    void printShowtimes(const vector<Showtime>& showtimes) const;
    void printRooms() const;
    void pause() const;

public:
    Menu() = default;
    void run();
};
