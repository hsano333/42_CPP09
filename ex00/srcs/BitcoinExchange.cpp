#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

using std::map;
using std::time_t;
using std::string;
using std::cout;
using std::endl;
using std::fstream;

BitcoinExchange::BitcoinExchange()
{
    this->load_database();
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& bce)
{
    *this = bce;
    /*
    map<time_t, string>::const_iterator ite = bce.database.begin();
    map<time_t, string>::const_iterator end = bce.database.end();
    for(; ite != end;ite++)
    {
        database.insert(*ite);
    }
    */
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &bce)
{
    if (this != &bce)
        return (*this);
    this->database.clear();
    map<time_t, string>::const_iterator ite = bce.database.begin();
    map<time_t, string>::const_iterator end = bce.database.end();
    for(; ite != end;ite++)
    {
        database.insert(*ite);
    }
    return (*this);
}

void BitcoinExchange::load_database()
{
    string filepath = "data.csv";
    string buf;
    fstream dbfile;

    dbfile.open(filepath, std::ios::in);
    if(!dbfile.is_open())
    {
        cout << "Error: could not open data.csv file" << endl;
        cout << "Put the file in the same place as the executable file(btc)" << endl;
        throw std::exception();
    }
    //agnore header
    getline(dbfile, buf);
    while (!dbfile.eof())
    {
        getline(dbfile, buf);

    }
}
