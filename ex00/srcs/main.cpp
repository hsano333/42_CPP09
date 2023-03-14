#include "BitcoinExchange.hpp"
#include <iostream>
#include <map>
#include <stdlib.h>

using std::string;
using std::cout;
using std::endl;
using std::map;
using std::exception;

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
    return (0);
}
