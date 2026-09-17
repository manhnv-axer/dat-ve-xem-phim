#include "Menu.h"
#include "InputHandler.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

namespace {
string roleText(Role role) {
    if (role == Role::Manager) return "Manager";
    if (role == Role::Staff) return "Staff";
    return "Customer";
}

string upper(string value) {
    transform(value.begin(), value.end(), value.begin(),
              [](unsigned char c) { return static_cast<char>(toupper(c)); });
    return value;
}
}

void Menu::pause() const {
    cout << "\nNhan Enter de tiep tuc...";
    string ignored;
    getline(cin, ignored);
}

void Menu::printMovies(const vector<Movie>& movies) const {
    cout << "\n================ DANH SACH PHIM ================\n";
    cout << left << setw(8) << "ID"
         << setw(28) << "TEN PHIM"
         << setw(20) << "THE LOAI"
         << right << setw(10) << "PHUT"
         << setw(8) << "TUOI"
         << "  " << left << setw(16) << "TRANG THAI" << '\n';
    cout << string(96, '-') << '\n';

    for (const Movie& movie : movies) {
        cout << left << setw(8) << movie.getMovieId()
             << setw(28) << movie.getTitle().substr(0, 27)
             << setw(20) << movie.getGenre().substr(0, 19)
             << right << setw(10) << movie.getDuration()
             << setw(8) << movie.getAgeLimit()
             << "  " << left << setw(16) << movie.getStatus().substr(0, 15) << '\n';
    }
    if (movies.empty()) cout << "Khong co du lieu.\n";
    cout << right;
}

void Menu::printShowtimes(const vector<Showtime>& showtimes) const {
    cout << "\n================ DANH SACH SHOWTIME ================\n";
    cout << left << setw(10) << "ID"
         << setw(10) << "PHIM"
         << setw(12) << "PHONG"
         << setw(14) << "NGAY"
         << setw(10) << "GIO"
         << setw(16) << "GIA"
         << "TRANG THAI\n";
    cout << string(82, '-') << '\n';

    for (const Showtime& showtime : showtimes) {
        cout << left << setw(10) << showtime.getShowtimeId()
             << setw(10) << showtime.getMovieId()
             << setw(12) << showtime.getRoomId()
             << setw(14) << showtime.getShowDate()
             << setw(10) << showtime.getStartTime()
             << setw(16) << fixed << setprecision(0) << showtime.getBasePrice()
             << showtime.getStatus() << '\n';
    }
    if (showtimes.empty()) cout << "Khong co du lieu.\n";
}

void Menu::printRooms() const {
    cout << "\n================ DANH SACH PHONG ================\n";
    cout << left << setw(10) << "ID"
         << setw(28) << "TEN PHONG"
         << setw(10) << "DONG"
         << setw(10) << "COT"
         << "SO GHE\n";
    cout << string(70, '-') << '\n';
    for (const CinemaRoom& room : roomManager.getItems()) {
        cout << left << setw(10) << room.getRoomId()
             << setw(28) << room.getRoomName().substr(0, 27)
             << setw(10) << room.getRowCount()
             << setw(10) << room.getColCount()
             << room.getSeats().size() << '\n';
    }
    if (roomManager.getItems().empty()) cout << "Khong co phong.\n";
}

void Menu::run() {
    loginMenu();
}

