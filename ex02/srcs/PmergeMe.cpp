#include "PmergeMe.hpp" 
#include <iostream>
using std::cout;
using std::endl;


PmergeMe::PmergeMe()
{
}
PmergeMe::~PmergeMe()
{
}
PmergeMe::PmergeMe(const PmergeMe& merge)
{
    *this = merge;
}
PmergeMe& PmergeMe::operator=(const PmergeMe& pmerge)
{
    if (this != &pmerge)
        return (*this);
    this->vector.clear();
    this->list.clear();
    std::vector<size_t>::const_iterator ite_v = pmerge.vector.begin();
    std::vector<size_t>::const_iterator end_v = pmerge.vector.end();
    std::list<size_t>::const_iterator ite_l = pmerge.list.begin();
    std::list<size_t>::const_iterator end_l = pmerge.list.end();
    for (; ite_v != end_v; ite_v++)
    {
        this->vector.push_back(*ite_v);
    }
    for (; ite_l != end_l; ite_l++)
    {
        this->vector.push_back(*ite_l);
    }
    return (*this);
}

void PmergeMe::push(size_t value)
{
    this->vector.push_back(value);
    this->list.push_back(value);
}

clock_t PmergeMe::sort_in_vector(size_t size)
{
    clock_t begin;
    clock_t end;
    begin = clock();

    size++;
    size++;
    size++;
    size++;
    (void)size;
    end = clock();
    return (end - begin);
}

clock_t PmergeMe::sort_in_list(size_t size)
{
    clock_t begin;
    clock_t end;
    begin = clock();

    (void)size;
    end = clock();
    return (end - begin);
}

clock_t PmergeMe::sort(Container container, size_t size)
{
    clock_t clock = 0;
    if (container == VECTOR)
    {
        clock = sort_in_vector(size);
    }
    else if (container == LIST)
    {
        clock = sort_in_list(size);
    }
    return (clock);
}

size_t PmergeMe::size()
{
    return (this->vector.size());
}

void PmergeMe::print_all()
{
    std::vector<size_t>::const_iterator ite = this->vector.begin();
    std::vector<size_t>::const_iterator end = this->vector.end();
    for (; ite != end; ite++)
    {
        cout << *ite << " " ;

    }

}
