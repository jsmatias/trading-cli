#include <string>
#include <map>
#include <iostream>

#include "wallet.h"
#include "book_entry.h"
#include "csv_reader.h"

/** insert currency to the wallet */
void Wallet::insertCurrency(std::string type, double amount)
{
    if (amount < 0) throw std::exception{};
    if (currencies.count(type) == 0) currencies[type] = 0.0;
    currencies[type] += amount;
}

/** remove currency to the wallet */
bool Wallet::removeCurrency(std::string type, double amount)
{
    if (amount < 0) throw std::exception{};
    if (!containsCurrency(type, amount)) return true;
    currencies[type] -= amount;
    return true;
}
/** check if the wallet contains this much currency or more */
bool Wallet::containsCurrency(std::string type, double amount)
{
    if (currencies.count(type) == 0 || currencies[type] < amount) return false;
    return true;
}

bool Wallet::canFulfillOrder(const OrderBookEntry& order)
{

    if (order.type != OrderType::ask && order.type != OrderType::bid)
    {
        std::cout << "Wallet::canFulfillOrder - Invalid Order type: " << order.type << std::endl;
        throw std::exception{}; 
    }

    double amount;
    std::string currency;

    std::vector<std::string> currencyPair = CSVReader::tokenise(order.product, "/");
    if (order.type == OrderType::ask)
    { 
        currency = currencyPair[0];
        amount = order.amount;
        std::cout << "Wallet::canFulfillOrder - ask: ";
    }
    if (order.type == OrderType::bid) 
    {
        currency = currencyPair[1];
        amount = order.amount * order.price;
        std::cout << "Wallet::canFulfillOrder - bid: ";
    }
    std::cout << "order.product: " << order.product;
    std::cout << " currency: " << currency;
    std::cout << " amount: " << amount << std::endl;
    
    return containsCurrency(currency, amount);
}

void Wallet::processSale(const OrderBookEntry& sale)
{
    std::vector<std::string> currencyPair = CSVReader::tokenise(sale.product, "/");
    std::string incomingCurrency;
    std::string outgoingCurrency;
    double incomingAmount;
    double outgoingAmount;

    std::cout << "Processing sale: ";
    // if ask
    if (sale.type == OrderType::asksale)
    {
        outgoingCurrency = currencyPair[0];
        outgoingAmount = sale.amount;
        incomingCurrency = currencyPair[1];
        incomingAmount = sale.amount * sale.price;
        std::cout << "Selling: " << outgoingAmount << " " << outgoingCurrency << std::endl;
        std::cout << "For: " << incomingAmount << " " << incomingCurrency << std::endl;
    }
    // if bid
    if (sale.type == OrderType::bidsale)
    {
        outgoingCurrency = currencyPair[1];
        outgoingAmount = sale.amount * sale.price;
        incomingCurrency = currencyPair[0];
        incomingAmount = sale.amount;
        std::cout << "Buying: " << incomingAmount << " " << incomingCurrency << std::endl;
        std::cout << "For: " << outgoingAmount << " " << outgoingCurrency << std::endl;
    }
    insertCurrency(incomingCurrency, incomingAmount);
    removeCurrency(outgoingCurrency, outgoingAmount);
}

/** generate a string representation of the wallet */
std::string Wallet::toString()
{
    std::string str{"You have:\n"};
    for (const auto& currency : currencies)
    {
        str += "+ " + std::to_string(currency.second) + " " + currency.first + "\n";
    };
    return str;
}

std::ostream& operator<<(std::ostream& os, Wallet& wallet)
{
    os << wallet.toString();
    return os;
}
