
#include <iostream>
#include <string>
#include <vector>
#include "merkel_main.h"
#include "book_entry.h"
#include "csv_reader.h"
#include "order_book.h"


void MerkelMain::init()
{
    currentTime = book.getEarliestTime();
    wallet.insertCurrency("BTC", 10);

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
};

void MerkelMain::printMenu()
{
    std::cout << "1. Print help" << std::endl;
    std::cout << "2. Print exchange stats" << std::endl;
    std::cout << "3. Make an offer" << std::endl;
    std::cout << "4. Make a bid" << std::endl;
    std::cout << "5. Print wallet" << std::endl;
    std::cout << "6. Continue" << std::endl;
    
    std::cout << "=========================" << std::endl;
    std::cout << "Current time: " << currentTime << std::endl;
    std::cout << "Prev time: " << book.getPreviousTime(currentTime) << std::endl;
}

int MerkelMain::getUserChoice()
{
    int choice;
    std::string line;
    std::cout << "Type in 1-6" << std::endl;
    std::cout << ">> ";
    getline(std::cin, line);
    try
    {
        choice = std::stoi(line);
    }
    catch (const std::exception& e)
    {
        return 0;
    }
    std::cout << "You chose option: " << choice << std::endl;
    return choice;
}

void MerkelMain::processChoice(int choice)
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
            makeAnAsk();
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

/**
 * Prints a help message
 */
void MerkelMain::printHelp()
{
    std::cout << "Help - Choose option from the menu" << std::endl;
    std::cout << "and follow the instructions on the screen." << std::endl;        
}
void MerkelMain::printExchangeStats()
{
    std::vector<OrderBookEntry> askEntries;
    std::vector<OrderBookEntry> bidEntries;
    double minAsk;
    double maxBid;

    for (const std::string& prod : book.getKnownProducts())
    {
        askEntries = book.getOrders(OrderType::ask, prod, currentTime);
        bidEntries = book.getOrders(OrderType::bid, prod, currentTime);

        std::cout << " ====== Product: " << prod << std::endl;
        if (!askEntries.empty())
        {
            minAsk = OrderBook::getLowPrice(askEntries);
            std::cout << "  Asks seen: " << askEntries.size() << std::endl;
            std::cout << "  Max ask: " << OrderBook::getHighPrice(askEntries) << std::endl;
            std::cout << "  Min ask: " << minAsk << std::endl;
            std::cout << "  Close ask: " << OrderBook::getClosePrice(askEntries) << std::endl;
            std::cout << "  SMA-7 ask: " << book.getSimpleMovingAverage(OrderType::ask, prod, currentTime, 7) << std::endl;
        }
        else std::cout << "  No ask prices..." << std::endl;

        if (!bidEntries.empty())
        {
            maxBid = OrderBook::getHighPrice(bidEntries);
            std::cout << "  Bids seen: " << bidEntries.size() << std::endl;
            std::cout << "  Max bib: " << maxBid << std::endl;
            std::cout << "  Min bid: " << OrderBook::getLowPrice(bidEntries) << std::endl;
            std::cout << "  Close bid: " << OrderBook::getClosePrice(bidEntries) << std::endl;
            std::cout << "  SMA-7 bid: " << book.getSimpleMovingAverage(OrderType::bid, prod, currentTime, 7) << std::endl;
        }
        else std::cout << "  No bid prices..." << std::endl;
        
        if (!bidEntries.empty() && !askEntries.empty()) std::cout << "  Spread: " << minAsk - maxBid << std::endl;
    }
}
void MerkelMain::makeAnAsk()
{
    std::cout << "Make an ask - enter the amount: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ",");
    if (tokens.size() != 3) 
    {
        std::cout << "Invalid number of tokens! ";
        std::cout << "Make sure your input has product,price and amount separated by commas." << std::endl;
        return;
    }
    try
    {
        OrderBookEntry obe{CSVReader::stringsToOBE(
            tokens[1],
            tokens[2],
            currentTime, 
            tokens[0],
            OrderType::ask
        )};
        if (wallet.canFulfillOrder(obe)) 
        {
            std::cout << "Wallet has enough funds." << std::endl;
            book.insertOrder(obe);
        }
        else 
        {
            std::cout << "Wallet has insufficient funds." << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

}
void MerkelMain::makeABid()
{
    std::cout << "Make an bid - enter the amount: product, price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ",");
    if (tokens.size() != 3) 
    {
        std::cout << "Invalid number of tokens! ";
        std::cout << "Make sure your input has product,price and amount separated by commas." << std::endl;
        return;
    }
    try
    {
        OrderBookEntry obe{CSVReader::stringsToOBE(
            tokens[1],
            tokens[2],
            currentTime, 
            tokens[0],
            OrderType::bid
        )};
        if (wallet.canFulfillOrder(obe)) 
        {
            std::cout << "Wallet has enough funds." << std::endl;
            book.insertOrder(obe);
        }
        else 
        {
            std::cout << "Wallet has insufficient funds." << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }
}
void MerkelMain::printWallet()
{
    std::cout << wallet << std::endl;
}
void MerkelMain::goToNextTimeFrame()
{
    std::cout << "Going to next time frame..." << std::endl;
    
    std::cout << "matching ..." << std::endl;
    std::vector<OrderBookEntry> sales;
    
    for (const std::string& p : book.getKnownProducts())
    {
        sales = book.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (const OrderBookEntry& sale : sales) 
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
        };
    };
    
    currentTime = book.getNextTime(currentTime);
}