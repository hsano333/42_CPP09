#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdlib.h>
#include <ios>
#include <iomanip>

using std::map;
using std::time_t;
using std::string;
using std::cout;
using std::endl;
using std::fstream;
using std::exception;
using std::stringstream;
//using std::stoi;

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
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &bce)
{
    if (this == &bce)
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

string BitcoinExchange::convert_value(string buf, string delimiter)
{
    size_t pos = buf.find(delimiter);
    if (pos == string::npos)
    {
        cout << "Warning database file(data.csv):invalid format. This line is ignored" << endl;
        return "";
    }
    return (buf.substr(pos+delimiter.size()));
}

bool BitcoinExchange::is_leap_year(int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
                return (true);
            return (false);
        }
        return (true);
    }
    return (false);
}

bool BitcoinExchange::is_valid_date(int year, int month, int day)
{
    int last_day_array[] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
    int last_day = last_day_array[month];

    if (day > last_day)
        return (false);
    if (month == 2 && day == 29)
    {
         if(is_leap_year(year))
             return (true);
         else
             return (false);
    }
    return (true);
}

time_t BitcoinExchange::convert_date(string buf, string delimiter)
{
    long year, month, day;

    size_t year_pos = buf.find("-");
    if (year_pos == string::npos)
    {
        cout << "Error: bad input => " << buf << endl;
        return (0);
    }
    size_t month_pos = buf.find("-", year_pos + 1);
    if (month_pos == string::npos)
    {
        cout << "Error: bad input => " << buf << endl;
        return (0);
    }
    size_t day_pos = buf.find(delimiter, month_pos + 1);
    if (day_pos == string::npos)
    {
        cout << "Error: bad input => " << buf << endl;
        return (0);
    }
    try
    {
        int base = 10;
        char *endptr;

        year = strtol(buf.substr(0, year_pos).c_str(), &endptr, base);
        if (errno == ERANGE || *endptr != '\0')
            throw std::exception();
        month = strtol(buf.substr(year_pos+1, month_pos - year_pos-1).c_str(), &endptr, base);
        if (errno == ERANGE || *endptr != '\0')
            throw std::exception();
        day = strtol(buf.substr(month_pos+1, day_pos - month_pos-1).c_str(), &endptr, base);
        if (errno == ERANGE || *endptr != '\0')
            throw std::exception();
        if (year < 1900 || year > 3000)
            throw std::exception();
        if (month <= 0 || month > 12)
            throw std::exception();
        if (day <= 0 || month > 31)
            throw std::exception();
        if(!this->is_valid_date(year, month, day))
            throw std::exception();
    } 
    catch (exception &e)
    {
        cout << "Error: bad date input => " << buf << endl;
        return (0);
    }
    struct tm tmp_date={};
    tmp_date.tm_year = year - 1900;
    tmp_date.tm_mon = month - 1;
    tmp_date.tm_mday = day;
    return (mktime(&tmp_date));
}

void BitcoinExchange::load_database()
{
    std::string filepath = "data.csv";
    string buf;
    fstream dbfile;

    dbfile.open(filepath.c_str(), std::ios::in);
    if(!dbfile.is_open())
    {
        cout << "Error: could not open data.csv file" << endl;
        cout << "Put the file in the same place as the executable file(btc)" << endl;
        throw std::ios_base::failure("Error: could not open " + filepath);
    }
    //ignore header
    getline(dbfile, buf);
    time_t tmp_date;
    string tmp_value = "0";
    string delimiter = ",";
    while (!dbfile.eof())
    {
        if (!getline(dbfile, buf))
                break ;
        tmp_date = this->convert_date(buf, delimiter);
        if (tmp_date == 0)
            continue;
        tmp_value = this->convert_value(buf, delimiter);
        if (tmp_value == "")
            continue;
        database.insert(make_pair(tmp_date, tmp_value));
    }
    dbfile.close();
}

time_t BitcoinExchange::search_date(time_t date)
{
    //time_t indicated_date;
    std::map<std::time_t , std::string>::iterator ite = this->database.begin();
    std::map<std::time_t , std::string>::iterator end = this->database.end();
    for (; ite != end; ite++)
    {
        if ((*ite).first == date)
            break;
        else if ((*ite).first > date)
        {
            if (ite != this->database.begin())
                ite--;
            break;
        }
    }

    if (ite == end)
        ite--;
    return (*ite).first;
}

string BitcoinExchange::calc(string rate, string input_value)
{
    string rval;
    int base = 10;
    char *endptr;
    stringstream ss;
    ss.clear();

    if (rate.find(".") || input_value.find("."))
    {
            double rate_val = strtod(rate.c_str(), &endptr);
            if (errno == ERANGE)
                throw std::range_error("Error: out of range");
            else if (*endptr != '\0')
                throw std::exception();
            else if (rate_val < 0)
                throw std::range_error("Error: not a positive number.");
            double input_val = strtod(input_value.c_str(), &endptr);
            if (input_val >= 1000)
                throw std::range_error("Error: too large a number.");
            else if (errno == ERANGE)
                throw std::range_error("Error: out of range");
            else if (*endptr != '\0')
                throw std::exception();
            else if (input_val <= 0)
                throw std::range_error("Error: not a positive number.");
            ss  << std::fixed << std::setprecision(3) << rate_val * input_val;
            return (ss.str());
    }
    else
    {
            long rate_val = strtol(rate.c_str(), &endptr, base);
            if (errno == ERANGE)
                throw std::range_error("Error: out of range");
            else if (*endptr != '\0')
                throw std::exception();
            else if (rate_val <= 0)
                throw std::range_error("Error: not a positive number.");
            long input_val= strtol(input_value.c_str(), &endptr, base);
            if (input_val >= 1000)
                throw std::range_error("Error: too large a number. No.2");
            else if (errno == ERANGE)
                throw std::range_error("Error: out of range");
            else if (*endptr != '\0')
                throw std::exception();
            else if (input_val <= 0)
                throw std::range_error("Error: not a positive number.");
            ss  << std::fixed << std::setprecision(3) << rate_val * input_val;
            return (ss.str());
    }
    return (rval);
}

void BitcoinExchange::display_exchanged_rate(std::string input_file_path)
{
    fstream infile;
    string buf;

    infile.open(input_file_path.c_str(), std::ios::in);
    if(!infile.is_open())
    {
        cout << "Error: could not open data.csv file" << endl;
        cout << "Put the file in the same place as the executable file(btc)" << endl;
        throw std::ios_base::failure("Error: could not open " + input_file_path);
    }
    //ignore header
    getline(infile, buf);
    time_t input_date;
    string input_value;
    string delimiter = " | ";
    time_t indicated_date;
    string rate_str;
    string exchanged_rate;
    while (!infile.eof())
    {
        if (!getline(infile, buf))
                break ;
        input_date = this->convert_date(buf, delimiter);
        if (input_date == 0)
            continue;
        input_value = this->convert_value(buf, delimiter);
        if (input_value == "")
            continue;
        indicated_date = this->search_date(input_date);
        try
        {
            rate_str = this->database.at(indicated_date);
        }
        catch (std::exception &e)
        {
            cout << "map?:" << indicated_date << endl;
            cout << e.what() << endl;
            cout << "map?" << endl;
        }
        try
        {
            exchanged_rate = this->calc(rate_str, input_value);
            cout << buf.substr(0, buf.find(delimiter)) << " => " << input_value << " = " << exchanged_rate << endl;
        }
        catch (std::exception &e)
        {
            cout << e.what() << endl;
        }
    }
    infile.close();
}