void Menu::loginMenu() {
    while (true) {
        InputHandler::clearScreen();
        cout << "\n====================================================\n";
        cout << "           HE THONG QUAN LY BAN VE CINEMA\n";
        cout << "====================================================\n";
        cout << "1. Dang nhap\n";
        cout << "2. Dang ky Customer\n";
        cout << "0. Thoat\n";

        const int choice = InputHandler::getInt("Chon: ", 0, 2);
        if (choice == 0) {
            return;
        }

        if (choice == 2) {
            string username;
            do {
                username = InputHandler::getLine("Username: ");
                if (!AccountManager::validUsername(username)) {
                    cout << "Loi: Username phai dai 3-20 ky tu, chi gom chu, so va dau _.\n";
                } else if (accountManager.usernameExists(username)) {
                    cout << "Loi: Username da ton tai. Vui long chon username khac.\n";
                }
            } while (!AccountManager::validUsername(username) ||
                     accountManager.usernameExists(username));

            string password;
            do {
                password = InputHandler::getPassword("Password: ");
                if (!AccountManager::validPassword(password)) {
                    cout << "Loi: Password phai co it nhat 6 ky tu.\n";
                }
            } while (!AccountManager::validPassword(password));

            string confirmPassword;
            do {
                confirmPassword = InputHandler::getPassword("Nhap lai Password: ");
                if (password != confirmPassword) {
                    cout << "Loi: Password nhap lai khong khop.\n";
                }
            } while (password != confirmPassword);

            const string name = InputHandler::getLine("Ho ten: ");
            string phone;
            do {
                phone = InputHandler::getLine("So dien thoai: ");
                if (!AccountManager::validPhone(phone)) {
                    cout << "Loi: So dien thoai phai gom 10 hoac 11 chu so va bat dau bang 0.\n";
                }
            } while (!AccountManager::validPhone(phone));

            string email;
            do {
                email = InputHandler::getLine("Email: ");
                if (!AccountManager::validEmail(email)) {
                    cout << "Loi: Email khong dung dinh dang.\n";
                }
            } while (!AccountManager::validEmail(email));
            string error;
            if (accountManager.registerCustomer(username, password, name, phone, email, error)) {
                cout << "Dang ky Customer thanh cong. Vui long dang nhap.\n";
                pause();
            } else {
                cout << "Loi: " << error << '\n';
                pause();
            }
            continue;
        }

        const Account* account = nullptr;
        while (account == nullptr) {
            const string username = InputHandler::getLine("Username: ");
            if (!AccountManager::validUsername(username)) {
                cout << "Loi: Username khong duoc de trong, dai 3-20 ky tu, chi gom chu, so va dau _.\n";
                continue;
            }
            if (!accountManager.usernameExists(username)) {
                cout << "Loi: Username khong ton tai trong he thong. Vui long nhap lai.\n";
                continue;
            }
            const string password = InputHandler::getPassword("Password: ");
            account = accountManager.authenticate(username, password);

            if (account == nullptr) {
                cout << "Sai username/password. Vui long nhap lai.\n";
            } else if (!account->active) {
                cout << "Tai khoan dang bi khoa. Vui long nhap lai.\n";
                account = nullptr;
            }
        }

        cout << "Dang nhap thanh cong: " << account->fullName
             << " (" << roleText(AccountManager::getRole(*account)) << ")\n";

        if (AccountManager::isManager(*account)) {
            managerMenu(*account);
        } else if (AccountManager::isStaff(*account)) {
            staffMenu(*account);
        } else {
            customerMenu(*account);
        }
    }
}

void Menu::customerMenu(const Account& account) {
    while (true) {
        InputHandler::clearScreen();
        cout << "\n---------------- CUSTOMER ----------------\n";
        cout << "1. Dat nhieu ghe trong mot Booking\n";
        cout << "2. Tra cuu phim va lich chieu\n";
        cout << "3. Xem Booking cua toi\n";
        cout << "4. Huy Booking (>= 30 phut truoc gio chieu)\n";
        cout << "0. Dang xuat\n";

        const int choice = InputHandler::getInt("Chon: ", 0, 4);
        if (choice == 0) return;
        if (choice == 1) bookingOnline(account);
        if (choice == 2) lookupMoviesAndShowtimes();
        if (choice == 3) bookingHistory(account.id);
        if (choice == 4) cancelBooking(account.id, false);
    }
}

void Menu::staffMenu(const Account& account) {
    while (true) {
        InputHandler::clearScreen();
        cout << "\n---------------- STAFF ----------------\n";
        cout << "1. Ban ve tai quay\n";
        cout << "2. Tra cuu phim/lich chieu\n";
        cout << "3. Xem Booking\n";
        cout << "4. Huy Booking\n";
        cout << "5. Xem danh sach Customer\n";
        cout << "0. Dang xuat\n";

        const int choice = InputHandler::getInt("Chon: ", 0, 5);
        if (choice == 0) return;
        if (choice == 1) bookingAtCounter(account);
        if (choice == 2) lookupMoviesAndShowtimes();
        if (choice == 3) {
            const string id = InputHandler::getLine("Customer ID: ");
            bookingHistory(id);
        }
        if (choice == 4) cancelBooking("", true);
        if (choice == 5) {
            vector<Account> customers = accountManager.getCustomers();
            for (const Account& customer : customers) {
                cout << customer.id << " | " << customer.fullName
                     << " | " << customer.phone << '\n';
            }
            pause();
        }
    }
}

void Menu::managerMenu(const Account& account) {
    Roles::Manager managerObject(account.id, account.fullName, account.phone, account.email);
    cout << "Quyen Manager: quan ly Staff, phim, suat chieu, phong, Customer, thong ke.\n";

    while (true) {
        InputHandler::clearScreen();
        cout << "\n================ MANAGER ================\n";
        cout << "1. Quan ly Staff (tao/khoa/mo khoa)\n";
        cout << "2. Quan ly phim\n";
        cout << "3. Quan ly Showtime\n";
        cout << "4. Quan ly phong + so do ghe\n";
        cout << "5. Quan ly Customer\n";
        cout << "6. Ban ve tai quay\n";
        cout << "7. Tra cuu phim/lich chieu\n";
        cout << "8. Thong ke\n";
        cout << "9. Xem tat ca Booking\n";
        cout << "0. Dang xuat\n";

        const int choice = InputHandler::getInt("Chon: ", 0, 9);
        if (choice == 0) return;
        if (choice == 1) staffAccountMenu();
        if (choice == 2) movieMenu();
        if (choice == 3) showtimeMenu();
        if (choice == 4) roomMenu();
        if (choice == 5) customerManagementMenu();
        if (choice == 6) bookingAtCounter(account);
        if (choice == 7) lookupMoviesAndShowtimes();
        if (choice == 8) statisticsMenu();
        if (choice == 9) {
            for (const Booking& booking : bookingManager.getItems()) {
                cout << booking.getBookingId() << " | Customer: "
                     << booking.getCustomerId() << " | Showtime: "
                     << booking.getShowtimeId() << " | "
                     << booking.getStatusText() << " | "
                     << fixed << setprecision(0) << booking.getTotal() << " VND\n";
            }
            pause();
        }
    }
}

