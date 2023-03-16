#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H

#include <map>
#include <ctime>
#include <sstream>
#include <string>

class BitcoinExchange
{
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &bce);
        BitcoinExchange& operator=(const BitcoinExchange &bce);
        ~BitcoinExchange();
        void display_exchanged_rate(std::string input_file_path);

    private:
        void load_database();
        std::time_t convert_date(std::string buf, std::string delimiter);
        std::string convert_value(std::string buf, std::string delimiter);
        std::time_t search_date(std::time_t date);
        std::string calc(std::string rate, std::string input_value);
        std::map<std::time_t , std::string> database;
        bool is_valid_date(int year, int month, int day);
        bool is_leap_year(int year);
};
#endif
