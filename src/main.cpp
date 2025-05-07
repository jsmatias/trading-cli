#include <iostream>
#include <string>
#include <vector>

#include "../lib/merkel_main.h"
#include "../lib/book_entry.h"

#include "../lib/wallet.h"

int main()
{
    // MerkelMain app{};
    // app.init();
    Wallet wallet{};
    
    std::cout << "Inserting 0.5 BTC" << std::endl;
    wallet.insertCurrency("BTC", 0.5);
    std::cout << wallet << std::endl;    

    std::cout << "Inseting 0.5 BTC" << std::endl;
    wallet.insertCurrency("BTC", 0.5);
    std::cout << wallet << std::endl;

    std::cout << "Removing 0.6 BTC" << std::endl;
    wallet.removeCurrency("BTC", 0.6);
    std::cout << wallet << std::endl;
    
    std::cout << "Trying to remove 0.5 BTC" << std::endl;
    wallet.removeCurrency("BTC", 0.5);
    std::cout << wallet << std::endl;

    std::cout << "Testing containsCurrency('BTC', 1.0)? " << wallet.containsCurrency("BTC", 1.0) << std::endl;
    std::cout << "Testing containsCurrency('BTC', 0.3)? " << wallet.containsCurrency("BTC", 0.3) << std::endl;

    return 0;
}