void Menu::staffAccountMenu() {
    while (true) {
        cout << "\n---------- QUAN LY STAFF (CHI MANAGER) ----------\n";
        cout << "1. Tao Staff\n2. Khoa Staff\n3. Mo khoa Staff\n4. Danh sach Staff\n0. Quay lai\n";
        const int choice = InputHandler::getInt("Chon: ", 0, 4);
        if (choice == 0) return;

        if (choice == 1) {
            string error;
            string username;
            do {
                username = InputHandler::getLine("Username: ");
                if (!AccountManager::validUsername(username)) {
                    cout << "Loi: Username phai dai 3-20 ky tu, chi gom chu, so va dau _.\n";
                } else if (accountManager.usernameExists(username)) {
                    cout << "Loi: Username da ton tai. Vui long chon username khac.\n";
                }
            } while (!AccountManager::validUsername(username) ||
                     accountManager.usernameExists(username));

            string password;
            do {
                password = InputHandler::getPassword("Password: ");
                if (!AccountManager::validPassword(password)) {
                    cout << "Loi: Password phai co it nhat 6 ky tu.\n";
                }
            } while (!AccountManager::validPassword(password));

            string confirmPassword;
            do {
                confirmPassword = InputHandler::getPassword("Nhap lai Password: ");
                if (password != confirmPassword) {
                    cout << "Loi: Password nhap lai khong khop.\n";
                }
            } while (password != confirmPassword);

            const string name = InputHandler::getLine("Ho ten: ");
            string phone;
            do {
                phone = InputHandler::getLine("SDT: ");
                if (!AccountManager::validPhone(phone)) {
                    cout << "Loi: So dien thoai phai gom 10 hoac 11 chu so va bat dau bang 0.\n";
                }
            } while (!AccountManager::validPhone(phone));

            string email;
            do {
                email = InputHandler::getLine("Email: ");
                if (!AccountManager::validEmail(email)) {
                    cout << "Loi: Email khong dung dinh dang.\n";
                }
            } while (!AccountManager::validEmail(email));
            if (accountManager.createStaff(username, password, name, phone, email, error)) {
                cout << "Tao Staff thanh cong.\n";
            } else {
                cout << "Loi: " << error << '\n';
            }
        } else if (choice == 2 || choice == 3) {
            const string id = InputHandler::getLine("Staff ID: ");
            string error;
            if (accountManager.setStaffStatus(id, choice == 3, error)) {
                cout << (choice == 2 ? "Da khoa Staff.\n" : "Da mo khoa Staff.\n");
            } else {
                cout << "Loi: " << error << '\n';
            }
        } else {
            // Danh sach Staff duoc hien thi ben duoi.
        }

        cout << "\n---------------- DANH SACH STAFF ----------------\n";
        cout << left << setw(8) << "ID" << setw(18) << "USERNAME"
             << setw(26) << "HO TEN" << setw(12) << "TRANG THAI" << '\n';
        cout << string(64, '-') << '\n';
        for (const Account& staff : accountManager.getStaff()) {
            cout << left << setw(8) << staff.id << setw(18) << staff.username
                 << setw(26) << staff.fullName.substr(0, 25)
                 << (staff.active ? "Active" : "Locked") << '\n';
        }
        pause();
    }
}

void Menu::movieMenu() {
    while (true) {
        cout << "\n---------- QUAN LY PHIM ----------\n";
        cout << "1. Them\n2. Sua\n3. Xoa\n4. Doi trang thai\n5. Xem\n0. Quay lai\n";
        const int choice = InputHandler::getInt("Chon: ", 0, 5);
        if (choice == 0) return;

        string error;
        if (choice == 1) {
            const string id = InputHandler::getLine("Ma phim (VD M11): ");
            const string title = InputHandler::getLine("Ten phim: ");
            const string genre = InputHandler::getLine("The loai: ");
            const int duration = InputHandler::getInt("Thoi luong: ", 1, 1000);
            const int age = InputHandler::getInt("Do tuoi: ", 0, 100);
            const string status = InputHandler::getLine("Trang thai: ");
            movieManager.addMovie(Movie(id, title, duration, genre, age, status), error);
        } else if (choice == 2) {
            printMovies(movieManager.getItems());
            const string id = InputHandler::getLine("Ma phim: ");
            const string title = InputHandler::getLine("Ten moi: ");
            const int duration = InputHandler::getInt("Thoi luong moi: ", 1, 1000);
            const string genre = InputHandler::getLine("The loai moi: ");
            const int age = InputHandler::getInt("Do tuoi moi: ", 0, 100);
            movieManager.updateMovie(id, title, duration, genre, age, error);
        } else if (choice == 3) {
            printMovies(movieManager.getItems());
            movieManager.deleteMovie(InputHandler::getLine("Ma phim: "), error);
        } else if (choice == 4) {
            printMovies(movieManager.getItems());
            const string id = InputHandler::getLine("Ma phim: ");
            const string status = InputHandler::getLine("Trang thai moi: ");
            movieManager.setStatus(id, status, error);
        } else {
            printMovies(movieManager.getItems());
        }

        if (!error.empty()) {
            cout << "Loi: " << error << '\n';
        } else if (choice != 5) {
            cout << "Thuc hien thanh cong.\n";
            printMovies(movieManager.getItems());
        }
        pause();
    }
}

