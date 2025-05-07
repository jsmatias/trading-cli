#pragma once
#include <string>

enum class OrderType {bid, ask, sale, unknown};

std::ostream& operator<<(std::ostream& os, const OrderType& orderType);

class OrderBookEntry
{
    public:
        /** Create a new OrderBookEntry with the price
         * amount, timestamp, product and order type.
        */
        OrderBookEntry(
           double price,
           double amount,
           const std::string& timestamp,
           const std::string& product,
           OrderType type
        );
        static OrderType stringToOrderBookType(const std::string& orderType);

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderType type;
};
