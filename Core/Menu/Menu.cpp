#include "Menu.h"

#include <cctype>

using namespace std;

string Menu::roleText(Role role) const
{
    if (role == Role::Manager)
        return "Manager";

    if (role == Role::Staff)
        return "Staff";

    return "Customer";
}

string Menu::upper(string value) const
{
    for (char& c : value)
        c = static_cast<char>(
            toupper(static_cast<unsigned char>(c)));

    return value;
}

string Menu::trimSeatInput(string value) const
{
    size_t first = value.find_first_not_of(" \t\r\n");

    if (first == string::npos)
        return "";

    size_t last = value.find_last_not_of(" \t\r\n");

    return upper(value.substr(first, last - first + 1));
}

void Menu::run()
{
    loginMenu();
}

void Menu::pause() const
{
    cout << "\nNhan Enter de tiep tuc...";

    string temp;
    getline(cin, temp);
}

void Menu::printMovies(const vector<Movie>& movies) const
{
    cout << "\n================ DANH SACH PHIM ================\n";

    cout << left
         << setw(8) << "ID"
         << setw(28) << "TEN PHIM"
         << setw(20) << "THE LOAI"
         << right << setw(10) << "PHUT"
         << setw(8) << "TUOI"
         << "  "
         << left << setw(16) << "TRANG THAI"
         << '\n';

    cout << string(96, '-') << '\n';

    for (const Movie& movie : movies)
    {
        cout << left
             << setw(8) << movie.getMovieId()
             << setw(28) << movie.getTitle().substr(0, 27)
             << setw(20) << movie.getGenre().substr(0, 19)
             << right << setw(10) << movie.getDuration()
             << setw(8) << movie.getAgeLimit()
             << "  "
             << left << setw(16)
             << movie.getStatus().substr(0, 15)
             << '\n';
    }

    if (movies.empty())
        cout << "Khong co du lieu.\n";

    cout << right;
}

void Menu::printShowtimes(const vector<Showtime>& showtimes) const
{
    cout << "\n================ DANH SACH SHOWTIME ================\n";

    cout << left
         << setw(10) << "ID"
         << setw(10) << "PHIM"
         << setw(12) << "PHONG"
         << setw(14) << "NGAY"
         << setw(10) << "GIO"
         << setw(16) << "GIA"
         << "TRANG THAI\n";

    cout << string(82, '-') << '\n';

    for (const Showtime& showtime : showtimes)
    {
        cout << left
             << setw(10) << showtime.getShowtimeId()
             << setw(10) << showtime.getMovieId()
             << setw(12) << showtime.getRoomId()
             << setw(14) << showtime.getShowDate()
             << setw(10) << showtime.getStartTime()
             << setw(16) << fixed << setprecision(0)
             << showtime.getBasePrice()
             << showtime.getStatus()
             << '\n';
    }

    if (showtimes.empty())
        cout << "Khong co du lieu.\n";
}

void Menu::printRooms() const
{
    cout << "\n================ DANH SACH PHONG ================\n";

    cout << left
         << setw(10) << "ID"
         << setw(28) << "TEN PHONG"
         << setw(10) << "DONG"
         << setw(10) << "COT"
         << "SO GHE\n";

    cout << string(70, '-') << '\n';

    for (const CinemaRoom& room : roomManager.getItems())
    {
        cout << left
             << setw(10) << room.getRoomId()
             << setw(28) << room.getRoomName().substr(0, 27)
             << setw(10) << room.getRowCount()
             << setw(10) << room.getColCount()
             << room.getSeats().size()
             << '\n';
    }

    if (roomManager.getItems().empty())
        cout << "Khong co phong.\n";
}
