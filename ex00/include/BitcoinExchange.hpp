#include <map>
#include <ctime>

class BitcoinExchange
{
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &bce);
        BitcoinExchange& operator=(const BitcoinExchange &bce);
        ~BitcoinExchange();

    private:
        void load_database();
        std::map<std::time_t , std::string> database;
};
