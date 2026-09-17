#include "Menu.h"

using namespace std;

void Menu::customerMenu(const Account& account)
{
    while (true)
    {
        input.clearScreen();

        cout << "\n---------------- CUSTOMER ----------------\n";
        cout << "1. Dat nhieu ghe trong mot Booking\n";
        cout << "2. Tra cuu phim va lich chieu\n";
        cout << "3. Xem Booking cua toi\n";
        cout << "4. Huy Booking (>= 30 phut truoc gio chieu)\n";
        cout << "0. Dang xuat\n";

        int choice = input.getInt("Chon: ", 0, 4);

        if (choice == 0)
            return;

        if (choice == 1)
            bookingOnline(account);
        else if (choice == 2)
            lookupMoviesAndShowtimes();
        else if (choice == 3)
            bookingHistory(account.id);
        else if (choice == 4)
            cancelBooking(account.id, false);
    }
}
