#include "Menu.h"
#include "../Room/CinemaRoom.h"
#include "../AccountManager/AccountManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

Menu::Menu() {
    movieMgr.loadFromFile();
    showtimeMgr.loadFromFile();
}

void Menu::run() {
    AccountManager accMgr;
    accMgr.load(); // Tải danh sách tài khoản từ data/users.txt

    const Account* currentAccount = nullptr;
    int authChoice;

    // --- MÀN HÌNH XÁC THỰC (ĐĂNG NHẬP / ĐĂNG KÝ) ---
    do {
        cout << "\n================ HE THONG XEM PHIM ================" << endl;
        cout << "1. Dang nhap" << endl;
        cout << "2. Dang ky tai khoan khach hang" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "===================================================" << endl;
        cout << "Moi ban chon: ";
        cin >> authChoice;

        if (authChoice == 1) {
            string user, pass;
            cout << "Nhap username: "; cin >> user;
            cout << "Nhap password: "; cin >> pass;

            currentAccount = accMgr.authenticate(user, pass);
            if (currentAccount != nullptr) {
                if (!currentAccount->active) {
                    cout << ">> Tai khoan cua bạn da bị khoa!" << endl;
                    currentAccount = nullptr;
                    system("pause");
                } else {
                    cout << ">> Dang nhap thanh công! Xin chao: " << currentAccount->fullName << endl;
                    system("pause");
                    break; // Thoát vòng lặp đăng nhập, đi tiếp vào hệ thống
                }
            } else {
                cout << ">> Sai username hoac password!" << endl;
                system("pause");
            }
        } 
        else if (authChoice == 2) {
            string user, pass, name, phone, err;
            cout << "\n--- DANG KY TAI KHOAN ---" << endl;
            cout << "Nhap username moi: "; cin >> user;
            cout << "Nhap password: "; cin >> pass;
            cin.ignore();
            cout << "Nhap ho ten day du: "; getline(cin, name);
            cout << "Nhap so dien thoai: "; cin >> phone;

            if (accMgr.registerAccount(user, pass, name, phone, err)) {
                cout << ">> Đang ký tai khoan thanh công! Ban co the đăng nhap ngay." << endl;
            } else {
                cout << ">> Đang ky that bai: " << err << endl;
            }
            system("pause");
        } 
        else if (authChoice == 0) {
            cout << "Tam biet!" << endl;
            return;
        }
    } while (true);

    // --- MENU CHÍNH SAU KHI ĐĂNG NHẬP ---
    int choice;
    Role userRole = AccountManager::getRole(*currentAccount);

    do {
        cout << "\n============= HE THONG DAT VE XEM PHIM =============" << endl;
        cout << "Xin chao: " << currentAccount->fullName << " (" << currentAccount->role << ")" << endl;
        cout << "----------------------------------------------------" << endl;
        
        if (userRole == Role::Customer) {
            // KHÁCH HÀNG: Đưa thẳng vào các tùy chọn tìm kiếm & đặt vé luôn, không qua menu phụ nữa
            cout << "1. Dat ve ngay (Cac phim dang chieu)" << endl;
            cout << "2. Tim phim theo ten" << endl;
            cout << "3. Tim phim theo the loai" << endl;
            cout << "0. Dang xuat & Thoat" << endl;
        } else {
            // ADMIN / STAFF: Giữ nguyên menu có quyền quản lý
            cout << "1. Menu Khach Hang (Dat ve)" << endl;
            cout << "2. Menu Quan Ly (Admin / Staff)" << endl;
            cout << "0. Dang xuat & Thoat" << endl;
        }
        cout << "====================================================" << endl;
        cout << "Moi ban chon: ";
        cin >> choice;

        if (userRole == Role::Customer) {
            // Xử lý trực tiếp cho Khách hàng
            if (choice == 1) {
                vector<Movie> list = movieMgr.getMoviesByStatus("Dang chieu");
                displayAndSelectMovie(list);
            } else if (choice == 2) {
                string keyword;
                cout << "Nhap ten phim can tim: ";
                cin.ignore();
                getline(cin, keyword);
                vector<Movie> list = movieMgr.searchMoviesByTitle(keyword);
                displayAndSelectMovie(list);
            } else if (choice == 3) {
                string keyword;
                cout << "Nhap the loai can tim: ";
                cin.ignore();
                getline(cin, keyword);
                vector<Movie> list = movieMgr.searchMoviesByGenre(keyword);
                displayAndSelectMovie(list);
            }
        } else {
            // Xử lý cho Admin / Staff
            if (choice == 1) {
                showCustomerMenu();
            } else if (choice == 2) {
                showAdminMenu();
            }
        }

        if (choice == 0) {
            cout << "Dang luu du lieu vao file txt..." << endl;
            movieMgr.saveToFile();
            showtimeMgr.saveToFile();
            accMgr.save();
            cout << "Da luu thanh cong. Tam biet!" << endl;
            break;
        }
    } while (choice != 0);
}

