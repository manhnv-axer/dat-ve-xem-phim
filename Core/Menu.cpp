#include "Menu.h"

// Constructor: Tự động tải dữ liệu từ file txt lên khi mở app
Menu::Menu() {
    movieMgr.loadFromFile();
    showtimeMgr.loadFromFile();
}

// Vòng lặp chính của chương trình
void Menu::run() {
    int choice;
    do {
        cout << "\n============= HE THONG DAT VE XEM PHIM =============" << endl;
        cout << "1. Menu Khach Hang (Xem phim, tra cuu)" << endl;
        cout << "2. Menu Quan Ly (Them/Sua/Xoa du lieu)" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "====================================================" << endl;
        cout << "Moi ban chon: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                showCustomerMenu(); 
                break;
            case 2: 
                showAdminMenu(); 
                break;
            case 0: 
                cout << "Dang luu du lieu vao file txt..." << endl;
                movieMgr.saveToFile();
                showtimeMgr.saveToFile();
                cout << "Da luu thanh cong. Tam biet!" << endl;
                break;
            default: 
                cout << "Lua chon khong hop le, vui long nhap lai!" << endl;
        }
    } while (choice != 0);
}

void Menu::showCustomerMenu() {
    int choice;
    do {
        cout << "\n--- MENU KHACH HANG ---" << endl;
        cout << "1. Xem danh sach phim dang chieu" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "Moi chon: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n--- DANH SACH PHIM ---" << endl;
            // Gọi getAll() từ DataManager để lấy danh sách và in ra
            for (const auto& m : movieMgr.getAll()) {
                m.displayMovieInfo();
            }
        }
    } while (choice != 0);
}

void Menu::showAdminMenu() {
    int choice;
    do {
        cout << "\n--- MENU QUAN LY ---" << endl;
        cout << "1. Quan ly Phim (Them phim moi)" << endl;
        cout << "2. Quan ly Suat chieu (Them suat chieu moi)" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "Moi chon: ";
        cin >> choice;

        if (choice == 1) {
            string id, title, genre;
            int duration, ageLimit;
            
            cout << "\n--- THEM PHIM MOI ---" << endl;
            cout << "Nhap Ma phim (VD: M02): ";
            cin >> id;
            
            // Xóa bộ nhớ đệm trước khi dùng getline để không bị trôi lệnh nhập chuỗi
            cin.ignore(); 
            
            cout << "Nhap Ten phim: ";
            getline(cin, title); // Hỗ trợ nhập tên phim có dấu cách
            
            cout << "Nhap The loai: ";
            getline(cin, genre);
            
            cout << "Nhap Thoi luong (phut): ";
            cin >> duration;
            
            cout << "Nhap Do tuoi quy dinh: ";
            cin >> ageLimit;

            // Khởi tạo đối tượng Movie và gọi hàm add() của template DataManager
            Movie newMovie(id, title, duration, genre, ageLimit);
            movieMgr.add(newMovie);
            
            cout << ">> Them phim thanh cong!" << endl;

        } else if (choice == 2) {
            string id, movieId, roomId, date, time;
            double price;
            
            cout << "\n--- THEM SUAT CHIEU MOI ---" << endl;
            cout << "Nhap Ma suat chieu (VD: ST02): ";
            cin >> id;
            
            cout << "Nhap Ma phim (VD: M01): ";
            cin >> movieId;
            
            cout << "Nhap Ma phong (VD: ROOM01): ";
            cin >> roomId;
            
            cout << "Nhap Ngay chieu (YYYY-MM-DD): ";
            cin >> date;
            
            cout << "Nhap Gio chieu (HH:MM): ";
            cin >> time;
            
            cout << "Nhap Gia ve co ban: ";
            cin >> price;

            // Khởi tạo đối tượng Showtime (Tạm thời để nullptr cho đối tượng con)
            Showtime newShowtime(id, date, time, price, nullptr, nullptr);
            showtimeMgr.add(newShowtime);
            
            cout << ">> Them suat chieu thanh cong!" << endl;
        }
    } while (choice != 0);
}