void Menu::showtimeMenu() {
    while (true) {
        cout << "\n---------- QUAN LY SHOWTIME ----------\n";
        cout << "1. Them\n2. Sua\n3. Huy\n4. Xoa\n5. Xem\n0. Quay lai\n";
        const int choice = InputHandler::getInt("Chon: ", 0, 5);
        if (choice == 0) return;

        string error;
        if (choice == 1) {
            const string id = InputHandler::getLine("Ma Showtime (VD ST31): ");
            const string movieId = InputHandler::getLine("Ma phim: ");
            const string roomId = InputHandler::getLine("Ma phong: ");
            const string date = InputHandler::getLine("Ngay YYYY-MM-DD: ");
            const string time = InputHandler::getLine("Gio HH:MM: ");
            const double price = InputHandler::getDouble("Gia co ban: ", 0);
            showtimeManager.addShowtime(Showtime(id, movieId, roomId, date, time, price), error);
        } else if (choice == 2) {
            printShowtimes(showtimeManager.getItems());
            const string id = InputHandler::getLine("Ma Showtime: ");
            const string movieId = InputHandler::getLine("Ma phim: ");
            const string roomId = InputHandler::getLine("Ma phong: ");
            const string date = InputHandler::getLine("Ngay: ");
            const string time = InputHandler::getLine("Gio: ");
            const double price = InputHandler::getDouble("Gia: ", 0);
            showtimeManager.updateShowtime(id, movieId, roomId, date, time, price, error);
        } else if (choice == 3) {
            printShowtimes(showtimeManager.getItems());
            showtimeManager.cancelShowtime(InputHandler::getLine("Ma Showtime: "), error);
        } else if (choice == 4) {
            printShowtimes(showtimeManager.getItems());
            showtimeManager.deleteShowtime(InputHandler::getLine("Ma Showtime: "), error);
        } else {
            printShowtimes(showtimeManager.getItems());
        }

        if (!error.empty()) {
            cout << "Loi: " << error << '\n';
        } else if (choice != 5) {
            cout << "Thuc hien thanh cong.\n";
            printShowtimes(showtimeManager.getItems());
        }
        pause();
    }
}

void Menu::roomMenu() {
    while (true) {
        cout << "\n---------- QUAN LY PHONG + GHE ----------\n";
        cout << "1. Tao phong (dong x cot)\n2. Sua kich thuoc\n3. Gan VIP ghe\n4. Bo VIP ghe\n5. Khoa ghe bao tri\n6. Mo khoa ghe\n7. Xem so do\n8. Xoa phong\n0. Quay lai\n";
        const int choice = InputHandler::getInt("Chon: ", 0, 8);
        if (choice == 0) return;

        string error;
        if (choice == 1) {
            printRooms();
            const string name = InputHandler::getLine("Ten phong: ");
            const int rows = InputHandler::getInt("So dong (1-26): ", 1, 26);
            const int cols = InputHandler::getInt("So cot (1-30): ", 1, 30);
            string newId;
            if (roomManager.createRoom(name, rows, cols, newId, error)) {
                cout << "Tao phong thanh cong: " << newId << '\n';
            }
        } else if (choice == 2) {
            printRooms();
            const string id = InputHandler::getLine("Ma phong: ");
            const string name = InputHandler::getLine("Ten phong moi: ");
            const int rows = InputHandler::getInt("So dong: ", 1, 26);
            const int cols = InputHandler::getInt("So cot: ", 1, 30);
            roomManager.updateRoom(id, name, rows, cols, error);
        } else if (choice >= 3 && choice <= 6) {
            printRooms();
            const string roomId = InputHandler::getLine("Ma phong: ");
            const string seatId = upper(InputHandler::getLine("Ma ghe (VD A0): "));
            if (choice == 3) roomManager.setSeatVIP(roomId, seatId, true, error);
            if (choice == 4) roomManager.setSeatVIP(roomId, seatId, false, error);
            if (choice == 5) roomManager.setSeatMaintenance(roomId, seatId, true, error);
            if (choice == 6) roomManager.setSeatMaintenance(roomId, seatId, false, error);
        } else if (choice == 7) {
            // Khi xem so do, hien danh sach phong truoc de nguoi dung chon
            // bang so thu tu, sau do moi hien so do ghe cua phong da chon.
            printRooms();

            const vector<CinemaRoom>& rooms = roomManager.getItems();
            if (rooms.empty()) {
                error = "Chua co phong nao.";
            } else {
                const int roomIndex = InputHandler::getInt(
                    "Chon phong (Nhap so): ", 0, static_cast<int>(rooms.size()));

                if (roomIndex == 0) {
                    cout << "Da huy xem so do.\n";
                } else {
                    const CinemaRoom& room = rooms[roomIndex - 1];
                    cout << "\n>> Ban da chon phong: " << room.getRoomId()
                         << " - " << room.getRoomName() << "\n";
                    room.displaySeatLayout();
                }
            }
        } else if (choice == 8) {
            printRooms();
            roomManager.deleteRoom(InputHandler::getLine("Ma phong: "), error);
        }

        if (!error.empty()) {
            cout << "Loi: " << error << '\n';
        } else if (choice != 7 || error.empty()) {
            cout << "Thuc hien thanh cong.\n";
            if (choice != 7) {
                printRooms();
            }
        }
        pause();
    }
}

