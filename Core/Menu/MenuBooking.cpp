#include "Menu.h"

#include <iomanip>

#include <sstream>

using namespace std;

void Menu::bookingOnline(const Account& customer)
{
    input.clearScreen();

    int movieIndex = chooseMovieForBooking();

    if (movieIndex < 0)
        return;

    vector<Movie> movies =
        movieManager.getByStatus("Dang chieu");

    if (movieIndex >= static_cast<int>(movies.size()))
        return;

    const Movie& selectedMovie = movies[movieIndex];

    cout << "\n=======================================================\n";
    cout << ">> DANG DAT VE CHO PHIM: "
         << selectedMovie.getTitle() << " <<\n";

    int showtimeIndex =
        chooseShowtimeForMovie(selectedMovie.getMovieId());

    if (showtimeIndex < 0)
        return;

    vector<Showtime> availableShowtimes;

    for (const Showtime& item :
         showtimeManager.getByMovieId(
             selectedMovie.getMovieId()))
    {
        if (item.getStatus() != "Da huy")
            availableShowtimes.push_back(item);
    }

    if (showtimeIndex >=
        static_cast<int>(availableShowtimes.size()))
        return;

    const Showtime& showtime =
        availableShowtimes[showtimeIndex];

    const CinemaRoom* room =
        roomManager.findById(showtime.getRoomId());

    if (room == nullptr)
    {
        cout << "Phong khong ton tai.\n";
        pause();
        return;
    }

    input.clearScreen();

    cout << "\n>> Ban da chon Suat: "
         << showtime.getStartTime()
         << " (Phong: "
         << showtime.getRoomId() << ")\n";

    room->displaySeatLayout(
        bookingManager.getBookedSeats(
            showtime.getShowtimeId()));

    string seatInput = input.getLine(
        ">> Nhap Ma ghe (VD: A0, D3) hoac 0 de huy: ");

    if (seatInput == "0")
        return;

    BookingRequest request{
        customer.id,
        showtime.getShowtimeId(),
        "",
        {}
    };

    stringstream stream(seatInput);
    string seat;

    while (getline(stream, seat, ','))
    {
        seat = trimSeatInput(seat);

        if (!seat.empty())
            request.seatIds.push_back(seat);
    }

    string bookingId;
    string error;

    if (bookingManager.createBooking(
            request,
            showtimeManager,
            roomManager,
            bookingId,
            error))
    {
        const Booking* booking =
            bookingManager.findById(bookingId);

        const Movie* movie =
            movieManager.findById(showtime.getMovieId());

        if (booking != nullptr && movie != nullptr)
        {
            input.clearScreen();

            booking->displayInvoice(
                movie->getTitle(),
                showtime.getShowDate(),
                showtime.getStartTime(),
                showtime.getRoomId());
        }
    }
    else
    {
        cout << "Dat ve that bai: "
             << error << '\n';
    }

    pause();
}

int Menu::chooseMovieForBooking()
{
    vector<Movie> movies =
        movieManager.getByStatus("Dang chieu");

    cout << "\n--- KET QUA TIM KIEM ---\n";

    int index = 1;

    for (const Movie& movie : movies)
    {
        cout << "[" << index++ << "] "
             << movie.getTitle()
             << " | The loai: "
             << movie.getGenre()
             << " | "
             << movie.getDuration()
             << " phut\n";
    }

    cout << "[0] Huy bo va quay lai\n";

    if (movies.empty())
    {
        cout << "Khong co phim dang chieu.\n";
        pause();
        return -1;
    }

    int choice = input.getInt(
        ">> Chon phim ban muon xem (Nhap so): ",
        0,
        static_cast<int>(movies.size()));

    if (choice == 0)
        return -1;

    return choice - 1;
}

