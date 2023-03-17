#include "RPN.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>
using std::string;
using std::stack;
using std::cout;
using std::endl;
using std::vector;

int main(int argc, char **argv)
{
    Rpn rpn;
    ssize_t result = 0;
    try{
        string tmp;
        if (argc == 2)
        {
            tmp = string(argv[1]);
            result = rpn.calc(tmp);
        }
        else if (argc > 2)
        {
            int i=1;
            while (i < argc)
            {
                tmp += argv[i];
                tmp += " ";
                i++;
            }
            //cout << "tmp=" << tmp << endl;
            result = rpn.calc(tmp);
        }
        cout << result << endl;
        //string tmp = argv[1];
        //rpn.load(tmp);
        //rpn.calc(tmp);
    }
    catch(std::range_error &e){
        cout << e.what() << endl;
        return (EXIT_FAILURE);
    }
    catch(std::exception &e){
        cout << "Error" << endl;
        return (EXIT_FAILURE);
    }

    std::vector<size_t> test1;
    std::vector<size_t> test2;

    test1.push_back(1);
    test1.push_back(2);
    test1.push_back(3);
    test1.push_back(4);
    test1.push_back(5);
    test2.push_back(10);
    test2.push_back(11);
    test2.push_back(12);
    test2.push_back(13);
    test2.push_back(14);
    size_t tmp = 1;
    test1.insert(test1.begin()+2,tmp); 
    return (0);
}
