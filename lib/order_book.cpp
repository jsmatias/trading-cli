#include <map>
#include "csv_reader.h"
#include "order_book.h"


OrderBook::OrderBook(const std::string& filename)
{
    orders = CSVReader::readCSV(filename);
    std::sort (
        orders.begin(), orders.end(), 
        [](const OrderBookEntry& entryI, const OrderBookEntry& entryJ)
        {
            return entryI.timestamp < entryJ.timestamp;
        }
    );
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;
    for (const OrderBookEntry& o : orders)
    {
        prodMap[o.product] = true;
    }
    for (const std::pair<const std::string, bool>& prodPair : prodMap)
    {
        products.push_back(prodPair.first);
    }
    return products;
}
std::vector<OrderBookEntry> OrderBook::getOrders(
    const OrderType& type, 
    const std::string& product,
    const std::string& timestamp
)
{
    std::vector<OrderBookEntry> ordersSub;
    for (OrderBookEntry o : orders)
    {
        if (
            o.type == type && 
            o.product == product && 
            o.timestamp == timestamp
        ) ordersSub.push_back(o);
    }
    return ordersSub;
}

std::string OrderBook::getEarliestTime()
{
    std::string earliestTime{orders[0].timestamp};
    for (const OrderBookEntry& o : orders)
    {
        if (o.timestamp < earliestTime) earliestTime = o.timestamp;
    }
    return earliestTime;
}

std::string OrderBook::getNextTime(const std::string& timestamp)
{
    std::string nextTimestamp{getEarliestTime()};
    for (const OrderBookEntry& e : orders)
    {
        if (e.timestamp > timestamp) 
        {
            nextTimestamp = e.timestamp;
            break;
        }
    }
    return nextTimestamp;
}


double OrderBook::getHighPrice(const std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;
    for (const OrderBookEntry& o : orders)
    {
        max = (o.price > max) ? o.price : max;
    }
    return max;
}

double OrderBook::getLowPrice(const std::vector<OrderBookEntry>& orders)
{
    double min = orders[0].price;
    for (const OrderBookEntry& o : orders)
    {
        min = (o.price < min) ? o.price : min;
    }
    return min;
}

