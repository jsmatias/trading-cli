#include <iostream>
#include <string>
#include <iostream>

#include "book_entry.h"

std::ostream& operator<<(std::ostream& os, const OrderType& orderType) {
    switch (orderType) {
        case OrderType::bid:    os << "bid"; break;
        case OrderType::ask:    os << "ask"; break;
        case OrderType::sale:   os << "sale"; break;
        default:                os << "unknown"; break;
    }
    return os;
}

OrderBookEntry::OrderBookEntry
(
    double price,
    double amount,
    const std::string& timestamp,
    const std::string& product,
    OrderType type
) : 
    price{price}, 
    amount{amount}, 
    timestamp{timestamp}, 
    product{product}, 
    type{type}
{}

OrderType OrderBookEntry::stringToOrderBookType(const std::string& orderType)
{
    if (orderType == "bid") return OrderType::bid;
    if (orderType == "ask") return OrderType::ask;
    return OrderType::unknown;
}