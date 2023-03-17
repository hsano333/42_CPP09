#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::list;


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

std::vector<size_t>* insert_sort_in_vector(const std::vector<size_t>* vec)
{
    cout << "insert_sort_in_vector No.1" << endl;
    std::vector<size_t> *tmp = new std::vector<size_t>;
    //std::vector<size_t>::const_iterator src_ite = vec->begin();
    std::vector<size_t>::const_iterator ite = vec->begin();
    std::vector<size_t>::const_iterator end = vec->end();
    std::vector<size_t>::iterator insert_ite;


    /*
    {
        cout << "test insert sort before" << endl;
        std::vector<size_t>::const_iterator ite2 = vec->begin();
        std::vector<size_t>::const_iterator end2 = vec->end();
        while (ite2 != end2)
        {
            cout << *ite2 << endl;
            ite2++;
        }
    }
    */
    if (vec->size() == 0)
        return (tmp);
    tmp->push_back(*ite);
    if (vec->size() == 1)
    {
        //tmp->push_back(*ite);
        return (tmp);
    }
    ++ite;
    if (tmp->at(0) < *ite)
        tmp->push_back(*ite);
    else
        tmp->insert(tmp->begin(), *ite);
    ++ite;
    while(ite != end)
    {
        size_t i = 0;
    cout << "insert_sort_in_vector No.2 ite=" << *ite << endl;
        for (i = 1;i<tmp->size();i++)
        {
    cout << "insert_sort_in_vector No.3" << endl;
            //if (tmp->size() < 2)
                //break;
    cout << "insert_sort_in_vector No.4" << endl;
            if ((*tmp)[i-1] < *ite && *ite <= (*tmp)[i])
                break;
    cout << "insert_sort_in_vector No.5" << endl;
        }
        //size_t test = 1;
        //tmp->insert(test, i);
        //tmp->insert(ite, *src_ite);

    cout << "insert_sort_in_vector No.6" << endl;
        insert_ite = tmp->begin();
        insert_ite += i;
    cout << "insert_sort_in_vector No.7: *ite=" << *ite << endl;
        tmp->insert(insert_ite, *ite);
    cout << "insert_sort_in_vector No.8" << endl;
        //src_ite++;
        ite++;
    }
    cout << "insert_sort_in_vector No.9" << endl;
    cout << "insert_sort_in_vector No.10" << endl;
    delete vec;
    {
        cout << "test insert sort after" << endl;
        std::vector<size_t>::const_iterator ite2 = tmp->begin();
        std::vector<size_t>::const_iterator end2 = tmp->end();
        while (ite2 != end2)
        {
            cout << *ite2 << endl;
            ite2++;

        }
        cout << "test insert sort after end" << endl;
    }
    //vec = tmp;
    return (tmp);
}

std::vector<size_t>* PmergeMe::merge_sort_in_vector(std::vector<size_t>* vec1, std::vector<size_t>* vec2)
{
    
    std::vector<size_t> *tmp = new std::vector<size_t>;
    std::vector<size_t>::iterator ite1 = vec1->begin();
    std::vector<size_t>::iterator end1 = vec1->end();
    std::vector<size_t>::iterator ite2 = vec2->begin();
    std::vector<size_t>::iterator end2 = vec2->end();
    size_t base_size = vec1->size() + vec2->size();
    while (base_size != tmp->size())
    {
        if (ite1 != end1 && ite2 != end2)
        {
            if (*ite1 < *ite2)
            {
                tmp->push_back(*ite1);
                ite1++;
            }
            else
            {
                tmp->push_back(*ite2);
                ite2++;
            }
        }
        else if (ite1 != end1)
        {
            while(ite1 != end1)
            {
                tmp->push_back(*ite1);
                ite1++;
            }
        }
        else
        {
            while(ite2 != end2)
            {
                tmp->push_back(*ite2);
                ite2++;
            }
        }
    }
    /*
    while(ite != end)
    {
        size_t i = 0;
        for (i = 1;i<tmp->size();i++)
        {
            if (tmp->size() < 2)
                break;
            if ((*tmp)[i-1] < *ite && *ite <= (*tmp)[i])
                break;
        }
        tmp->insert(vec.begin(), i);
        ite++;
    }
    */
    return (tmp);
}

