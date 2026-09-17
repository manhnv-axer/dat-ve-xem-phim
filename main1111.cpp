#define NOMINMAX // Ngăn macro min/max của Windows
#include <windows.h>

#include <iostream>
#include "Core/Menu.h"

// Không dùng using namespace std; ở đây để tránh xung đột kiểu byte toàn cục

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Menu appMenu;
    appMenu.run();

    return 0;
}