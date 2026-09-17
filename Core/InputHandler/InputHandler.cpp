#include "InputHandler.h"

#include <iostream>
#include <limits>
#include <conio.h>
#include <cstdlib>

using namespace std;

int InputHandler::getInt(const string& message, int min, int max)
{
    int value;

    while (true)
    {
        cout << message;

        if (cin >> value && value >= min && value <= max)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Gia tri khong hop le!\n";
    }
}

double InputHandler::getDouble(const string& message, double min)
{
    double value;

    while (true)
    {
        cout << message;

        if (cin >> value && value >= min)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Gia tri khong hop le!\n";
    }
}

string InputHandler::getString(const string& message)
{
    cout << message;

    string value;
    getline(cin, value);

    return value;
}

string InputHandler::getPassword(const string& message)
{
    cout << message;

    string password;
    char key;

    while (true)
    {
        key = _getch();

        // Enter
        if (key == 13)
        {
            cout << '\n';
            break;
        }

        // Backspace
        if (key == 8)
        {
            if (!password.empty())
            {
                password.pop_back();
                cout << "\b \b";
            }

            continue;
        }

        // Ký tự có thể nhập
        if (key >= 32 && key <= 126)
        {
            password += key;
            cout << '*';
        }
    }

    return password;
}

void InputHandler::pause()
{
    cout << "\nNhan Enter de tiep tuc...";

    string temp;
    getline(cin, temp);
}

void InputHandler::clearScreen()
{
    system("cls");
}