void Menu::customerManagementMenu() {
    while (true) {
        cout << "\n---------- QUAN LY CUSTOMER ----------\n";
        cout << "1. Danh sach\n2. Tim kiem\n3. Sua thong tin\n4. Xoa\n0. Quay lai\n";
        const int choice = InputHandler::getInt("Chon: ", 0, 4);
        if (choice == 0) return;

        string error;
        if (choice == 1 || choice == 2) {
            const string key = choice == 2 ? InputHandler::getLine("Tu khoa: ") : "";
            const vector<Account> customers = accountManager.searchCustomers(key);
            cout << "\n" << left << setw(8) << "ID" << setw(18) << "USERNAME"
                 << setw(26) << "HO TEN" << setw(15) << "SDT" << "EMAIL\n";
            cout << string(90, '-') << '\n';
            for (const Account& customer : customers) {
                cout << left << setw(8) << customer.id
                     << setw(18) << customer.username
                     << setw(26) << customer.fullName.substr(0, 25)
                     << setw(15) << customer.phone << customer.email << '\n';
            }
        } else if (choice == 3) {
            const string id = InputHandler::getLine("Customer ID: ");
            const string name = InputHandler::getLine("Ho ten moi: ");
            const string phone = InputHandler::getLine("SDT moi: ");
            const string email = InputHandler::getLine("Email moi: ");
            accountManager.updateCustomer(id, name, phone, email, error);
        } else {
            accountManager.deleteCustomer(InputHandler::getLine("Customer ID: "), error);
        }

        if (!error.empty()) cout << "Loi: " << error << '\n';
        else if (choice >= 3) cout << "Thuc hien thanh cong.\n";

           if (choice >= 3) {
              cout << "\n---------------- DANH SACH CUSTOMER ----------------\n";
              cout << left << setw(8) << "ID" << setw(18) << "USERNAME"
                  << setw(26) << "HO TEN" << setw(15) << "SDT" << "EMAIL\n";
              cout << string(90, '-') << '\n';
              for (const Account& customer : accountManager.getCustomers()) {
                 cout << left << setw(8) << customer.id << setw(18) << customer.username
                     << setw(26) << customer.fullName.substr(0, 25)
                     << setw(15) << customer.phone << customer.email << '\n';
              }
        }
        pause();
    }
}

string trimSeatInput(string value);

void Menu::bookingOnline(const Account& customer) {
    InputHandler::clearScreen();

    const int movieIndex = chooseMovieForBooking();
    if (movieIndex < 0) {
        return;
    }

    const vector<Movie> movies = movieManager.getByStatus("Dang chieu");
    if (movieIndex >= static_cast<int>(movies.size())) {
        return;
    }

    const Movie& selectedMovie = movies[movieIndex];
    cout << "\n=======================================================\n";
    cout << ">> DANG DAT VE CHO PHIM: " << selectedMovie.getTitle() << " <<\n";

    const int showtimeIndex = chooseShowtimeForMovie(selectedMovie.getMovieId());
    if (showtimeIndex < 0) {
        return;
    }

    vector<Showtime> availableShowtimes;
    for (const Showtime& item : showtimeManager.getByMovieId(selectedMovie.getMovieId())) {
        if (item.getStatus() != "Da huy") {
            availableShowtimes.push_back(item);
        }
    }
    if (showtimeIndex >= static_cast<int>(availableShowtimes.size())) {
        return;
    }

    const Showtime& showtime = availableShowtimes[showtimeIndex];
    const CinemaRoom* room = roomManager.findById(showtime.getRoomId());
    if (room == nullptr) {
        cout << "Phong khong ton tai.\n";
        pause();
        return;
    }

    InputHandler::clearScreen();
    cout << "\n>> Ban da chon Suat: " << showtime.getStartTime()
         << " (Phong: " << showtime.getRoomId() << ")\n";
    room->displaySeatLayout(bookingManager.getBookedSeats(showtime.getShowtimeId()));

    const string input = InputHandler::getLine(
        ">> Nhap Ma ghe ban muon ngoi (VD: A0, D3) hoac go '0' de huy: ");
    if (input == "0") {
        return;
    }

    BookingRequest request{customer.id, showtime.getShowtimeId(), "", {}};
    stringstream stream(input);
    string seat;
    while (getline(stream, seat, ',')) {
        seat = trimSeatInput(seat);
        if (!seat.empty()) {
            request.seatIds.push_back(seat);
        }
    }

    string bookingId;
    string error;
    if (bookingManager.createBooking(request, showtimeManager, roomManager, bookingId, error)) {
        const Booking* booking = bookingManager.findById(bookingId);
        const Movie* movie = movieManager.findById(showtime.getMovieId());
        if (booking != nullptr && movie != nullptr) {
            InputHandler::clearScreen();
            booking->displayInvoice(movie->getTitle(), showtime.getShowDate(),
                                    showtime.getStartTime(), showtime.getRoomId());
        }
    } else {
        cout << "Dat ve that bai: " << error << '\n';
    }
    pause();
}

