#pragma once

#include <string>
#include <map>
#include "order_book.h"


class Wallet
{
    public:
        Wallet() = default;
        /** insert currency to the wallet */
        void insertCurrency(std::string type, double amount);
        /** remove currency to the wallet */
        bool removeCurrency(std::string type, double amount);
        /** check if the wallet contains this much currency or more */
        bool containsCurrency(std::string type, double amount);
        /** check if an order can be fulfilled */
        bool canFulfillOrder(const OrderBookEntry& order);
        /** process a sale order */
        void processSale(const OrderBookEntry& sale);
        /** generate a string representation of the wallet */
        std::string toString();

        friend std::ostream& operator<<(std::ostream& os, Wallet& wallet);

    private:
        std::map<std::string, double> currencies;
};