
#include "PmergeMe.hpp"
#include <iostream>
#include <cstdio>
#include <errno.h>
#include <stdlib.h>
using std::cout;
using std::endl;

#include <stdio.h>
__attribute__((destructor)) void f(void){
    system("leaks PmergeMe");
}

int main(int argc, char **argv)
{
    size_t size = argc / 128;
    double unit =  (1000000 / CLOCKS_PER_SEC);
    if (argc < 8)
        size = 1;
    else
        size = argc / 4;

    PmergeMe pmerge;
    if (argc <= 1)
    {
        cout << "Error" << endl;
        return (EXIT_FAILURE);
    }
    int i = 1;
    while(i < argc)
    {
        char *endptr;
        int base = 10;
        long long value = strtoll(argv[i], &endptr, base);
        if (errno == ERANGE || *endptr != '\0')
        {
            cout << "Error:invalid value [" << argv[i] << "]" << endl;
            return (EXIT_FAILURE);
        }
        else if (value <= 0)
        {
            cout << "Error:out of range [" << argv[i] << "]  (> 0) " << endl;
            return (EXIT_FAILURE);
        }
        pmerge.push(value);
        i++;
    }
    cout << "Before:    ";
    pmerge.print_all();
    clock_t vector_clock = pmerge.sort(VECTOR, size);
    clock_t list_clock = pmerge.sort(LIST, size);
    cout << "After :    ";
    pmerge.print_all_sorted();

    cout << "Time to process a range of ";
    cout << pmerge.size() << " elements with std::[Vector] : ";
    cout << std::fixed << std::setprecision(0) << vector_clock * unit << " us" << endl;
    //cout << vector_clock << " us" << endl;

    cout << "Time to process a range of ";
    cout << pmerge.size() << " elements with std::[List]   : ";
    cout << std::fixed << std::setprecision(0) << list_clock * unit << " us" << endl;

    clock_t test = clock();
    cout << "test: per_sec=" << CLOCKS_PER_SEC << ", unit=" << unit << endl;
    cout << "test: clock=" << test << endl;
}