void Menu::showCustomerMenu() {
    int choice;
    do {
        cout << "\n--- MENU KHACH HANG ---" << endl;
        cout << "1. Dat ve ngay (Cac phim dang chieu)" << endl;
        cout << "2. Tim phim theo ten" << endl;
        cout << "3. Tim phim theo the loai" << endl;
        cout << "0. Quay lai" << endl;
        cout << "Moi chon: ";
        cin >> choice;

        if (choice == 1) {
            vector<Movie> list = movieMgr.getMoviesByStatus("Dang chieu");
            displayAndSelectMovie(list);
        } else if (choice == 2) {
            string keyword;
            cout << "Nhap ten phim can tim: ";
            cin.ignore();
            getline(cin, keyword);
            vector<Movie> list = movieMgr.searchMoviesByTitle(keyword);
            displayAndSelectMovie(list);
        } else if (choice == 3) {
            string keyword;
            cout << "Nhap the loai can tim (VD: Hanh dong): ";
            cin.ignore();
            getline(cin, keyword);
            vector<Movie> list = movieMgr.searchMoviesByGenre(keyword);
            displayAndSelectMovie(list);
        }
    } while (choice != 0);
}

void Menu::displayAndSelectMovie(vector<Movie>& movies) {
    if (movies.empty()) {
        cout << ">> Khong co bo phim nao phu hop!" << endl;
        system("pause");
        return;
    }

    cout << "\n--- KET QUA TIM KIEM ---" << endl;
    for (int i = 0; i < movies.size(); i++) {
        cout << "[" << i + 1 << "] " << movies[i].getTitle() 
             << " | The loai: " << movies[i].getGenre() 
             << " | " << movies[i].getDuration() << " phut" << endl;
    }
    cout << "[0] Huy bo va quay lai" << endl;
    
    int select;
    cout << ">> Chon phim ban muon xem (Nhap so): ";
    cin >> select;

    if (select > 0 && select <= movies.size()) {
        bookingFlow(movies[select - 1]);
    }
}

