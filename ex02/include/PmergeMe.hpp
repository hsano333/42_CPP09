#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <cstdio>
#include <vector>
#include <list>
#include <time.h>
#include <sstream>
#include <iomanip>

enum EContainer{
    VECTOR,
    LIST,
};

typedef enum EContainer Container;

class PmergeMe
{
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe& merge);
        PmergeMe& operator=(const PmergeMe& pmerge);
        void push(size_t i);
        void print_all();
        clock_t sort(Container container, size_t size);
        size_t size();
    private:
        std::vector<size_t> vector;
        std::list<size_t> list;
        clock_t sort_in_vector(size_t size);
        clock_t sort_in_list(size_t size);
};

#endif
