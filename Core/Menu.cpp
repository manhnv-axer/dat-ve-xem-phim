#include "Menu.h"
#include "../Room/CinemaRoom.h"
#include "../AccountManager/AccountManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <conio.h> // Thu vien de dung _getch() an mat khau

Menu::Menu() {
    movieMgr.loadFromFile();
    showtimeMgr.loadFromFile();
}

void Menu::run() {
    AccountManager accMgr;
    accMgr.load(); // Tai danh sach tai khoan tu data/users.txt

    const Account* currentAccount = nullptr;
    int authChoice;

    // --- MAN HINH XAC THUC (DANG NHAP / DANG KY) ---
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
            
            // --- XU LY AN MAT KHAU BANG DAU * ---
            cout << "Nhap password: ";
            pass = "";
            char ch;
            while ((ch = _getch()) != '\r') {
                if (ch == '\b') {
                    if (pass.length() > 0) {
                        pass.pop_back();
                        cout << "\b \b";
                    }
                } else {
                    pass += ch;
                    cout << "*";
                }
            }
            cout << endl;
            // ------------------------------------

            currentAccount = accMgr.authenticate(user, pass);
            if (currentAccount != nullptr) {
                if (!currentAccount->active) {
                    cout << ">> Tai khoan cua ban da bi khoa!" << endl;
                    currentAccount = nullptr;
                    system("pause");
                } else {
                    cout << ">> Dang nhap thanh cong! Xin chao: " << currentAccount->fullName << endl;
                    system("pause");
                    break; // Thoat vong lap dang nhap, di tiep vao he thong
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
                cout << ">> Dang ky tai khoan thanh cong! Ban co the dang nhap ngay." << endl;
            } else {
                cout << ">> Dang ky that bai: " << err << endl;
            }
            system("pause");
        } 
        else if (authChoice == 0) {
            cout << "Tam biet!" << endl;
            return;
        }
    } while (true);

    // --- MENU CHINH SAU KHI DANG NHAP ---
    int choice;
    Role userRole = AccountManager::getRole(*currentAccount);

    do {
        cout << "\n============= HE THONG DAT VE XEM PHIM =============" << endl;
        cout << "Xin chao: " << currentAccount->fullName << " (" << currentAccount->role << ")" << endl;
        cout << "----------------------------------------------------" << endl;
        
        if (userRole == Role::Customer) {
            cout << "1. Dat ve ngay (Cac phim dang chieu)" << endl;
            cout << "2. Tim phim theo ten" << endl;
            cout << "3. Tim phim theo the loai" << endl;
            cout << "4. Xem lich su dat ve cua toi" << endl;
            cout << "0. Dang xuat & Thoat" << endl;
        } else {
            cout << "1. Menu Khach Hang (Dat ve)" << endl;
            cout << "2. Menu Quan Ly (Admin / Staff)" << endl;
            cout << "0. Dang xuat & Thoat" << endl;
        }
        cout << "====================================================" << endl;
        cout << "Moi ban chon: ";
        cin >> choice;

        if (userRole == Role::Customer) {
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
            } else if (choice == 4) {
                string currentUsername;
                cout << ">> [Bao Mat] Vui long xac nhan lai Username cua ban de tra cuu: ";
                cin >> currentUsername;
                showTicketHistory(currentUsername); 
                system("pause");
            }
        } else {
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
        cout << "4. Xem lich su dat ve cua toi" << endl;
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
        else if (choice == 4) {
            string currentUsername;
            cout << ">> [Bao Mat] Vui long xac nhan lai Username cua ban de tra cuu: ";
            cin >> currentUsername;
            showTicketHistory(currentUsername); 
            system("pause");
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
        cout << "3. Xem lich su dat ve (Toan he thong)" << endl; 
        cout << "0. Quay lai menu chinh" << endl;
        cout << "Moi chon: ";
        cin >> choice;

        if (choice == 1) {
            int action;
            cout << "\n--- QUAN LY PHIM ---" << endl;
            cout << "1. Them phim moi" << endl;
            cout << "2. Cap nhat trang thai phim" << endl;
            cout << "3. Xoa phim" << endl;
            cout << "4. Xem danh sach phim" << endl;
            cout << "0. Quay lai" << endl;
            cout << "Moi chon: ";
            cin >> action;
            
            if (action == 1) {
                string id, title, genre;
                int duration, ageLimit;
                vector<Movie> allMovies = movieMgr.getAll();
                int maxMovieId = 0;
                for (const auto& m : allMovies) {
                    string currentId = m.getMovieId();
                    if (currentId.length() >= 2 && currentId[0] == 'M') {
                        int num = atoi(currentId.substr(1).c_str());
                        if (num > maxMovieId) maxMovieId = num;
                    }
                }
                int nextId = maxMovieId + 1;
                id = "M" + string(nextId < 10 ? "0" : "") + to_string(nextId);
                cout << "\n>> He thong tu dong cap Ma phim: " << id << endl;
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
            else if (action == 4) {
                vector<Movie> allMovies = movieMgr.getAll();
                if (allMovies.empty()) {
                    cout << ">> Hien chua co phim nao trong he thong!" << endl;
                    system("pause");
                } else {
                    int itemsPerPage = 10;
                    int totalMovies = allMovies.size();
                    int totalPages = (totalMovies + itemsPerPage - 1) / itemsPerPage;
                    int currentPage = 1;
                    char nav;
                    
                    do {
                        cout << "\n============================== DANH SACH PHIM ==============================\n";
                        cout << left << setw(10) << "Ma Phim"
                             << setw(30) << "Ten Phim"
                             << setw(15) << "The Loai"
                             << setw(15) << "Thoi Luong"
                             << setw(10) << "Do Tuoi"
                             << setw(15) << "Trang Thai" << endl;
                        cout << string(95, '-') << endl;
                        
                        int startIdx = (currentPage - 1) * itemsPerPage;
                        int endIdx = startIdx + itemsPerPage;
                        if (endIdx > totalMovies) endIdx = totalMovies;
                        
                        for (int i = startIdx; i < endIdx; i++) {
                            cout << left << setw(10) << allMovies[i].getMovieId()
                                 << setw(30) << allMovies[i].getTitle()
                                 << setw(15) << allMovies[i].getGenre()
                                 << setw(15) << to_string(allMovies[i].getDuration()) + " phut"
                                 << setw(10) << allMovies[i].getAgeLimit()
                                 << setw(15) << allMovies[i].getStatus() << endl;
                        }
                        cout << "============================================================================\n";
                        
                        cout << ">> Trang " << currentPage << "/" << totalPages << " | Nhap [N] de sang trang | [P] de quay lai | [0] Thoat: ";
                        cin >> nav;
                        
                        if ((nav == 'N' || nav == 'n') && currentPage < totalPages) {
                            currentPage++;
                        } else if ((nav == 'P' || nav == 'p') && currentPage > 1) {
                            currentPage--;
                        }
                    } while (nav != '0');
                }
            }
        } // --- DAY LA DAU NGOAC DONG CUA phan (choice == 1) ---
        
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

            vector<Showtime> allST = showtimeMgr.getAll();
            int maxSTId = 0;
            for (const auto& st : allST) {
                string currentId = st.getShowtimeId();
                if (currentId.length() >= 3 && currentId.substr(0, 2) == "ST") {
                    int num = atoi(currentId.substr(2).c_str());
                    if (num > maxSTId) maxSTId = num;
                }
            }
            int nextSTId = maxSTId + 1;
            id = "ST" + string(nextSTId < 10 ? "0" : "") + to_string(nextSTId);
            cout << ">> He thong tu dong cap Ma suat chieu: " << id << endl;
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
        else if (choice == 3) {
            showTicketHistory(""); 
            system("pause");
        }
    } while (choice != 0);
}

// Khai bao ten ham chinh xac la thuoc ve class Menu
void Menu::showTicketHistory(string username) {
    ifstream file("data/tickets.txt");
    if (!file.is_open()) {
        cout << ">> Loi: Khong the mo file lich su dat ve!" << endl;
        return;
    }

    string line;
    bool found = false;
    cout << "\n==================== LICH SU DAT VE ====================\n";
    
    while (getline(file, line)) {
        if (username == "" || line.find(username) != string::npos) {
            cout << line << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << ">> Chua co lich su dat ve nao!" << endl;
    }
    cout << "========================================================\n";
    file.close();
}