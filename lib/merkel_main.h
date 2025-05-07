#pragma once
#include <vector>

#include "order_book.h"
#include "wallet.h"

class MerkelMain
{
    public:
        MerkelMain() = default;
        /** Call this method to start the sim. */
        void init();

    private:
        void printExchangeStats();
        void printHelp();
        void printMenu();
        void printWallet();
        void makeABid();
        void makeAnAsk();
        void processChoice(int choice);
        void goToNextTimeFrame();
        int getUserChoice();
        
        OrderBook book{"./data/book_of_orders.csv"};
        Wallet wallet;
        std::string currentTime;
};
