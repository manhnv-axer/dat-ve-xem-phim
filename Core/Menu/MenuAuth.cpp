#include "Menu.h"

using namespace std;

void Menu::loginMenu()
{
    while (true)
    {
        input.clearScreen();

        cout << "\n====================================================\n";
        cout << "           HE THONG QUAN LY BAN VE CINEMA\n";
        cout << "====================================================\n";
        cout << "1. Dang nhap\n";
        cout << "2. Dang ky Customer\n";
        cout << "0. Thoat\n";

        int choice = input.getInt("Chon: ", 0, 2);

        if (choice == 0)
            return;

        if (choice == 2)
        {
            string username;

            do
            {
                username = input.getLine("Username: ");

                if (!AccountManager::validUsername(username))
                    cout << "Loi: Username phai dai 3-20 ky tu, chi gom chu, so va dau _.\n";
                else if (accountManager.usernameExists(username))
                    cout << "Loi: Username da ton tai. Vui long chon username khac.\n";

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

            do
            {
                phone = input.getLine("So dien thoai: ");

                if (!AccountManager::validPhone(phone))
                    cout << "Loi: So dien thoai phai gom 10 hoac 11 chu so va bat dau bang 0.\n";

            } while (!AccountManager::validPhone(phone));

            string email;

            do
            {
                email = input.getLine("Email: ");

                if (!AccountManager::validEmail(email))
                    cout << "Loi: Email khong dung dinh dang.\n";

            } while (!AccountManager::validEmail(email));

            string error;

            if (accountManager.registerCustomer(
                    username, password, name, phone, email, error))
            {
                cout << "Dang ky Customer thanh cong. Vui long dang nhap.\n";
            }
            else
            {
                cout << "Loi: " << error << '\n';
            }

            pause();
            continue;
        }

        const Account* account = nullptr;

        while (account == nullptr)
        {
            string username = input.getLine("Username: ");

            if (!AccountManager::validUsername(username))
            {
                cout << "Loi: Username khong hop le.\n";
                continue;
            }

            if (!accountManager.usernameExists(username))
            {
                cout << "Loi: Username khong ton tai trong he thong.\n";
                continue;
            }

            string password = input.getPassword("Password: ");

            account = accountManager.authenticate(username, password);

            if (account == nullptr)
            {
                cout << "Sai username/password. Vui long nhap lai.\n";
            }
            else if (!account->active)
            {
                cout << "Tai khoan dang bi khoa. Vui long nhap lai.\n";
                account = nullptr;
            }
        }

        cout << "Dang nhap thanh cong: "
             << account->fullName
             << " (" << roleText(AccountManager::getRole(*account))
             << ")\n";

        if (AccountManager::isManager(*account))
            managerMenu(*account);
        else if (AccountManager::isStaff(*account))
            staffMenu(*account);
        else
            customerMenu(*account);
    }
}
