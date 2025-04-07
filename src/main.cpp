#include <iostream>
#include "../lib/menu.h"

int main()
{
    int choice;
    while (true)
    {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "Get ready to start trading!" << std::endl;
        printMenu();
        choice = getUserChoice();
        processChoice(choice);
        
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cin.get();
    }

    return 0;
}