int Menu::chooseMovieForBooking() {
    const vector<Movie> movies = movieManager.getByStatus("Dang chieu");

    cout << "\n--- KET QUA TIM KIEM ---\n";
    int index = 1;
    for (const Movie& movie : movies) {
        cout << "[" << index++ << "] " << movie.getTitle()
             << " | The loai: " << movie.getGenre()
             << " | " << movie.getDuration() << " phut\n";
    }
    cout << "[0] Huy bo va quay lai\n";

    if (movies.empty()) {
        cout << "Khong co phim dang chieu.\n";
        pause();
        return -1;
    }

    const int choice = InputHandler::getInt(">> Chon phim ban muon xem (Nhap so): ",
                                            0, static_cast<int>(movies.size()));
    if (choice == 0) {
        return -1;
    }
    return choice - 1;
}

int Menu::chooseShowtimeForMovie(const string& movieId) {
    const vector<Showtime> showtimes = showtimeManager.getByMovieId(movieId);

    cout << "\n--- DANH SACH SUAT CHIEU ---\n";
    int index = 1;
    for (const Showtime& showtime : showtimes) {
        if (showtime.getStatus() == "Da huy") {
            continue;
        }
        cout << "[" << index++ << "] Ma suat: " << showtime.getShowtimeId()
             << " | Ngay: " << showtime.getShowDate()
             << " | Gio: " << showtime.getStartTime()
             << " | Phong: " << showtime.getRoomId()
             << " | Gia ve co ban: " << fixed << setprecision(0)
             << showtime.getBasePrice() << " VND\n";
    }
    cout << "[0] Huy bo va quay lai\n";

    vector<Showtime> available;
    for (const Showtime& showtime : showtimes) {
        if (showtime.getStatus() != "Da huy") {
            available.push_back(showtime);
        }
    }

    if (available.empty()) {
        cout << "Khong co suat chieu dang hoat dong cho phim nay.\n";
        pause();
        return -1;
    }

    const int choice = InputHandler::getInt(">> Chon suat chieu (Nhap so): ",
                                            0, static_cast<int>(available.size()));
    if (choice == 0) {
        return -1;
    }

    // getByMovieId co the chua ca Showtime da huy, nen tra ve vi tri trong
    // danh sach da loc. bookingOnline se lay lai cung tap available.
    const Showtime& selected = available[choice - 1];
    const vector<Showtime> all = showtimeManager.getByMovieId(movieId);
    for (size_t i = 0; i < all.size(); ++i) {
        if (all[i].getShowtimeId() == selected.getShowtimeId()) {
            int availableIndex = 0;
            for (size_t j = 0; j <= i; ++j) {
                if (all[j].getStatus() != "Da huy") {
                    ++availableIndex;
                }
            }
            return availableIndex - 1;
        }
    }
    return -1;
}

string trimSeatInput(string value) {
    const size_t first = value.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }
    const size_t last = value.find_last_not_of(" \t\r\n");
    value = value.substr(first, last - first + 1);
    transform(value.begin(), value.end(), value.begin(),
              [](unsigned char c) { return static_cast<char>(toupper(c)); });
    return value;
}

