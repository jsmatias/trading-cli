#include <string>
#include <map>

#include "wallet.h"

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
