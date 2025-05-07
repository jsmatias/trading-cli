#pragma once
#include <string>

enum class OrderType {bid, ask, unknown, asksale, bidsale};

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
           OrderType type,
           std::string username = "dataset"
        );
        static OrderType stringToOrderBookType(const std::string& orderType);

        friend std::ostream& operator<<(std::ostream& os, OrderBookEntry order);

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderType type;
        std::string username;
};
