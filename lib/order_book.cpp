#include <map>
#include <iostream>
#include <algorithm>

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

std::string OrderBook::getPreviousTime(const std::string& timestamp)
{
    std::vector<OrderBookEntry> ordersSortedDescending = orders;
    std::sort (
        ordersSortedDescending.begin(), ordersSortedDescending.end(), 
        [](const OrderBookEntry& entryI, const OrderBookEntry& entryJ)
        {
            return entryI.timestamp > entryJ.timestamp;
        }
    );
    std::string prevTimestamp{ordersSortedDescending[0].timestamp};

    for (const OrderBookEntry& e : ordersSortedDescending)
    {
        if (e.timestamp < timestamp) 
        {
            prevTimestamp = e.timestamp;
            break;
        }
    }
    return prevTimestamp;
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

double OrderBook::getClosePrice(const std::vector<OrderBookEntry>& orders)
{
    return orders[0].price;
}
        
double OrderBook::getSimpleMovingAverage(
    const OrderType& type, 
    const std::string& product,
    const std::string& timestamp,
    const unsigned int& period
)
{
    std::string currentTimestamp = timestamp;
    std::vector<OrderBookEntry> ordersSubset;
    double total{0.0};
    uint i{0};
    
    do
    {
        ordersSubset = getOrders(type, product, currentTimestamp);
        if (!ordersSubset.empty()) total += getClosePrice(ordersSubset);
        else return NAN;
        
        currentTimestamp = getPreviousTime(currentTimestamp);
        ++i;
    } while (i < period);
    return total / period;
}

void OrderBook::insertOrder(const OrderBookEntry& order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBook::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(
    const std::string& product, 
    const std::string& timestamp
){
    // asks = orderbook.asks in this timeframe
    std::vector<OrderBookEntry> asks = getOrders(OrderType::ask, product, timestamp);
    // bids = orderbook.bids in this timeframe
    std::vector<OrderBookEntry> bids = getOrders(OrderType::bid, product, timestamp);

    std::vector<OrderBookEntry> sales;

    // sort asks lowest first
    std::sort(asks.begin(), asks.end(), compareByPriceAsc);
    // sort bids highest first
    std::sort(bids.begin(), bids.end(), compareByPriceDesc);

    for (OrderBookEntry ask : asks) 
    {
        for (OrderBookEntry bid : bids) 
        {
            if (bid.price >= ask.price) // we have a match
            {   
                if (bid.amount == ask.amount) // bid completely clears ask
                {
                    OrderBookEntry sale = OrderBookEntry
                    {
                        ask.price, ask.amount, timestamp, product, OrderType::sale
                    };    
                    sales.push_back(sale);
                    bid.amount = 0.0;
                    ask.amount = 0.0;
                    break;
                }; 
                
                if (bid.amount > ask.amount) // ask is completely gone slice the bid
                {
                    OrderBookEntry sale = OrderBookEntry
                    {
                        ask.price, ask.amount, timestamp, product, OrderType::sale
                    };    
                    sales.push_back(sale);
                    bid.amount -= ask.amount;
                    ask.amount = 0.0;
                    break;
                };
                
                if (bid.amount < ask.amount) // bid is completely gone, slice the ask
                {
                    OrderBookEntry sale = OrderBookEntry
                    {
                        ask.price, bid.amount, timestamp, product, OrderType::sale
                    };    
                    sales.push_back(sale);
                    bid.amount = 0;
                    ask.amount -= bid.amount;
                    continue;
                };
            }   
        };
        
    };
    return sales;
}
