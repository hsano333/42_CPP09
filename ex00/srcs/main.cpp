#include "BitcoinExchange.hpp"
#include <iostream>
#include <map>
#include <stdlib.h>

using std::string;
using std::cout;
using std::endl;
using std::map;
using std::exception;

#include <stdio.h>
__attribute__((destructor)) void f(void){
    system("leaks btc");
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Error: could not open file." << endl;
        return (EXIT_FAILURE);
    }
    try{
        BitcoinExchange bitcoin;
        string input_file = string(argv[1]);
        bitcoin.display_exchanged_rate(input_file);
    } catch (std::ios_base::failure &e) {
        cout << e.what() << endl;
        return (EXIT_FAILURE);
    }catch (exception &e){
        cout << e.what() << endl;
        return (EXIT_FAILURE);
    }


    /*

    struct tm tmp_date={};
    tmp_date.tm_year = 2022 - 1900;
    tmp_date.tm_mon =  2-1;
    tmp_date.tm_mday = 30;
    time_t tmp = mktime(&tmp_date);
    //cout << "2022/2/30:" << tmp << endl;
    tmp_date.tm_mon =  3-1;
    tmp_date.tm_mday = 1;
    tmp = mktime(&tmp_date);
    //cout << "2022/3/1:" << tmp << endl;

    float test1 = 47115;
    float test2 = 1000.1;
    cout << test1 * test2 << endl;
    */
    return (0);
}