void PmergeMe::make_divided_vector(std::vector<std::vector<size_t>* >& divided, size_t size)
{
    for(size_t i=0;i<divided.size();i++)
    {
        divided[i] = new std::vector<size_t>;
    }
    std::vector<size_t>::const_iterator ite = this->vector.begin();
    std::vector<size_t>::const_iterator end = this->vector.end();

    size_t cnt = 0;
    size_t i = 0;
    while(ite != end)
    {
        if (cnt == size)
        {
            i++;
            cnt = 0;
        }
        else
        {
            cnt++;
        }
        divided[i]->push_back(*ite);
        ite++;
    }
}

void PmergeMe::repeat_merge_sort_in_vector(std::vector<std::vector<size_t>* >& divided)
{
    size_t base_size = this->vector.size();
    std::vector<size_t>* tmp;
        cout << "repeat_merge_sort_in_vector No.1 base_size=" << base_size << ", first_size=" << (*divided.begin())->size() << endl;
    std::vector<std::vector<size_t>* >::iterator end = divided.end();
    std::vector<std::vector<size_t>* >::iterator ite = divided.begin();
    while (base_size != (*divided.begin())->size())
    {
        std::vector<std::vector<size_t>* >::iterator tmp_ite;
        cout << "repeat_merge_sort_in_vector No.2 base_size=" << base_size << ", first_size=" << (*divided.begin())->size() << endl;
        while(ite != end && (*ite)->size() == 0)
            ite++;
        cout << "repeat_merge_sort_in_vector No.3 end=" << &end << endl;
        tmp_ite = ite;
        if (ite != end)
            ite++;
        while(ite != end && (*ite)->size() == 0)
            ite++;
        cout << "repeat_merge_sort_in_vector No.4 tmp_ite=" << &tmp_ite << ", ite=" << &ite  << endl;
        if (ite != end)
        {
            {
                std::vector<std::vector<size_t>* >::iterator end2 = divided.end();
                std::vector<std::vector<size_t>* >::iterator ite2 = divided.begin();
                while(ite2 != end2)
                {
                    cout << "test:*ite1 size()=" << (*ite2)->size() << endl;
                    ite2++;
                }

            }
            tmp = this->merge_sort_in_vector(*tmp_ite, *ite);
            (*ite)->clear();
            //(*tmp_ite)->clear();
            //delete *ite;
            //*ite = NULL;
            cout << "repeat_merge_sort_in_vector No.5 *ite=" << *ite << ", *tmp_ite=" << *tmp_ite << endl;
            cout << "repeat_merge_sort_in_vector No.5-2 *ite_size=" << (*ite)->size() << ", *tmp_ite=" << (*tmp_ite)->size() << endl;
            //while(1)
            {
                std::vector<std::vector<size_t>* >::iterator end2 = divided.end();
                std::vector<std::vector<size_t>* >::iterator ite2 = divided.begin();
                while(ite2 != end2)
                {
                    cout << "test:*ite2 size()=" << (*ite2)->size() << endl;
                    ite2++;
                }

            }
            delete *tmp_ite;
            *tmp_ite = tmp;
        }
        else
            ite = divided.begin();
        cout << "repeat_merge_sort_in_vector No.6 base_size=" << base_size << ", first_size=" << (*divided.begin())->size() << endl;
    }
    this->sorted_vector = divided[0];
}

clock_t PmergeMe::sort_in_vector(size_t size)
{
    clock_t begin_time;
    clock_t end_time;
    begin_time = clock();

    cout << "sort_in_vector No.1" << endl;
    std::vector<std::vector<size_t>* > divided(this->vector.size()/size + 1);
    cout << "sort_in_vector No.2" << endl;
    make_divided_vector(divided, size);
    cout << "sort_in_vector No.3" << endl;
    std::transform(divided.begin(),divided.end(),divided.begin(), insert_sort_in_vector);
    cout << "sort_in_vector No.4" << endl;
    repeat_merge_sort_in_vector(divided);
    cout << "sort_in_vector No.5" << endl;

    end_time = clock();
    return (end_time - begin_time);
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
    cout << endl;
}

void PmergeMe::print_all_sorted()
{
    std::vector<size_t>::const_iterator ite = this->sorted_vector->begin();
    std::vector<size_t>::const_iterator end = this->sorted_vector->end();
    for (; ite != end; ite++)
    {
        cout << *ite << " " ;
    }
    cout << endl;
}
