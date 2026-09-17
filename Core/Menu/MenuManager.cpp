#include "Menu.h"

#include <iomanip>

using namespace std;

void Menu::managerMenu(const Account& account)
{
    while (true)
    {
        input.clearScreen();

        cout << "\n================ MANAGER ================\n";
        cout << "1. Quan ly Staff\n";
        cout << "2. Quan ly phim\n";
        cout << "3. Quan ly Showtime\n";
        cout << "4. Quan ly phong + so do ghe\n";
        cout << "5. Quan ly Customer\n";
        cout << "6. Ban ve tai quay\n";
        cout << "7. Tra cuu phim/lich chieu\n";
        cout << "8. Thong ke\n";
        cout << "9. Xem tat ca Booking\n";
        cout << "0. Dang xuat\n";

        int choice = input.getInt("Chon: ", 0, 9);

        if (choice == 0)
            return;

        if (choice == 1)
            staffAccountMenu();
        else if (choice == 2)
            movieMenu();
        else if (choice == 3)
            showtimeMenu();
        else if (choice == 4)
            roomMenu();
        else if (choice == 5)
            customerManagementMenu();
        else if (choice == 6)
            bookingAtCounter(account);
        else if (choice == 7)
            lookupMoviesAndShowtimes();
        else if (choice == 8)
            statisticsMenu();
        else if (choice == 9)
        {
            for (const Booking& booking : bookingManager.getItems())
            {
                cout << booking.getBookingId()
                     << " | Customer: " << booking.getCustomerId()
                     << " | Showtime: " << booking.getShowtimeId()
                     << " | " << booking.getStatusText()
                     << " | " << fixed << setprecision(0)
                     << booking.getTotal() << " VND\n";
            }

            pause();
        }
    }
}

void Menu::customerManagementMenu()
{
    while (true)
    {
        cout << "\n---------- QUAN LY CUSTOMER ----------\n";
        cout << "1. Danh sach\n";
        cout << "2. Tim kiem\n";
        cout << "3. Sua thong tin\n";
        cout << "4. Xoa\n";
        cout << "0. Quay lai\n";

        int choice = input.getInt("Chon: ", 0, 4);

        if (choice == 0)
            return;

        string error;

        if (choice == 1 || choice == 2)
        {
            string key;

            if (choice == 2)
                key = input.getLine("Tu khoa: ");

            vector<Account> customers =
                accountManager.searchCustomers(key);

            cout << "\n"
                 << left
                 << setw(8) << "ID"
                 << setw(18) << "USERNAME"
                 << setw(26) << "HO TEN"
                 << setw(15) << "SDT"
                 << "EMAIL\n";

            cout << string(90, '-') << '\n';

            for (const Account& customer : customers)
            {
                cout << left
                     << setw(8) << customer.id
                     << setw(18) << customer.username
                     << setw(26) << customer.fullName.substr(0, 25)
                     << setw(15) << customer.phone
                     << customer.email
                     << '\n';
            }
        }
        else if (choice == 3)
        {
            string id = input.getLine("Customer ID: ");
            string name = input.getLine("Ho ten moi: ");
            string phone = input.getLine("SDT moi: ");
            string email = input.getLine("Email moi: ");

            accountManager.updateCustomer(
                id, name, phone, email, error);
        }
        else
        {
            accountManager.deleteCustomer(
                input.getLine("Customer ID: "), error);
        }

        if (!error.empty())
            cout << "Loi: " << error << '\n';
        else if (choice >= 3)
            cout << "Thuc hien thanh cong.\n";

        pause();
    }
}
