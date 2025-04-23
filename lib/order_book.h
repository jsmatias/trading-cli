#pragma once

#include <string>
#include <vector>
#include "book_entry.h"

class OrderBook
{
    public:
        /** Construct the order book reading the data from a file*/
        OrderBook(const std::string& filename);
        /** Return a vector with all known products*/
        std::vector<std::string> getKnownProducts();
        /** Return a vector of orders according to the given filters*/
        std::vector<OrderBookEntry> getOrders(
            const OrderType& type, 
            const std::string& product,
            const std::string& timestamp
        );
        /** Return the earliest time in the book */
        std::string getEarliestTime();
        /** Return the next timestamp for a given timestamp */
        std::string getNextTime(const std::string& timestamp);
        /** Return the price of highest bid for a given orders subset */
        static double getHighPrice(const std::vector<OrderBookEntry>& orders_subset);
        /** Return the price of lowest bid for a given orders subset */
        static double getLowPrice(const std::vector<OrderBookEntry>& orders_subset);

    private:
        std::vector<OrderBookEntry> orders;
};