void Menu::bookingFlow(Movie selectedMovie) {
    cout << "\n=======================================================" << endl;
    cout << ">> DANG DAT VE CHO PHIM: " << selectedMovie.getTitle() << " <<" << endl;
    
    vector<Showtime> listST = showtimeMgr.getShowtimesByMovieId(selectedMovie.getMovieId());
    
    if (listST.empty()) {
        cout << ">> Xin loi, phim nay hien chua co lich chieu nao!" << endl;
        system("pause");
        return;
    }

    cout << "\n--- DANH SACH SUAT CHIEU ---" << endl;
    for (int i = 0; i < listST.size(); i++) {
        cout << "[" << i + 1 << "] ";
        listST[i].displayShowtime();
    }
    cout << "[0] Huy bo va quay lai" << endl;
    
    int selectST;
    cout << ">> Chon suat chieu (Nhap so): ";
    cin >> selectST;

    if (selectST > 0 && selectST <= listST.size()) {
        Showtime selectedST = listST[selectST - 1];
        CinemaRoom room(selectedST.getRoomId(), "Phong Chieu VIP");
        
        // Đọc vé cũ từ file data/tickets.txt để đánh dấu [X]
        ifstream inFile("data/tickets.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                string tId, mName, tDate, tTime, sId, tType, tPrice;
                getline(ss, tId, '|'); getline(ss, mName, '|'); getline(ss, tDate, '|');
                getline(ss, tTime, '|'); getline(ss, sId, '|');
                
                if (tId.find(selectedST.getShowtimeId()) != string::npos) {
                    Seat* s = room.getSeatById(sId);
                    if (s != nullptr) s->setBooked(true);
                }
            }
            inFile.close();
        }

        cout << "\n>> Ban da chon Suat: " << selectedST.getStartTime() << " (Phong: " << selectedST.getRoomId() << ")" << endl;
        room.displayRoomMap();
        
        string selectSeatId;
        cout << ">> Nhap Ma ghe ban muon ngoi (VD: A5, D8) hoac go '0' de huy: ";
        cin >> selectSeatId;

        if (selectSeatId == "0") return;

        selectSeatId[0] = toupper(selectSeatId[0]);
        Seat* chosenSeat = room.getSeatById(selectSeatId);
        
        if (chosenSeat != nullptr) {
            if (chosenSeat->getIsBooked()) {
                cout << ">> Ghe nay da co nguoi dat! Vui long chon ghe khac." << endl;
                system("pause");
                return;
            }

            chosenSeat->setBooked(true);
            
            Ticket* myTicket = nullptr;
            string ticketId = "TICKET_" + selectedST.getShowtimeId() + "_" + chosenSeat->getSeatId();
            string ticketType = "Thuong";
            double finalPrice = selectedST.getBasePrice();

            if (chosenSeat->getIsVIP()) {
                myTicket = new VIPTicket(ticketId, selectedST.getBasePrice());
                ticketType = "VIP";
                finalPrice = selectedST.getBasePrice() * 1.5;
            } else {
                myTicket = new StandardTicket(ticketId, selectedST.getBasePrice());
            }

            ofstream outFile("data/tickets.txt", ios::app);
            if (outFile.is_open()) {
                outFile << ticketId << "|" << selectedMovie.getTitle() << "|" 
                        << selectedST.getShowDate() << "|" << selectedST.getStartTime() << "|" 
                        << chosenSeat->getSeatId() << "|" << ticketType << "|" << finalPrice << "\n";
                outFile.close();
            }

            cout << "\n========================================" << endl;
            cout << "       DAT VE THANH CONG!               " << endl;
            cout << "========================================" << endl;
            cout << "Phim: " << selectedMovie.getTitle() << endl;
            cout << "Suat chieu: " << selectedST.getStartTime() << " | Ngay: " << selectedST.getShowDate() << endl;
            cout << "Vi tri ghe: " << chosenSeat->getSeatId() << endl;
            
            myTicket->displayTicket();
            cout << "========================================\n" << endl;
            system("pause");

            delete myTicket;
        } else {
            cout << ">> Ma ghe khong ton tai! Vui long nhap dung dinh dang (VD: A5, H12)." << endl;
            system("pause");
        }
    }
}

