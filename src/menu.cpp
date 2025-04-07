#include <iostream>
#include "menu.h"
#include "../include/menu_functions.h"

void printMenu ()
{
    std::cout << "1. Print help" << std::endl;
    std::cout << "2. Print exchange stats" << std::endl;
    std::cout << "3. Make an offer" << std::endl;
    std::cout << "4. Make a bid" << std::endl;
    std::cout << "5. Print wallet" << std::endl;
    std::cout << "6. Continue" << std::endl;

    std::cout << "=========================" << std::endl;
}

int getUserChoice()
{
    int choice;
    std::cout << "Type in 1-6" << std::endl;
    std::cout << ">> ";
    std::cin >> choice;
    return choice;
}

void processChoice(int choice)
{
    switch (choice)
    {
        case 1:
            printHelp();
            break;
        case 2:
            printExchangeStats();
            break;
        case 3:
            makeAnOffer();
            break;
        case 4:
            makeABid();
            break;
        case 5:
            printWallet();
            break;
        case 6:
            goToNextTimeFrame();
            break;
        default:
            std::cout << "Invalid choice! Choose 1-6." << std::endl;
            break;
    }
}