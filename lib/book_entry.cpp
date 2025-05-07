#include <iostream>
#include <string>
#include <iostream>
#include <iomanip>

#include "book_entry.h"

std::ostream& operator<<(std::ostream& os, const OrderType& orderType) {
    switch (orderType) {
        case OrderType::bid:     os << "bid"; break;
        case OrderType::ask:     os << "ask"; break;
        case OrderType::asksale: os << "asksale"; break;
        case OrderType::bidsale: os << "bidsale"; break;
        default:                 os << "unknown"; break;
    }
    return os;
}

OrderBookEntry::OrderBookEntry
(
    double price,
    double amount,
    const std::string& timestamp,
    const std::string& product,
    OrderType type,
    std::string username
) : 
    price{price}, 
    amount{amount}, 
    timestamp{timestamp}, 
    product{product}, 
    type{type},
    username{username}
{}

OrderType OrderBookEntry::stringToOrderBookType(const std::string& orderType)
{
    if (orderType == "bid") return OrderType::bid;
    if (orderType == "ask") return OrderType::ask;
    if (orderType == "bidsale") return OrderType::bidsale;
    if (orderType == "asksale") return OrderType::asksale;
    return OrderType::unknown;
}

std::ostream& operator<<(std::ostream& os, OrderBookEntry order)
{
    os << std::left << std::setw(20) << order.timestamp << " ";
    os << std::left << std::setw(10) << order.product << " ";
    os << std::right << std::setw(20) << std::fixed << std::setprecision(6) << order.amount << " ";
    os << std::right << std::setw(20) << std::fixed << std::setprecision(6) << order.price << " ";
    os << std::left << std::setw(10) << order.username;
    os << std::endl;
    return os;
}
