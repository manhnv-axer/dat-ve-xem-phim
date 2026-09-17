#pragma once

#include "../Ticket/Ticket.h"
#include <memory>
#include <string>
#include <vector>

using namespace std;

enum class BookingStatus {
    Paid,
    Cancelled
};

class Booking {
private:
    string bookingId;
    string customerId;
    string showtimeId;
    string staffId;
    string createdAt;
    BookingStatus status;
    vector<unique_ptr<Ticket>> tickets;

public:
    Booking();
    Booking(const string& id, const string& customerId,
            const string& showtimeId, const string& staffId,
            const string& createdAt, BookingStatus status = BookingStatus::Paid);
    Booking(const Booking& other);
    Booking& operator=(const Booking& other);
    Booking(Booking&&) noexcept = default;
    Booking& operator=(Booking&&) noexcept = default;
    ~Booking() = default;

    const string& getBookingId() const;
    const string& getCustomerId() const;
    const string& getShowtimeId() const;
    const string& getStaffId() const;
    const string& getCreatedAt() const;
    BookingStatus getStatus() const;
    string getStatusText() const;

    const vector<unique_ptr<Ticket>>& getTickets() const;
    vector<unique_ptr<Ticket>>& getTickets();
    double getTotal() const;

    void addTicket(unique_ptr<Ticket> ticket);
    void setStatus(BookingStatus value);
    bool containsSeat(const string& seatId) const;
    void displayInvoice(const string& movieTitle, const string& showDate,
                        const string& startTime, const string& roomId) const;
};
