#include "Menu.h"

using namespace std;

void Menu::showtimeMenu()
{
    while (true)
    {
        cout << "\n---------- QUAN LY SHOWTIME ----------\n";
        cout << "1. Them\n";
        cout << "2. Sua\n";
        cout << "3. Huy\n";
        cout << "4. Xoa\n";
        cout << "5. Xem\n";
        cout << "0. Quay lai\n";

        int choice = input.getInt("Chon: ", 0, 5);

        if (choice == 0)
            return;

        string error;

        if (choice == 1)
        {
            string id = input.getLine("Ma Showtime: ");
            string movieId = input.getLine("Ma phim: ");
            string roomId = input.getLine("Ma phong: ");
            string date = input.getLine("Ngay YYYY-MM-DD: ");
            string time = input.getLine("Gio HH:MM: ");
            double price = input.getDouble("Gia co ban: ", 0);

            showtimeManager.addShowtime(
                Showtime(id, movieId, roomId, date, time, price),
                error);
        }
        else if (choice == 2)
        {
            printShowtimes(showtimeManager.getItems());

            string id = input.getLine("Ma Showtime: ");
            string movieId = input.getLine("Ma phim: ");
            string roomId = input.getLine("Ma phong: ");
            string date = input.getLine("Ngay: ");
            string time = input.getLine("Gio: ");
            double price = input.getDouble("Gia: ", 0);

            showtimeManager.updateShowtime(
                id, movieId, roomId, date, time, price, error);
        }
        else if (choice == 3)
        {
            printShowtimes(showtimeManager.getItems());

            showtimeManager.cancelShowtime(
                input.getLine("Ma Showtime: "), error);
        }
        else if (choice == 4)
        {
            printShowtimes(showtimeManager.getItems());

            showtimeManager.deleteShowtime(
                input.getLine("Ma Showtime: "), error);
        }
        else
        {
            printShowtimes(showtimeManager.getItems());
        }

        if (!error.empty())
            cout << "Loi: " << error << '\n';
        else if (choice != 5)
            cout << "Thuc hien thanh cong.\n";

        pause();
    }
}
