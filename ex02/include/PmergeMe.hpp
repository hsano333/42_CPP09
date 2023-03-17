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
        void print_all_sorted();
        clock_t sort(Container container, size_t size);
        size_t size();
    private:
        std::vector<size_t> vector;
        std::list<size_t> list;
        std::vector<size_t> *sorted_vector;
        std::list<size_t> *sorted_list;
        clock_t sort_in_vector(size_t size);
        clock_t sort_in_list(size_t size);
        //std::vector<size_t>* insert_sort_in_vector(const std::vector<size_t> &vec );
        //void insert_sort_in_vector(const std::vector<size_t> &vec );
        std::vector<size_t>* merge_sort_in_vector(std::vector<size_t> *vec1, std::vector<size_t> *vec2);
        void make_divided_vector(std::vector<std::vector<size_t>* >&divided, size_t size);
        void repeat_merge_sort_in_vector(std::vector<std::vector<size_t>* >&divided);
};

#endif