int Menu::chooseShowtimeForMovie(const string& movieId)
{
    vector<Showtime> showtimes =
        showtimeManager.getByMovieId(movieId);

    cout << "\n--- DANH SACH SUAT CHIEU ---\n";

    int index = 1;

    for (const Showtime& showtime : showtimes)
    {
        if (showtime.getStatus() == "Da huy")
            continue;

        cout << "[" << index++ << "] "
             << "Ma suat: "
             << showtime.getShowtimeId()
             << " | Ngay: "
             << showtime.getShowDate()
             << " | Gio: "
             << showtime.getStartTime()
             << " | Phong: "
             << showtime.getRoomId()
             << " | Gia ve: "
             << fixed << setprecision(0)
             << showtime.getBasePrice()
             << " VND\n";
    }

    cout << "[0] Huy bo va quay lai\n";

    vector<Showtime> available;

    for (const Showtime& showtime : showtimes)
    {
        if (showtime.getStatus() != "Da huy")
            available.push_back(showtime);
    }

    if (available.empty())
    {
        cout << "Khong co suat chieu dang hoat dong.\n";
        pause();
        return -1;
    }

    int choice = input.getInt(
        ">> Chon suat chieu (Nhap so): ",
        0,
        static_cast<int>(available.size()));

    if (choice == 0)
        return -1;

    return choice - 1;
}

void Menu::bookingAtCounter(
    const Account& operatorAccount)
{
    input.clearScreen();

    cout << "\n================ BAN VE TAI QUAY ================\n";
    cout << "Quy trinh: chon Customer -> chon phim -> chon suat chieu -> chon ghe.\n";

    cout << "\n";

    for (const Account& customer :
         accountManager.getCustomers())
    {
        cout << customer.id
             << " | "
             << customer.username
             << " | "
             << customer.fullName
             << " | "
             << customer.phone
             << '\n';
    }

    if (accountManager.getCustomers().empty())
    {
        cout << "Chua co Customer nao.\n";
        pause();
        return;
    }

    string customerId = upper(
        input.getLine("Nhap Customer ID: "));

    const Account* customer =
        accountManager.findById(customerId);

    if (customer == nullptr ||
        !AccountManager::isCustomer(*customer))
    {
        cout << "Customer khong ton tai.\n";
        pause();
        return;
    }

    int movieIndex = chooseMovieForBooking();

    if (movieIndex < 0)
        return;

    vector<Movie> movies =
        movieManager.getByStatus("Dang chieu");

    const Movie& selectedMovie =
        movies[movieIndex];

    cout << "\n>> DANG BAN VE CHO PHIM: "
         << selectedMovie.getTitle()
         << " <<\n";

    int showtimeIndex =
        chooseShowtimeForMovie(
            selectedMovie.getMovieId());

    if (showtimeIndex < 0)
        return;

    vector<Showtime> available;

    for (const Showtime& showtime :
         showtimeManager.getByMovieId(
             selectedMovie.getMovieId()))
    {
        if (showtime.getStatus() != "Da huy")
            available.push_back(showtime);
    }

    const Showtime& showtime =
        available[showtimeIndex];

    const CinemaRoom* room =
        roomManager.findById(showtime.getRoomId());

    if (room == nullptr)
    {
        cout << "Phong khong ton tai.\n";
        pause();
        return;
    }

    input.clearScreen();

    cout << ">> Ban da chon Suat: "
         << showtime.getStartTime()
         << " (Phong: "
         << showtime.getRoomId()
         << ")\n";

    room->displaySeatLayout(
        bookingManager.getBookedSeats(
            showtime.getShowtimeId()));

    string seatInput = input.getLine(
        ">> Nhap Ma ghe (VD: A0, D3) hoac 0 de huy: ");

    if (seatInput == "0")
        return;

    BookingRequest request{
        customerId,
        showtime.getShowtimeId(),
        operatorAccount.id,
        {}
    };

    stringstream stream(seatInput);
    string seat;

    while (getline(stream, seat, ','))
    {
        seat = trimSeatInput(seat);

        if (!seat.empty())
            request.seatIds.push_back(seat);
    }

    string bookingId;
    string error;

    if (bookingManager.createBooking(
            request,
            showtimeManager,
            roomManager,
            bookingId,
            error))
    {
        const Booking* booking =
            bookingManager.findById(bookingId);

        const Movie* movie =
            movieManager.findById(showtime.getMovieId());

        if (booking != nullptr && movie != nullptr)
        {
            input.clearScreen();

            booking->displayInvoice(
                movie->getTitle(),
                showtime.getShowDate(),
                showtime.getStartTime(),
                showtime.getRoomId());
        }
    }
    else
    {
        cout << "Ban ve that bai: "
             << error << '\n';
    }

    pause();
}

