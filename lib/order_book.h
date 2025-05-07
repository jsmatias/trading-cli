#pragma once

#include <string>
#include <vector>
#include "book_entry.h"

class OrderBook
{
    public:
        /** Construct the order book reading the data from a file*/
        OrderBook(const std::string& filename);
        /** Return a vector with all known products*/
        std::vector<std::string> getKnownProducts();
        /** Return a vector of orders according to the given filters*/
        std::vector<OrderBookEntry> getOrders(
            const OrderType& type, 
            const std::string& product,
            const std::string& timestamp
        );
        /** Return the earliest time in the book */
        std::string getEarliestTime();
        /** Return the next timestamp for a given timestamp */
        std::string getNextTime(const std::string& timestamp);
        /** Return the highest price for a given orders subset */
        static double getHighPrice(const std::vector<OrderBookEntry>& orders);
        /** Return the lowest price for a given orders subset */
        static double getLowPrice(const std::vector<OrderBookEntry>& orders);
        /** Return the next timestamp for a given timestamp */
        std::string getPreviousTime(const std::string& timestamp);
        /** Return the close price for a given orders subset */
        static double getClosePrice(const std::vector<OrderBookEntry>& orders);
        /**
         * Computes the Simple Moving Average (SMA) over a specified number of periods.
         *
         * This method calculates the SMA-n for a given type, product, and timestamp.
         * The result represents the average value of the specified type over the past `period`
         * intervals leading up to the given `timestamp`.
         *
         * @param type      (e.g., bid or ask) - In reality the calculation should be done for a
         *                  filled orders, but this is fine for exercise.
         * @param product   The product identifier pair.
         * @param timestamp The timestamp at which the SMA is evaluated. The calculation
         *                  includes the values at this timestamp and the previous `period - 1` intervals.
         * @param period    The number of intervals over which to compute the average.
         *                  Must be greater than 0.
         *
         * @return The computed simple moving average as a double. If there is insufficient data
         *         to compute the average, the function may return NaN.
         */
        double getSimpleMovingAverage(
            const OrderType& type, 
            const std::string& product,
            const std::string& timestamp,
            const unsigned int& period
        );

        void insertOrder(const OrderBookEntry& order);
        static bool compareByTimestamp(const OrderBookEntry& e1, const OrderBookEntry& e2)
        {
            return e1.timestamp < e2.timestamp;
        };
        static bool compareByPriceAsc(const OrderBookEntry& e1, const OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        };
        static bool compareByPriceDesc(const OrderBookEntry& e1, const OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        };

        std::vector<OrderBookEntry> matchAsksToBids(const std::string& product, const std::string& timestamp);

        friend std::ostream& operator<<(std::ostream& os, OrderBook orderBook);

    private:
        std::vector<OrderBookEntry> orders;
};