void Menu::showAdminMenu() {
    int choice;
    do {
        cout << "\n--- MENU QUAN LY ---" << endl;
        cout << "1. Quan ly Phim (Them/Sua/Xoa)" << endl;
        cout << "2. Quan ly Suat chieu (Them suat chieu)" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "Moi chon: ";
        cin >> choice;

        if (choice == 1) {
            int action;
            cout << "\n--- QUAN LY PHIM ---" << endl;
            cout << "1. Them phim moi" << endl;
            cout << "2. Cap nhat trang thai phim" << endl;
            cout << "3. Xoa phim" << endl;
            cout << "0. Quay lai" << endl;
            cout << "Moi chon: ";
            cin >> action;
            
            if (action == 1) {
                string id, title, genre;
                int duration, ageLimit;
                
                cout << "Nhap Ma phim (VD: M02): "; cin >> id;
                cin.ignore(); 
                cout << "Nhap Ten phim: "; getline(cin, title); 
                cout << "Nhap The loai: "; getline(cin, genre);
                cout << "Nhap Thoi luong (phut): "; cin >> duration;
                cout << "Nhap Do tuoi quy dinh: "; cin >> ageLimit;

                Movie newMovie(id, title, duration, genre, ageLimit, "Dang chieu");
                movieMgr.add(newMovie);
                cout << ">> Them phim thanh cong!" << endl;
                system("pause");
            } 
            else if (action == 2) {
                cout << "\n--- DANH SACH PHIM HIEN TAI ---" << endl;
                vector<Movie> allMovies = movieMgr.getAll();
                if (allMovies.empty()) {
                    cout << ">> Hien chua co phim nao trong he thong!" << endl;
                } else {
                    for (const auto& m : allMovies) {
                        cout << "[Ma: " << m.getMovieId() << "] " << m.getTitle() 
                             << " | Trang thai: " << m.getStatus() << endl;
                    }
                    string id, newStatus;
                    cout << "\nNhap Ma phim can cap nhat (VD: M01): "; cin >> id;
                    cin.ignore();
                    cout << "Nhap Trang thai moi (Dang chieu / Sap chieu): "; getline(cin, newStatus);
                    movieMgr.updateMovieStatus(id, newStatus);
                }
                system("pause");
            } 
            else if (action == 3) {
                cout << "\n--- DANH SACH PHIM HIEN TAI ---" << endl;
                vector<Movie> allMovies = movieMgr.getAll();
                if (allMovies.empty()) {
                    cout << ">> Hien chua co phim nao trong he thong!" << endl;
                } else {
                    for (const auto& m : allMovies) {
                        cout << "[Ma: " << m.getMovieId() << "] " << m.getTitle() << endl;
                    }
                    string id;
                    cout << "\nNhap Ma phim can xoa: "; cin >> id;
                    movieMgr.deleteMovie(id);
                }
                system("pause");
            }
        } 
        else if (choice == 2) {
            string id, movieId, roomId, date, time;
            double price;
            
            cout << "\n--- THEM SUAT CHIEU MOI ---" << endl;
            cout << "\nDanh sach phim dang co trong he thong:" << endl;
            vector<Movie> allMovies = movieMgr.getAll();
            if (allMovies.empty()) {
                cout << ">> Hien chua co phim nao! Vui long them phim truoc." << endl;
                system("pause");
                continue;
            } else {
                for (const auto& m : allMovies) {
                    cout << " - [Ma: " << m.getMovieId() << "] " << m.getTitle() << endl;
                }
            }
            cout << "---------------------------" << endl;

            cout << "Nhap Ma suat chieu (VD: ST02): "; cin >> id;
            cout << "Nhap Ma phim (Chon tu danh sach tren): "; cin >> movieId; 
            cout << "Nhap Ma phong (VD: ROOM01): "; cin >> roomId;
            cout << "Nhap Ngay chieu (YYYY-MM-DD): "; cin >> date;
            cout << "Nhap Gio chieu (HH:MM): "; cin >> time;
            cout << "Nhap Gia ve co ban: "; cin >> price;

            Showtime newShowtime(id, movieId, roomId, date, time, price);
            showtimeMgr.add(newShowtime);
            cout << ">> Them suat chieu thanh cong!" << endl;
            system("pause");
        }
    } while (choice != 0);
}