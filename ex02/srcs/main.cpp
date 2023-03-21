/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:08:36 by hsano             #+#    #+#             */
/*   Updated: 2023/03/21 19:18:15 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "PmergeMe.hpp"
#include <iostream>
#include <cstdio>
#include <errno.h>
#include <stdlib.h>
using std::cout;
using std::endl;

/*
#include <stdio.h>
__attribute__((destructor)) void f(void){
    system("leaks PmergeMe");
}
*/

int main(int argc, char **argv)
{
    if (argc <= 2)
    {
        cout << "Error" << endl;
        return (EXIT_FAILURE);
    }

    size_t size = argc / 128;
    double unit =  (1000000 / CLOCKS_PER_SEC);
    if (argc < 8)
        size = 1;
    else if (argc < 512)
        size = argc / 8;
    else if (argc < 8192)
        size = argc / 32;
    else if (argc < 65536)
        size = argc / 128;
    else
        size = argc / 512;

    PmergeMe pmerge;
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
    pmerge.print_all(VECTOR);
    clock_t vector_clock = pmerge.sort(VECTOR, size);
    clock_t list_clock = pmerge.sort(LIST, size);
    cout << "After :    ";
    pmerge.print_all_sorted(VECTOR);
    //pmerge.check_sort();

    cout << "Time to process a range of ";
    cout << pmerge.size() << " elements with std::[Vector] : ";
    cout << std::fixed << std::setprecision(0) << vector_clock * unit << " us" << endl;

    cout << "Time to process a range of ";
    cout << pmerge.size() << " elements with std::[List]   : ";
    cout << std::fixed << std::setprecision(0) << list_clock * unit << " us" << endl;
}