void Menu::lookupMoviesAndShowtimes()
{
    cout << "\n";
    cout << "1. Tat ca phim\n";
    cout << "2. Tim theo ten\n";
    cout << "3. Tim theo the loai\n";
    cout << "4. Xem lich cua phim\n";

    int choice = input.getInt(
        "Chon: ", 1, 4);

    if (choice == 1)
    {
        printMovies(movieManager.getItems());
    }
    else if (choice == 2)
    {
        printMovies(
            movieManager.searchByTitle(
                input.getLine("Tu khoa: ")));
    }
    else if (choice == 3)
    {
        printMovies(
            movieManager.searchByGenre(
                input.getLine("The loai: ")));
    }
    else
    {
        string movieId =
            input.getLine("Ma phim: ");

        printShowtimes(
            showtimeManager.getByMovieId(movieId));
    }

    pause();
}

void Menu::bookingHistory(
    const string& customerId)
{
    vector<Booking> bookings =
        bookingManager.getCustomerBookings(
            customerId);

    cout << "\n==================== LICH SU DAT VE ====================\n";

    if (bookings.empty())
    {
        cout << "Chua co lich su dat ve nao!\n";
        pause();
        return;
    }

    for (const Booking& booking : bookings)
    {
        string seats;

        for (size_t i = 0;
             i < booking.getTickets().size();
             ++i)
        {
            if (i > 0)
                seats += ", ";

            seats +=
                booking.getTickets()[i]->getSeatId();
        }

        cout << booking.getBookingId()
             << " | Customer: "
             << booking.getCustomerId()
             << " | Showtime: "
             << booking.getShowtimeId()
             << " | "
             << booking.getStatusText()
             << " | "
             << seats
             << " | "
             << fixed << setprecision(0)
             << booking.getTotal()
             << " VND\n";
    }

    pause();
}

void Menu::cancelBooking(
    const string& customerId,
    bool managerOrStaff)
{
    if (!managerOrStaff)
    {
        vector<Booking> bookings =
            bookingManager.getCustomerBookings(
                customerId);

        bool hasActiveBooking = false;

        cout << "\n================ BOOKING CO THE HUY ================\n";

        for (const Booking& item : bookings)
        {
            if (item.getStatus() ==
                BookingStatus::Cancelled)
                continue;

            hasActiveBooking = true;

            cout << item.getBookingId()
                 << " | Showtime: "
                 << item.getShowtimeId()
                 << " | Tong tien: "
                 << fixed << setprecision(0)
                 << item.getTotal()
                 << " VND\n";
        }

        if (!hasActiveBooking)
        {
            cout << "Khong co Booking nao co the huy.\n";
            pause();
            return;
        }
    }

    string bookingId =
        input.getLine("Ma Booking: ");

    const Booking* booking =
        bookingManager.findById(bookingId);

    if (booking == nullptr)
    {
        cout << "Khong tim thay Booking.\n";
        pause();
        return;
    }

    if (!managerOrStaff &&
        booking->getCustomerId() != customerId)
    {
        cout << "Customer chi duoc huy Booking cua chinh minh.\n";
        pause();
        return;
    }

    string error;

    if (bookingManager.cancelBooking(
            bookingId,
            showtimeManager,
            error))
    {
        cout << "Huy Booking thanh cong.\n";
    }
    else
    {
        cout << "Khong the huy: "
             << error << '\n';
    }

    pause();
}