void Menu::bookingAtCounter(const Account& operatorAccount) {
    InputHandler::clearScreen();

    cout << "\n================ BAN VE TAI QUAY ================\n";
    cout << "Quy trinh: chon Customer -> chon phim -> chon suat chieu -> chon ghe.\n";
    cout << "Nhap Customer ID tu danh sach ben duoi.\n\n";
    cout << left << setw(12) << "CUSTOMER ID"
         << setw(20) << "USERNAME"
         << setw(28) << "HO TEN"
         << setw(16) << "SDT" << "EMAIL\n";
    cout << string(90, '-') << '\n';
    for (const Account& customer : accountManager.getCustomers()) {
        cout << left << setw(12) << customer.id
             << setw(20) << customer.username
             << setw(28) << customer.fullName.substr(0, 27)
             << setw(16) << customer.phone << customer.email << '\n';
    }
    if (accountManager.getCustomers().empty()) {
        cout << "Chua co Customer nao.\n";
        pause();
        return;
    }
    cout << string(90, '-') << '\n';

    const string customerId = upper(InputHandler::getLine("Nhap Customer ID: "));
    const Account* customer = accountManager.findById(customerId);
    if (customer == nullptr || !AccountManager::isCustomer(*customer)) {
        cout << "Customer khong ton tai.\n";
        pause();
        return;
    }

    cout << "\n--- BAN VE TAI QUAY ---\n";
    const int movieIndex = chooseMovieForBooking();
    if (movieIndex < 0) {
        return;
    }

    const vector<Movie> movies = movieManager.getByStatus("Dang chieu");
    const Movie& selectedMovie = movies[movieIndex];
    cout << "\n>> DANG BAN VE CHO PHIM: " << selectedMovie.getTitle() << " <<\n";

    const int showtimeIndex = chooseShowtimeForMovie(selectedMovie.getMovieId());
    if (showtimeIndex < 0) {
        return;
    }

    vector<Showtime> available;
    for (const Showtime& showtime : showtimeManager.getByMovieId(selectedMovie.getMovieId())) {
        if (showtime.getStatus() != "Da huy") {
            available.push_back(showtime);
        }
    }
    const Showtime& showtime = available[showtimeIndex];

    const CinemaRoom* room = roomManager.findById(showtime.getRoomId());
    if (room == nullptr) {
        cout << "Phong khong ton tai.\n";
        pause();
        return;
    }

    InputHandler::clearScreen();
    cout << ">> Ban da chon Suat: " << showtime.getStartTime()
         << " (Phong: " << showtime.getRoomId() << ")\n";
    room->displaySeatLayout(bookingManager.getBookedSeats(showtime.getShowtimeId()));

    const string input = InputHandler::getLine(
        ">> Nhap Ma ghe ban muon ngoi (VD: A0, D3) hoac go '0' de huy: ");
    if (input == "0") {
        return;
    }

    BookingRequest request{customerId, showtime.getShowtimeId(), operatorAccount.id, {}};
    stringstream stream(input);
    string seat;
    while (getline(stream, seat, ',')) {
        seat = trimSeatInput(seat);
        if (!seat.empty()) {
            request.seatIds.push_back(seat);
        }
    }

    string bookingId;
    string error;
    if (bookingManager.createBooking(request, showtimeManager, roomManager, bookingId, error)) {
        const Booking* booking = bookingManager.findById(bookingId);
        const Movie* movie = movieManager.findById(showtime.getMovieId());
        if (booking != nullptr && movie != nullptr) {
            InputHandler::clearScreen();
            booking->displayInvoice(movie->getTitle(), showtime.getShowDate(),
                                    showtime.getStartTime(), showtime.getRoomId());
        }
    } else {
        cout << "Ban ve that bai: " << error << '\n';
    }
    pause();
}

void Menu::lookupMoviesAndShowtimes() {
    cout << "\n1. Tat ca phim\n2. Tim theo ten\n3. Tim theo the loai\n4. Xem lich cua phim\n";
    const int choice = InputHandler::getInt("Chon: ", 1, 4);
    if (choice == 1) {
        printMovies(movieManager.getItems());
    } else if (choice == 2) {
        printMovies(movieManager.searchByTitle(InputHandler::getLine("Tu khoa: ")));
    } else if (choice == 3) {
        printMovies(movieManager.searchByGenre(InputHandler::getLine("The loai: ")));
    } else {
        const string movieId = InputHandler::getLine("Ma phim: ");
        printShowtimes(showtimeManager.getByMovieId(movieId));
    }
    pause();
}

void Menu::bookingHistory(const string& customerId) {
    const vector<Booking> bookings = bookingManager.getCustomerBookings(customerId);

    cout << "\n==================== LICH SU DAT VE ====================\n";
    cout << left << setw(10) << "BOOKING"
         << setw(12) << "CUSTOMER"
         << setw(12) << "SHOWTIME"
         << setw(12) << "TRANG THAI"
         << setw(21) << "TAO LUC"
         << setw(22) << "GHE"
         << right << setw(15) << "TONG TIEN" << '\n';
    cout << string(104, '-') << '\n';

    if (bookings.empty()) {
        cout << "Chua co lich su dat ve nao!\n";
        cout << string(104, '-') << '\n';
        pause();
        return;
    }

    for (const Booking& booking : bookings) {
        string seats;
        for (size_t i = 0; i < booking.getTickets().size(); ++i) {
            if (i > 0) seats += ", ";
            seats += booking.getTickets()[i]->getSeatId();
        }
        if (seats.size() > 20) seats = seats.substr(0, 17) + "...";

        cout << left << setw(10) << booking.getBookingId()
             << setw(12) << booking.getCustomerId()
             << setw(12) << booking.getShowtimeId()
             << setw(12) << booking.getStatusText()
             << setw(21) << booking.getCreatedAt()
             << setw(22) << seats
             << right << setw(15) << fixed << setprecision(0)
             << booking.getTotal() << " VND\n";
    }
    cout << right;
    cout << string(104, '-') << '\n';
    pause();
}

