#pragma once

#include "Booking.h"
#include "../Manager.h"
#include "../Room/CinemaRoomManager.h"
#include "../Showtime/ShowtimeManager.h"

#include <string>
#include <vector>

using namespace std;

struct BookingRequest {
    string customerId;
    string showtimeId;
    string staffId;
    vector<string> seatIds;
};

class BookingManager : public Manager<Booking> {
private:
    static string trim(const string& value);
    static vector<string> split(const string& value, char delimiter);
    static string nowText();
    int nextId() const;

public:
    explicit BookingManager(const string& file = "data/bookings.txt");

    bool load() override;
    bool save() const override;
    const Booking* findById(const string& id) const override;

    bool isSeatBooked(const string& showtimeId, const string& seatId) const;
    vector<string> getBookedSeats(const string& showtimeId) const;

    bool createBooking(const BookingRequest& request,
                       const ShowtimeManager& showtimes,
                       const CinemaRoomManager& rooms,
                       string& bookingId,
                       string& errorMessage);

    bool cancelBooking(const string& bookingId,
                       const ShowtimeManager& showtimes,
                       string& errorMessage);

    vector<Booking> getCustomerBookings(const string& customerId) const;
    double revenueOnDate(const string& date) const;
    double revenueInMonth(const string& month) const;
    double revenueInYear(const string& year) const;
    int totalPaidBookings() const;
    int totalPaidTickets() const;
    vector<pair<string, double>> revenueByMovie(const ShowtimeManager& showtimes) const;
};
