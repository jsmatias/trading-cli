#pragma once
#include <vector>
#include "order_book.h"

class MerkelMain
{
    public:
        MerkelMain() = default;
        /** Call this method to start the sim. */
        void init();

    private:
        OrderBook book{"./data/test.csv"};
        std::string currentTime;

        void printExchangeStats();
        void printHelp();
        void printMenu();
        void printWallet();
        void makeABid();
        void makeAnAsk();
        void processChoice(int choice);
        void goToNextTimeFrame();
        int getUserChoice();
};
