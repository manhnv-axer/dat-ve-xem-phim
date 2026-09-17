#pragma once

#include <iostream>
#include <limits>
#include <cstdlib>
#include <string>

#ifdef _WIN32
#include <conio.h>
#endif

using namespace std;

class InputHandler {
public:
    static void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        cout << "\033[2J\033[H";
#endif
    }

    static int getInt(const string& prompt, int minValue, int maxValue) {
        while (true) {
            cout << prompt;
            int value;
            if (cin >> value && value >= minValue && value <= maxValue) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Gia tri khong hop le. Vui long nhap lai.\n";
        }
    }

    static double getDouble(const string& prompt, double minValue) {
        while (true) {
            cout << prompt;
            double value;
            if (cin >> value && value >= minValue) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Gia tri khong hop le. Vui long nhap lai.\n";
        }
    }

    static string getLine(const string& prompt) {
        cout << prompt;
        string value;
        getline(cin, value);
        return value;
    }

    static string getPassword(const string& prompt) {
#ifdef _WIN32
        cout << prompt;
        string password;
        while (true) {
            int key = _getch();
            if (key == 13) {
                cout << '\n';
                break;
            }
            if (key == 8) {
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
                continue;
            }
            if (key == 0 || key == 224) {
                _getch();
                continue;
            }
            if (key >= 32 && key <= 126) {
                password.push_back(static_cast<char>(key));
                cout << '*';
            }
        }
        return password;
#else
        return getLine(prompt);
#endif
    }
};
