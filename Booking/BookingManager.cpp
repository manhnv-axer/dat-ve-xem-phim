#include "BookingManager.h"
#include "../Ticket/StandardTicket.h"
#include "../Ticket/VIPTicket.h"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

BookingManager::BookingManager(const string& file) : Manager<Booking>(file) {
    load();
}

string BookingManager::trim(const string& value) {
    const size_t first = value.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }
    const size_t last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

vector<string> BookingManager::split(const string& value, char delimiter) {
    vector<string> result;
    string field;
    stringstream stream(value);
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

string BookingManager::nowText() {
    const auto now = chrono::system_clock::now();
    const time_t current = chrono::system_clock::to_time_t(now);
    tm localTime{};
#ifdef _WIN32
    localtime_s(&localTime, &current);
#else
    localtime_r(&current, &localTime);
#endif

    ostringstream output;
    output << put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return output.str();
}

int BookingManager::nextId() const {
    int maximum = 0;
    for (const Booking& booking : items) {
        if (booking.getBookingId().size() > 1 && booking.getBookingId()[0] == 'B') {
            try {
                maximum = max(maximum, stoi(booking.getBookingId().substr(1)));
            } catch (...) {
            }
        }
    }
    return maximum + 1;
}

bool BookingManager::load() {
    items.clear();
    ifstream input(fileName);
    if (!input) {
        return true;
    }

    string line;
    while (getline(input, line)) {
        vector<string> fields = split(line, '|');
        if (fields.size() < 7 || fields[0] == "BookingId") {
            continue;
        }

        BookingStatus status = fields[4] == "CANCELLED"
                                   ? BookingStatus::Cancelled
                                   : BookingStatus::Paid;
        Booking booking(fields[0], fields[1], fields[2], fields[3], fields[5], status);

        vector<string> ticketRecords = split(fields[6], ';');
        for (const string& record : ticketRecords) {
            vector<string> ticketFields = split(record, ',');
            if (ticketFields.size() < 4) {
                continue;
            }

            const string& ticketId = ticketFields[0];
            const string& seatId = ticketFields[1];
            const string& type = ticketFields[2];
            double basePrice = 0;
            try {
                basePrice = stod(ticketFields[3]);
            } catch (...) {
                continue;
            }

            if (type == "VIP") {
                booking.addTicket(make_unique<VIPTicket>(ticketId, fields[2], seatId, basePrice));
            } else {
                booking.addTicket(make_unique<StandardTicket>(ticketId, fields[2], seatId, basePrice));
            }
        }
        items.push_back(move(booking));
    }
    return true;
}

bool BookingManager::save() const {
    ofstream output(fileName);
    if (!output) {
        return false;
    }

    output << "BookingId|CustomerId|ShowtimeId|StaffId|Status|CreatedAt|Tickets|Total\n";
    for (const Booking& booking : items) {
        output << booking.getBookingId() << '|'
               << booking.getCustomerId() << '|'
               << booking.getShowtimeId() << '|'
               << booking.getStaffId() << '|'
               << booking.getStatusText() << '|'
               << booking.getCreatedAt() << '|';

        bool first = true;
        for (const unique_ptr<Ticket>& ticket : booking.getTickets()) {
            if (!first) {
                output << ';';
            }
            first = false;
            output << ticket->getTicketId() << ','
                   << ticket->getSeatId() << ','
                   << ticket->getType() << ','
                   << ticket->getBasePrice();
        }
        output << '|' << booking.getTotal() << '\n';
    }
    return true;
}

const Booking* BookingManager::findById(const string& id) const {
    for (const Booking& booking : items) {
        if (booking.getBookingId() == id) {
            return &booking;
        }
    }
    return nullptr;
}

bool BookingManager::isSeatBooked(const string& showtimeId, const string& seatId) const {
    for (const Booking& booking : items) {
        if (booking.getShowtimeId() == showtimeId &&
            booking.getStatus() == BookingStatus::Paid &&
            booking.containsSeat(seatId)) {
            return true;
        }
    }
    return false;
}

vector<string> BookingManager::getBookedSeats(const string& showtimeId) const {
    vector<string> result;
    for (const Booking& booking : items) {
        if (booking.getShowtimeId() != showtimeId ||
            booking.getStatus() != BookingStatus::Paid) {
            continue;
        }
        for (const unique_ptr<Ticket>& ticket : booking.getTickets()) {
            result.push_back(ticket->getSeatId());
        }
    }
    return result;
}

bool BookingManager::createBooking(const BookingRequest& request,
                                   const ShowtimeManager& showtimes,
                                   const CinemaRoomManager& rooms,
                                   string& bookingId,
                                   string& errorMessage) {
    const Showtime* showtime = showtimes.findById(request.showtimeId);
    if (showtime == nullptr) {
        errorMessage = "Suat chieu khong ton tai.";
        return false;
    }
    if (showtime->getStatus() == "Da huy") {
        errorMessage = "Suat chieu da bi huy.";
        return false;
    }

    const CinemaRoom* room = rooms.findById(showtime->getRoomId());
    if (room == nullptr) {
        errorMessage = "Phong chieu khong ton tai.";
        return false;
    }
    if (request.seatIds.empty()) {
        errorMessage = "Booking phai co it nhat mot ghe.";
        return false;
    }

    vector<string> uniqueSeats;
    for (string seatId : request.seatIds) {
        transform(seatId.begin(), seatId.end(), seatId.begin(),
                  [](unsigned char c) { return static_cast<char>(toupper(c)); });

        if (find(uniqueSeats.begin(), uniqueSeats.end(), seatId) != uniqueSeats.end()) {
            errorMessage = "Khong duoc chon trung ghe trong mot Booking.";
            return false;
        }
        uniqueSeats.push_back(seatId);

        const Seat* seat = room->getSeatById(seatId);
        if (seat == nullptr) {
            errorMessage = "Ghe " + seatId + " khong ton tai.";
            return false;
        }
        if (seat->isMaintenance()) {
            errorMessage = "Ghe " + seatId + " dang bao tri.";
            return false;
        }
        if (isSeatBooked(showtime->getShowtimeId(), seatId)) {
            errorMessage = "Ghe " + seatId + " da duoc dat.";
            return false;
        }
    }

    bookingId = "B";
    ostringstream idStream;
    idStream << 'B' << setw(4) << setfill('0') << nextId();
    bookingId = idStream.str();

    Booking booking(bookingId, request.customerId, request.showtimeId,
                    request.staffId, nowText(), BookingStatus::Paid);

    int ticketNumber = 1;
    for (const string& seatId : uniqueSeats) {
        ostringstream ticketId;
        ticketId << bookingId << "-T" << setw(2) << setfill('0') << ticketNumber++;
        const Seat* seat = room->getSeatById(seatId);

        if (seat->isVIP()) {
            booking.addTicket(make_unique<VIPTicket>(
                ticketId.str(), request.showtimeId, seatId, showtime->getBasePrice()));
        } else {
            booking.addTicket(make_unique<StandardTicket>(
                ticketId.str(), request.showtimeId, seatId, showtime->getBasePrice()));
        }
    }

    items.push_back(move(booking));
    if (!save()) {
        items.pop_back();
        errorMessage = "Khong ghi duoc data/bookings.txt.";
        return false;
    }
    return true;
}

bool BookingManager::cancelBooking(const string& bookingId,
                                    const ShowtimeManager& showtimes,
                                    string& errorMessage) {
    Booking* booking = nullptr;
    for (Booking& item : items) {
        if (item.getBookingId() == bookingId) {
            booking = &item;
            break;
        }
    }

    if (booking == nullptr) {
        errorMessage = "Khong tim thay Booking.";
        return false;
    }
    if (booking->getStatus() == BookingStatus::Cancelled) {
        errorMessage = "Booking da huy truoc do.";
        return false;
    }

    const Showtime* showtime = showtimes.findById(booking->getShowtimeId());
    if (showtime == nullptr) {
        errorMessage = "Khong tim thay suat chieu.";
        return false;
    }

    tm showTime{};
    istringstream dateStream(showtime->getShowDate() + " " + showtime->getStartTime());
    dateStream >> get_time(&showTime, "%Y-%m-%d %H:%M");
    if (dateStream.fail()) {
        errorMessage = "Khong doc duoc ngay gio suat chieu.";
        return false;
    }

    const time_t showTimestamp = mktime(&showTime);
    const auto now = chrono::system_clock::now();
    const time_t currentTimestamp = chrono::system_clock::to_time_t(now);
    const double minutesLeft = difftime(showTimestamp, currentTimestamp) / 60.0;

    if (minutesLeft < 30.0) {
        errorMessage = "Chi duoc huy Booking truoc gio chieu it nhat 30 phut.";
        return false;
    }

    booking->setStatus(BookingStatus::Cancelled);
    if (!save()) {
        errorMessage = "Khong ghi duoc data/bookings.txt.";
        return false;
    }
    return true;
}

vector<Booking> BookingManager::getCustomerBookings(const string& customerId) const {
    return filter([&](const Booking& booking) {
        return booking.getCustomerId() == customerId;
    });
}

double BookingManager::revenueOnDate(const string& date) const {
    double total = 0;
    for (const Booking& booking : items) {
        if (booking.getStatus() == BookingStatus::Paid &&
            booking.getCreatedAt().substr(0, 10) == date) {
            total += booking.getTotal();
        }
    }
    return total;
}

double BookingManager::revenueInMonth(const string& month) const {
    double total = 0;
    for (const Booking& booking : items) {
        if (booking.getStatus() == BookingStatus::Paid &&
            booking.getCreatedAt().substr(0, 7) == month) {
            total += booking.getTotal();
        }
    }
    return total;
}

double BookingManager::revenueInYear(const string& year) const {
    double total = 0;
    for (const Booking& booking : items) {
        if (booking.getStatus() == BookingStatus::Paid &&
            booking.getCreatedAt().substr(0, 4) == year) {
            total += booking.getTotal();
        }
    }
    return total;
}

int BookingManager::totalPaidBookings() const {
    int count = 0;
    for (const Booking& booking : items) {
        if (booking.getStatus() == BookingStatus::Paid) {
            ++count;
        }
    }
    return count;
}

int BookingManager::totalPaidTickets() const {
    int count = 0;
    for (const Booking& booking : items) {
        if (booking.getStatus() == BookingStatus::Paid) {
            count += static_cast<int>(booking.getTickets().size());
        }
    }
    return count;
}

vector<pair<string, double>> BookingManager::revenueByMovie(const ShowtimeManager& showtimes) const {
    vector<pair<string, double>> result;

    for (const Booking& booking : items) {
        if (booking.getStatus() != BookingStatus::Paid) {
            continue;
        }

        const Showtime* showtime = showtimes.findById(booking.getShowtimeId());
        if (showtime == nullptr) {
            continue;
        }

        bool found = false;
        for (auto& entry : result) {
            if (entry.first == showtime->getMovieId()) {
                entry.second += booking.getTotal();
                found = true;
                break;
            }
        }
        if (!found) {
            result.push_back({showtime->getMovieId(), booking.getTotal()});
        }
    }

    sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    return result;
}