void Menu::cancelBooking(const string& customerId, bool managerOrStaff) {
    if (!managerOrStaff) {
        const vector<Booking> bookings = bookingManager.getCustomerBookings(customerId);
        bool hasActiveBooking = false;

        cout << "\n================ BOOKING CO THE HUY ================\n";
        cout << left << setw(12) << "BOOKING"
             << setw(12) << "SHOWTIME"
             << setw(24) << "GHE"
             << right << setw(15) << "TONG TIEN" << '\n';
        cout << string(63, '-') << '\n';

        for (const Booking& item : bookings) {
            if (item.getStatus() == BookingStatus::Cancelled) {
                continue;
            }

            hasActiveBooking = true;
            string seats;
            for (size_t index = 0; index < item.getTickets().size(); ++index) {
                if (index > 0) seats += ", ";
                seats += item.getTickets()[index]->getSeatId();
            }
            cout << left << setw(12) << item.getBookingId()
                 << setw(12) << item.getShowtimeId()
                 << setw(24) << seats.substr(0, 23)
                 << right << setw(15) << fixed << setprecision(0)
                 << item.getTotal() << " VND\n";
        }

        if (!hasActiveBooking) {
            cout << "Khong co Booking nao co the huy.\n";
            pause();
            return;
        }
        cout << string(63, '-') << '\n';
    }

    const string bookingId = InputHandler::getLine("Ma Booking: ");
    const Booking* booking = bookingManager.findById(bookingId);
    if (booking == nullptr) {
        cout << "Khong tim thay Booking.\n";
        pause();
        return;
    }
    if (!managerOrStaff && booking->getCustomerId() != customerId) {
        cout << "Customer chi duoc huy Booking cua chinh minh.\n";
        pause();
        return;
    }

    string error;
    if (bookingManager.cancelBooking(bookingId, showtimeManager, error)) {
        cout << "Huy Booking thanh cong.\n";
    } else {
        cout << "Khong the huy: " << error << '\n';
    }
    pause();
}

void Menu::statisticsMenu() {
    while (true) {
        InputHandler::clearScreen();
        cout << "\n================ THONG KE DOANH THU ================\n";
        cout << "1. Doanh thu theo ngay\n";
        cout << "2. Doanh thu theo thang\n";
        cout << "3. Doanh thu theo nam\n";
        cout << "4. Tong Booking / tong ve da ban\n";
        cout << "5. Doanh thu theo phim\n";
        cout << "0. Quay lai\n";

        const int choice = InputHandler::getInt("Chon: ", 0, 5);
        if (choice == 0) {
            return;
        }

        if (choice == 1) {
            const string date = InputHandler::getLine("Nhap ngay (YYYY-MM-DD): ");
            cout << "\nDoanh thu ngay " << date << ": "
                 << fixed << setprecision(0)
                 << bookingManager.revenueOnDate(date) << " VND\n";
        } else if (choice == 2) {
            const string month = InputHandler::getLine("Nhap thang (YYYY-MM): ");
            cout << "\nDoanh thu thang " << month << ": "
                 << fixed << setprecision(0)
                 << bookingManager.revenueInMonth(month) << " VND\n";
        } else if (choice == 3) {
            const string year = InputHandler::getLine("Nhap nam (YYYY): ");
            cout << "\nDoanh thu nam " << year << ": "
                 << fixed << setprecision(0)
                 << bookingManager.revenueInYear(year) << " VND\n";
        } else if (choice == 4) {
            cout << "\nTong Booking da thanh toan : " << bookingManager.totalPaidBookings() << '\n';
            cout << "Tong ve da ban             : " << bookingManager.totalPaidTickets() << '\n';
        } else if (choice == 5) {
            cout << "\n================ DOANH THU THEO PHIM ================\n";
            cout << left << setw(8) << "STT" << setw(12) << "MA PHIM"
                 << setw(40) << "TEN PHIM" << right << setw(20) << "DOANH THU" << '\n';
            cout << string(80, '-') << '\n';

            const vector<pair<string, double>> ranking = bookingManager.revenueByMovie(showtimeManager);
            int index = 1;
            for (const auto& entry : ranking) {
                const Movie* movie = movieManager.findById(entry.first);
                cout << left << setw(8) << index++ << setw(12) << entry.first
                     << setw(40) << (movie == nullptr ? "Khong tim thay" : movie->getTitle().substr(0, 39))
                     << right << setw(20) << fixed << setprecision(0) << entry.second << " VND\n";
            }
            if (ranking.empty()) {
                cout << "Chua co doanh thu.\n";
            }
        }
        cout << right;
        pause();
    }
}
