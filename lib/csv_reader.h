#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "book_entry.h"

class CSVReader
{
    public:
        CSVReader() = default;

        /** parse the sent CSV file into multiple
        * OrderBookEntry objects which should contain
        * lines like:
        * 2020/03/17 17:01:24.884492,ETH/BTC,bid,0.02187305,6.85567013
        */
        static std::vector<OrderBookEntry> readCSV(const std::string& fileName);
        static std::vector<std::string> tokenise(const std::string& line, const char* separator);
        static OrderBookEntry stringsToOBE(const std::vector<std::string>& strings);
        static OrderBookEntry stringsToOBE
        (
            std::string price,
            std::string amount,
            std::string timestamp,
            std::string product,
            OrderType orderType
        );
};