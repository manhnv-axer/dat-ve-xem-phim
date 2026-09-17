#include "Menu.h"

#include <iomanip>

using namespace std;

void Menu::statisticsMenu()
{
    while (true)
    {
        input.clearScreen();

        cout << "\n================ THONG KE DOANH THU ================\n";
        cout << "1. Doanh thu theo ngay\n";
        cout << "2. Doanh thu theo thang\n";
        cout << "3. Doanh thu theo nam\n";
        cout << "4. Tong Booking / tong ve da ban\n";
        cout << "5. Doanh thu theo phim\n";
        cout << "0. Quay lai\n";

        int choice = input.getInt("Chon: ", 0, 5);

        if (choice == 0)
            return;

        if (choice == 1)
        {
            string date =
                input.getLine("Nhap ngay (YYYY-MM-DD): ");

            cout << "\nDoanh thu ngay "
                 << date << ": "
                 << fixed << setprecision(0)
                 << bookingManager.revenueOnDate(date)
                 << " VND\n";
        }
        else if (choice == 2)
        {
            string month =
                input.getLine("Nhap thang (YYYY-MM): ");

            cout << "\nDoanh thu thang "
                 << month << ": "
                 << fixed << setprecision(0)
                 << bookingManager.revenueInMonth(month)
                 << " VND\n";
        }
        else if (choice == 3)
        {
            string year =
                input.getLine("Nhap nam (YYYY): ");

            cout << "\nDoanh thu nam "
                 << year << ": "
                 << fixed << setprecision(0)
                 << bookingManager.revenueInYear(year)
                 << " VND\n";
        }
        else if (choice == 4)
        {
            cout << "\nTong Booking da thanh toan: "
                 << bookingManager.totalPaidBookings()
                 << '\n';

            cout << "Tong ve da ban: "
                 << bookingManager.totalPaidTickets()
                 << '\n';
        }
        else if (choice == 5)
        {
            cout << "\n================ DOANH THU THEO PHIM ================\n";

            vector<pair<string, double>> ranking =
                bookingManager.revenueByMovie(
                    showtimeManager);

            int index = 1;

            for (const auto& entry : ranking)
            {
                const Movie* movie =
                    movieManager.findById(entry.first);

                cout << index++ << ". "
                     << entry.first
                     << " | "
                     << (movie == nullptr
                         ? "Khong tim thay"
                         : movie->getTitle())
                     << " | "
                     << fixed << setprecision(0)
                     << entry.second
                     << " VND\n";
            }

            if (ranking.empty())
                cout << "Chua co doanh thu.\n";
        }

        pause();
    }
}
