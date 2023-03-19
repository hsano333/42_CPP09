#include "RPN.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>
using std::string;
using std::stack;
using std::cout;
using std::endl;

/*
#include <stdio.h>
__attribute__((destructor)) void f(void){
    system("leaks RPN");
}
*/

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
            result = rpn.calc(tmp);
        }
        cout << result << endl;
    }
    catch(std::range_error &e){
        cout << e.what() << endl;
        return (EXIT_FAILURE);
    }
    catch(std::exception &e){
        cout << "Error" << endl;
        return (EXIT_FAILURE);
    }
    return (0);
}
