#include "Menu.h"

int main() {
    AccountManager accountManager("data/users.txt");
    runMainMenu(accountManager);
    return 0;
}