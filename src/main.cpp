#include <iostream>
#include <string>
#include <vector>

#include "../lib/merkel_main.h"
#include "../lib/book_entry.h"

int main()
{
    // std::vector<OrderBookEntry> book{};
    // OrderBookEntry entry1{0.021, 0.58, "2020/03/17 17:01:24.884492", "ETH/BTC", OrderType::bid};
    // OrderBookEntry entry2{0.022, 0.8, "2020/03/17 17:01:25.884492", "ETH/BTC", OrderType::ask};

    // book.push_back(entry1);
    // book.push_back(entry2);

    MerkelMain app{};
    app.init();
    return 0;
}