#include <iostream>
#include "menu_functions.h"

/**
 * Prints a help message
 */
void printHelp()
{
    std::cout << "Help - Choose option from the menu" << std::endl;
    std::cout << "and follow the instructions on the screen." << std::endl;        
}
void printExchangeStats()
{
    std::cout << "Some stats" << std::endl;
}
void makeAnOffer()
{
    std::cout << "Place an offer." << std::endl;
}
void makeABid()
{
    std::cout << "Place a bid" << std::endl;
}
void printWallet()
{
    std::cout << "My wallet" << std::endl;
}
void goToNextTimeFrame()
{
    std::cout << "Go to next timeframe." << std::endl;
}