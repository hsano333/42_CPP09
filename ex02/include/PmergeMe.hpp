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
        void print_all(Container container);
        void print_all_sorted(Container container);
        clock_t sort(Container container, size_t size);
        size_t size();
        bool check_sort();
        static void print_vector(std::string &str, std::vector<size_t> &vec) ;
        static void print_list(std::string &str, std::list<size_t> &lst);
    private:
        std::vector<size_t> vector;
        std::list<size_t> list;
        std::vector<size_t> *sorted_vector;
        std::list<size_t> *sorted_list;
        clock_t sort_in_vector(size_t size);
        clock_t sort_in_list(size_t size);
        std::vector<size_t>* merge_sort_in_vector(std::vector<size_t> *vec1, std::vector<size_t> *vec2);
        void make_divided_vector(std::vector<std::vector<size_t>* >&divided, size_t size);
        void repeat_merge_sort_in_vector(std::vector<std::vector<size_t>* >&divided);
        std::list<size_t>* merge_sort_in_list(std::list<size_t> *lst1, std::list<size_t> *lst2);
        void make_divided_list(std::list<std::list<size_t>* >&divided, size_t size);
        void repeat_merge_sort_in_list(std::list<std::list<size_t>* >&divided);
};

#endif
