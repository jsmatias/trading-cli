#include <iostream>
#include <string>

#include "book_entry.h"

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
