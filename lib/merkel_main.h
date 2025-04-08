#pragma once

class MerkelMain
{
    public:
        MerkelMain();
        void init();
        void printMenu();
        int getUserChoice();
        void processChoice(int choice);
        void printHelp();
        void printExchangeStats();
        void makeAnOffer();
        void makeABid();
        void printWallet();
        void goToNextTimeFrame();
};
