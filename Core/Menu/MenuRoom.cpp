#include "Menu.h"

using namespace std;

void Menu::roomMenu()
{
    while (true)
    {
        cout << "\n---------- QUAN LY PHONG + GHE ----------\n";
        cout << "1. Tao phong (dong x cot)\n";
        cout << "2. Sua kich thuoc\n";
        cout << "3. Gan VIP ghe\n";
        cout << "4. Bo VIP ghe\n";
        cout << "5. Khoa ghe bao tri\n";
        cout << "6. Mo khoa ghe\n";
        cout << "7. Xem so do\n";
        cout << "8. Xoa phong\n";
        cout << "0. Quay lai\n";

        int choice = input.getInt("Chon: ", 0, 8);

        if (choice == 0)
            return;

        string error;

        if (choice == 1)
        {
            printRooms();

            string name = input.getLine("Ten phong: ");
            int rows = input.getInt("So dong (1-26): ", 1, 26);
            int cols = input.getInt("So cot (1-30): ", 1, 30);

            string newId;

            if (roomManager.createRoom(
                    name, rows, cols, newId, error))
            {
                cout << "Tao phong thanh cong: "
                     << newId << '\n';
            }
        }
        else if (choice == 2)
        {
            printRooms();

            string id = input.getLine("Ma phong: ");
            string name = input.getLine("Ten phong moi: ");
            int rows = input.getInt("So dong: ", 1, 26);
            int cols = input.getInt("So cot: ", 1, 30);

            roomManager.updateRoom(
                id, name, rows, cols, error);
        }
        else if (choice >= 3 && choice <= 6)
        {
            printRooms();

            string roomId = input.getLine("Ma phong: ");
            string seatId = upper(
                input.getLine("Ma ghe (VD A0): "));

            if (choice == 3)
                roomManager.setSeatVIP(
                    roomId, seatId, true, error);
            else if (choice == 4)
                roomManager.setSeatVIP(
                    roomId, seatId, false, error);
            else if (choice == 5)
                roomManager.setSeatMaintenance(
                    roomId, seatId, true, error);
            else
                roomManager.setSeatMaintenance(
                    roomId, seatId, false, error);
        }
        else if (choice == 7)
        {
            printRooms();

            const vector<CinemaRoom>& rooms =
                roomManager.getItems();

            if (rooms.empty())
            {
                cout << "Chua co phong nao.\n";
            }
            else
            {
                int roomIndex = input.getInt(
                    "Chon phong (Nhap so, 0 de huy): ",
                    0,
                    static_cast<int>(rooms.size()));

                if (roomIndex > 0)
                {
                    const CinemaRoom& room =
                        rooms[roomIndex - 1];

                    cout << "\n>> Ban da chon phong: "
                         << room.getRoomId()
                         << " - "
                         << room.getRoomName()
                         << "\n";

                    room.displaySeatLayout();
                }
            }
        }
        else if (choice == 8)
        {
            printRooms();

            roomManager.deleteRoom(
                input.getLine("Ma phong: "), error);
        }

        if (!error.empty())
            cout << "Loi: " << error << '\n';
        else if (choice != 7)
        {
            cout << "Thuc hien thanh cong.\n";

            if (choice != 0)
                printRooms();
        }

        pause();
    }
}
