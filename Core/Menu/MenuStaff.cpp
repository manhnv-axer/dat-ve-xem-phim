#include "Menu.h"

#include <iomanip>

using namespace std;

void Menu::staffMenu(const Account& account)
{
    while (true)
    {
        input.clearScreen();

        cout << "\n---------------- STAFF ----------------\n";
        cout << "1. Ban ve tai quay\n";
        cout << "2. Tra cuu phim/lich chieu\n";
        cout << "3. Xem Booking\n";
        cout << "4. Huy Booking\n";
        cout << "5. Xem danh sach Customer\n";
        cout << "0. Dang xuat\n";

        int choice = input.getInt("Chon: ", 0, 5);

        if (choice == 0)
            return;

        if (choice == 1)
        {
            bookingAtCounter(account);
        }
        else if (choice == 2)
        {
            lookupMoviesAndShowtimes();
        }
        else if (choice == 3)
        {
            string id = input.getLine("Customer ID: ");
            bookingHistory(id);
        }
        else if (choice == 4)
        {
            cancelBooking("", true);
        }
        else if (choice == 5)
        {
            cout << "\n---------------- DANH SACH CUSTOMER ----------------\n";

            for (const Account& customer : accountManager.getCustomers())
            {
                cout << customer.id << " | "
                     << customer.fullName << " | "
                     << customer.phone << '\n';
            }

            pause();
        }
    }
}

void Menu::staffAccountMenu()
{
    while (true)
    {
        cout << "\n---------- QUAN LY STAFF (CHI MANAGER) ----------\n";
        cout << "1. Tao Staff\n";
        cout << "2. Khoa Staff\n";
        cout << "3. Mo khoa Staff\n";
        cout << "4. Danh sach Staff\n";
        cout << "0. Quay lai\n";

        int choice = input.getInt("Chon: ", 0, 4);

        if (choice == 0)
            return;

        if (choice == 1)
        {
            string error;
            string username;

            do
            {
                username = input.getLine("Username: ");

                if (!AccountManager::validUsername(username))
                    cout << "Loi: Username phai dai 3-20 ky tu, chi gom chu, so va dau _.\n";
                else if (accountManager.usernameExists(username))
                    cout << "Loi: Username da ton tai.\n";

            } while (!AccountManager::validUsername(username) ||
                     accountManager.usernameExists(username));

            string password;

            do
            {
                password = input.getPassword("Password: ");

                if (!AccountManager::validPassword(password))
                    cout << "Loi: Password phai co it nhat 6 ky tu.\n";

            } while (!AccountManager::validPassword(password));

            string confirmPassword;

            do
            {
                confirmPassword = input.getPassword("Nhap lai Password: ");

                if (password != confirmPassword)
                    cout << "Loi: Password nhap lai khong khop.\n";

            } while (password != confirmPassword);

            string name = input.getLine("Ho ten: ");
            string phone;
            string email;

            do
            {
                phone = input.getLine("SDT: ");

                if (!AccountManager::validPhone(phone))
                    cout << "Loi: So dien thoai khong hop le.\n";

            } while (!AccountManager::validPhone(phone));

            do
            {
                email = input.getLine("Email: ");

                if (!AccountManager::validEmail(email))
                    cout << "Loi: Email khong dung dinh dang.\n";

            } while (!AccountManager::validEmail(email));

            if (accountManager.createStaff(
                    username, password, name, phone, email, error))
            {
                cout << "Tao Staff thanh cong.\n";
            }
            else
            {
                cout << "Loi: " << error << '\n';
            }
        }
        else if (choice == 2 || choice == 3)
        {
            string id = input.getLine("Staff ID: ");
            string error;

            if (accountManager.setStaffStatus(
                    id, choice == 3, error))
            {
                cout << (choice == 2
                    ? "Da khoa Staff.\n"
                    : "Da mo khoa Staff.\n");
            }
            else
            {
                cout << "Loi: " << error << '\n';
            }
        }

        cout << "\n---------------- DANH SACH STAFF ----------------\n";

        cout << left
             << setw(8) << "ID"
             << setw(18) << "USERNAME"
             << setw(26) << "HO TEN"
             << setw(12) << "TRANG THAI"
             << '\n';

        cout << string(64, '-') << '\n';

        for (const Account& staff : accountManager.getStaff())
        {
            cout << left
                 << setw(8) << staff.id
                 << setw(18) << staff.username
                 << setw(26) << staff.fullName.substr(0, 25)
                 << (staff.active ? "Active" : "Locked")
                 << '\n';
        }

        pause();
    }
}
