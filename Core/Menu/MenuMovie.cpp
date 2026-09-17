#include "Menu.h"

using namespace std;

void Menu::movieMenu()
{
    while (true)
    {
        cout << "\n---------- QUAN LY PHIM ----------\n";
        cout << "1. Them\n";
        cout << "2. Sua\n";
        cout << "3. Xoa\n";
        cout << "4. Doi trang thai\n";
        cout << "5. Xem\n";
        cout << "0. Quay lai\n";

        int choice = input.getInt("Chon: ", 0, 5);

        if (choice == 0)
            return;

        string error;

        if (choice == 1)
        {
            string id = input.getLine("Ma phim: ");
            string title = input.getLine("Ten phim: ");
            string genre = input.getLine("The loai: ");
            int duration = input.getInt("Thoi luong: ", 1, 1000);
            int age = input.getInt("Do tuoi: ", 0, 100);
            string status = input.getLine("Trang thai: ");

            movieManager.addMovie(
                Movie(id, title, duration, genre, age, status),
                error);
        }
        else if (choice == 2)
        {
            printMovies(movieManager.getItems());

            string id = input.getLine("Ma phim: ");
            string title = input.getLine("Ten moi: ");
            int duration = input.getInt("Thoi luong moi: ", 1, 1000);
            string genre = input.getLine("The loai moi: ");
            int age = input.getInt("Do tuoi moi: ", 0, 100);

            movieManager.updateMovie(
                id, title, duration, genre, age, error);
        }
        else if (choice == 3)
        {
            printMovies(movieManager.getItems());

            movieManager.deleteMovie(
                input.getLine("Ma phim: "), error);
        }
        else if (choice == 4)
        {
            printMovies(movieManager.getItems());

            string id = input.getLine("Ma phim: ");
            string status = input.getLine("Trang thai moi: ");

            movieManager.setStatus(id, status, error);
        }
        else
        {
            printMovies(movieManager.getItems());
        }

        if (!error.empty())
            cout << "Loi: " << error << '\n';
        else if (choice != 5)
            cout << "Thuc hien thanh cong.\n";

        pause();
    }
}
