#include <fstream>
#include <iostream>
#include "csv_reader.h"

std::vector<OrderBookEntry> CSVReader::readCSV(const std::string& fileName)
{
    std::ifstream csvFile{fileName};
    std::vector<OrderBookEntry> orders;

    if (!csvFile.is_open())
    {
        std::cout << "Error opening file: " << fileName << std::endl;
        throw std::exception{};
    }

    std::string line;
    while (std::getline(csvFile, line))
    {
        try
        {
            orders.push_back(stringsToOBE(tokenise(line, ",")));
        }
        catch(const std::exception& e)
        {   
            std::cerr << e.what() << std::endl;
            std::cout << "Bad line format: " << line << std::endl;
            continue;
        }
        
    }
    return orders;
}

std::vector<std::string> CSVReader::tokenise(const std::string& line, const char* separator)
{
    std::vector<std::string> tokens;
    int start, end;
    start = line.find_first_not_of(separator, 0);
    do
    {    
        end = line.find_first_of(separator, start);
        if (end == start || start == line.length()) break;
        tokens.push_back
        (
            (end != std::string::npos) ? 
            line.substr(start, end - start) : 
            line.substr(start, line.length() - start)
        );
        start = end + 1;
    } while (end != std::string::npos);
    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(const std::vector<std::string>& tokens)
{
    std::string timestamp;
    std::string product;
    OrderType type;
    double price, amount;

    if (tokens.size() != 5)
    {
        std::cerr << "CSVReader::stringsToOBE - Invalid data format" << std::endl;
        throw std::exception{};
    }

    timestamp = tokens[0];
    product = tokens[1];
    type = OrderBookEntry::stringToOrderBookType(tokens[2]);
    try 
    {
        price = std::stod(tokens[3]); 
        amount = std::stod(tokens[4]); 
    }
    catch(const std::exception& e)
    {
        std::cout << "Bad double: " << tokens[3] << std::endl;
        std::cout << "Bad double: " << tokens[4] << std::endl;
        throw;
    }
    
    OrderBookEntry obe {
        price,
        amount,
        timestamp,
        product,
        type  
    };
    return obe;
}

OrderBookEntry CSVReader::stringsToOBE(
    std::string price,
    std::string amount,
    std::string timestamp,
    std::string product,
    OrderType orderType
)
{
    double priceDouble, amountDouble;

    try 
    {
        priceDouble = std::stod(price); 
        amountDouble = std::stod(amount); 
    }
    catch(const std::exception& e)
    {
        std::cout << "CSVReader::stringsToOBE Bad double: " << price << std::endl;
        std::cout << "CSVReader::stringsToOBE Bad double: " << amount << std::endl;
        throw;
    }
    OrderBookEntry obe {
        priceDouble,
        amountDouble,
        timestamp,
        product,
        orderType
    };
    return obe;
}