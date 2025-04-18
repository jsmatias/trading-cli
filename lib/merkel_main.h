#pragma once
#include <vector>
#include "book_entry.h"

class MerkelMain
{
    public:
        MerkelMain() = default;
        /** Call this method to start the sim. */
        void init();

    private:
        std::vector<OrderBookEntry> book{};

        void loadOrderBook();
        void printExchangeStats();
        void printHelp();
        void printMenu();
        void printWallet();
        void makeABid();
        void makeAnOffer();
        void processChoice(int choice);
        void goToNextTimeFrame();
        int getUserChoice();
};
