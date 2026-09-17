#include "Booking.h"

#include <iomanip>
#include <iostream>

using namespace std;

Booking::Booking()
    : bookingId(""), customerId(""), showtimeId(""), staffId(""),
      createdAt(""), status(BookingStatus::Paid) {}

Booking::Booking(const string& id, const string& customerIdValue,
                 const string& showtimeIdValue, const string& staffIdValue,
                 const string& createdAtValue, BookingStatus statusValue)
    : bookingId(id), customerId(customerIdValue), showtimeId(showtimeIdValue),
      staffId(staffIdValue), createdAt(createdAtValue), status(statusValue) {}

Booking::Booking(const Booking& other)
    : bookingId(other.bookingId), customerId(other.customerId),
      showtimeId(other.showtimeId), staffId(other.staffId),
      createdAt(other.createdAt), status(other.status) {
    for (const unique_ptr<Ticket>& ticket : other.tickets) {
        tickets.push_back(ticket->clone());
    }
}

Booking& Booking::operator=(const Booking& other) {
    if (this == &other) {
        return *this;
    }

    bookingId = other.bookingId;
    customerId = other.customerId;
    showtimeId = other.showtimeId;
    staffId = other.staffId;
    createdAt = other.createdAt;
    status = other.status;
    tickets.clear();

    for (const unique_ptr<Ticket>& ticket : other.tickets) {
        tickets.push_back(ticket->clone());
    }
    return *this;
}

const string& Booking::getBookingId() const { return bookingId; }
const string& Booking::getCustomerId() const { return customerId; }
const string& Booking::getShowtimeId() const { return showtimeId; }
const string& Booking::getStaffId() const { return staffId; }
const string& Booking::getCreatedAt() const { return createdAt; }
BookingStatus Booking::getStatus() const { return status; }

string Booking::getStatusText() const {
    return status == BookingStatus::Paid ? "PAID" : "CANCELLED";
}

const vector<unique_ptr<Ticket>>& Booking::getTickets() const { return tickets; }
vector<unique_ptr<Ticket>>& Booking::getTickets() { return tickets; }

double Booking::getTotal() const {
    double total = 0;
    for (const unique_ptr<Ticket>& ticket : tickets) {
        total += ticket->getPrice();
    }
    return total;
}

void Booking::addTicket(unique_ptr<Ticket> ticket) {
    if (ticket != nullptr) {
        tickets.push_back(move(ticket));
    }
}

void Booking::setStatus(BookingStatus value) { status = value; }

bool Booking::containsSeat(const string& seatId) const {
    for (const unique_ptr<Ticket>& ticket : tickets) {
        if (ticket->getSeatId() == seatId) {
            return true;
        }
    }
    return false;
}

void Booking::displayInvoice(const string& movieTitle, const string& showDate,
                             const string& startTime, const string& roomId) const {
    cout << "\n============================================================\n";
    cout << "                     HOA DON DAT VE\n";
    cout << "============================================================\n";
    cout << "Ma Booking : " << bookingId << '\n';
    cout << "Khach hang : " << customerId << '\n';
    cout << "Phim       : " << movieTitle << '\n';
    cout << "Suat chieu : " << showDate << ' ' << startTime << '\n';
    cout << "Phong      : " << roomId << '\n';
    cout << "Nhan vien  : " << (staffId.empty() ? "Online" : staffId) << '\n';
    cout << "Trang thai : " << getStatusText() << '\n';
    cout << "------------------------------------------------------------\n";

    for (const unique_ptr<Ticket>& ticket : tickets) {
        ticket->displayTicket();
    }

    cout << "------------------------------------------------------------\n";
    cout << "Tong cong  : " << fixed << setprecision(0) << getTotal() << " VND\n";
    cout << "============================================================\n";
}
