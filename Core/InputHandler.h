#pragma once
#include <iostream>
#include <string>

class InputHandler
{
public:
    int getInt(const string& message, int min, int max);
    double getDouble(const string& message, double min);
    string getString(const string& message);
    string getPassword(const string& message);

    void pause();
    void clearScreen();
};