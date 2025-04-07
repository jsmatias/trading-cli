#include <iostream>
#include <string>
#include <vector>

#include "../lib/menu.h"
#include "../lib/book_entry.h"

int main()
{
    std::vector<OrderBookEntry> book{};
    OrderBookEntry entry1{0.021, 0.58, "2020/03/17 17:01:24.884492", "ETH/BTC", OrderType::bid};
    OrderBookEntry entry2{0.022, 0.8, "2020/03/17 17:01:25.884492", "ETH/BTC", OrderType::ask};

    book.push_back(entry1);
    book.push_back(entry2);


    int choice;
    while (true)
    {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "Get ready to start trading!" << std::endl;
        printMenu();
        choice = getUserChoice();
        processChoice(choice);
        
        for (const OrderBookEntry& entry : book)
        {
            std::cout << entry.timestamp << " " << entry.product << std::endl;
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cin.get();
    }

    return 0;
}