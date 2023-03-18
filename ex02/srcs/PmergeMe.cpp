#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::list;


PmergeMe::PmergeMe() : sorted_vector(NULL) , sorted_list(NULL)
{
}
PmergeMe::~PmergeMe()
{
    delete sorted_vector;
    delete sorted_list;
}
PmergeMe::PmergeMe(const PmergeMe& merge) : sorted_vector(NULL) , sorted_list(NULL)
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

    if (pmerge.sorted_vector)
    {
        this->sorted_vector = new std::vector<size_t>;
        ite_v = pmerge.sorted_vector->begin();
        end_v = pmerge.sorted_vector->end();
        while (ite_v != end_v)
        {
            this->sorted_vector->push_back(*ite_v);
            ite_v++;
        }
    }
    if (pmerge.sorted_list)
    {
        this->sorted_list = new std::list<size_t>;
        ite_l = pmerge.sorted_list->begin();
        end_l = pmerge.sorted_list->end();
        while (ite_l != end_l)
        {
            this->sorted_list->push_back(*ite_l);
            ite_l++;
        }
    }
    return (*this);
}

void PmergeMe::print_vector(std::string &str, std::vector<size_t> &vec)
{
    std::vector<size_t>::const_iterator ite_c = vec.begin();
    std::vector<size_t>::const_iterator end_c = vec.end();
    cout << str << endl;
    while(ite_c != end_c)
    {
        cout << *ite_c << " ";
        ite_c++;
    }
    cout << endl;
}

void PmergeMe::print_list(std::string &str, std::list<size_t> &lst)
{
    std::list<size_t>::const_iterator ite_c = lst.begin();
    std::list<size_t>::const_iterator end_c = lst.end();
    cout << str << endl;
    while(ite_c != end_c)
    {
        cout << *ite_c << " ";
        ite_c++;
    }
    cout << endl;
}

void PmergeMe::push(size_t value)
{
    this->vector.push_back(value);
    this->list.push_back(value);
}

std::vector<size_t>* insert_sort_in_vector(std::vector<size_t>* vec)
{
    std::vector<size_t>::const_iterator ite = vec->begin();
    std::vector<size_t>::const_iterator end = vec->end();
    std::vector<size_t>::iterator insert_ite;

    if (vec->size() <= 1)
    {
        return vec;
    }
    std::vector<size_t> *tmp = new std::vector<size_t>;
    tmp->push_back(*ite);
    ++ite;
    if (tmp->at(0) < *ite)
        tmp->push_back(*ite);
    else
        tmp->insert(tmp->begin(), *ite);
    ++ite;
    while(ite != end)
    {
        size_t i = 0;
        for (i = 1;i<tmp->size();i++)
        {
            if ((*tmp)[i-1] < *ite && *ite <= (*tmp)[i])
                break;
            else if ((*tmp)[i-1] > *ite)
            {
                i--;
                break;
            }
        }

        insert_ite = tmp->begin();
        insert_ite += i;
        tmp->insert(insert_ite, *ite);
        ite++;
    }
    delete vec;
    return (tmp);
}

std::vector<size_t>* clear_vector(const std::vector<size_t>* vec)
{
    delete vec;
    return (NULL);
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
    std::vector<std::vector<size_t>* >::iterator ite = divided.begin();
    std::vector<std::vector<size_t>* >::iterator end = divided.end();
    std::vector<std::vector<size_t>* >::iterator tmp_ite;
    while (base_size != (*divided.begin())->size())
    {
        while(ite != end && (*ite)->size() == 0)
            ite++;
        tmp_ite = ite;
        if (ite != end)
            ite++;
        while(ite != end && (*ite)->size() == 0)
            ite++;
        if (ite != end)
        {
            tmp = this->merge_sort_in_vector(*tmp_ite, *ite);
            (*ite)->clear();
            delete *tmp_ite;
            *tmp_ite = tmp;
        }
        else
            ite = divided.begin();
    }
    this->sorted_vector = tmp;
}

clock_t PmergeMe::sort_in_vector(size_t size)
{
    clock_t begin_time;
    clock_t end_time;

    begin_time = clock();

    std::vector<std::vector<size_t>* > divided(this->vector.size()/size + 1);
    make_divided_vector(divided, size);
    std::transform(divided.begin(),divided.end(),divided.begin(), insert_sort_in_vector);

    repeat_merge_sort_in_vector(divided);
    std::transform(++divided.begin(),divided.end(),divided.begin(), clear_vector);

    end_time = clock();
    return (end_time - begin_time);
}

std::list<size_t>* insert_sort_in_list(std::list<size_t>* lst)
{
    std::list<size_t>::const_iterator ite = lst->begin();
    std::list<size_t>::const_iterator end = lst->end();
    std::list<size_t>::iterator insert_ite;

    if (lst->size() <= 1)
    {
        return lst;
    }
    std::list<size_t> *tmp = new std::list<size_t>;
    tmp->push_back(*ite);
    ++ite;
    if (tmp->front() < *ite)
        tmp->push_back(*ite);
    else
        tmp->insert(tmp->begin(), *ite);
    ++ite;
    while(ite != end)
    {
        size_t i = 0;
        std::list<size_t>::iterator ite_sorted = tmp->begin();
        std::list<size_t>::iterator pre_ite_sorted = tmp->begin();
        std::list<size_t>::const_iterator end_sorted = tmp->end();
        while (ite_sorted != end_sorted)
        {
            pre_ite_sorted = ite_sorted;
            ite_sorted++;
            if (*pre_ite_sorted < *ite && *ite <= *ite_sorted)
                break;
            else if (*pre_ite_sorted > *ite)
            {
                i--;
                break;
            }
            ite_sorted++;
        }
        //insert_ite = tmp->begin();
        //insert_ite += i;
        tmp->insert(pre_ite_sorted, *ite);
        ite++;
    }
    delete lst;
    return (tmp);
}

std::list<size_t>* clear_list(const std::list<size_t>* lst)
{
    delete lst;
    return (NULL);
}

std::list<size_t>* PmergeMe::merge_sort_in_list(std::list<size_t>* lst1, std::list<size_t>* lst2)
{
    
    std::list<size_t> *tmp = new std::list<size_t>;
    std::list<size_t>::iterator ite1 = lst1->begin();
    std::list<size_t>::iterator end1 = lst1->end();
    std::list<size_t>::iterator ite2 = lst2->begin();
    std::list<size_t>::iterator end2 = lst2->end();
    size_t base_size = lst1->size() + lst2->size();
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
        tmp->insert(lst.begin(), i);
        ite++;
    }
    */
    return (tmp);
}

void PmergeMe::make_divided_list(std::list<std::list<size_t>* >& divided, size_t size)
{
    std::list<std::list<size_t>* >::iterator divided_ite = divided.begin();
    std::list<std::list<size_t>* >::iterator divided_end = divided.end();
    while(divided_ite != divided_end)
    {
        *divided_ite = new std::list<size_t>;
        divided_ite++;
    }
    std::list<size_t>::const_iterator ite = this->list.begin();
    std::list<size_t>::const_iterator end = this->list.end();

    size_t cnt = 0;
    divided_ite = divided.begin();
    while(ite != end)
    {
        if (cnt == size)
        {
            divided_ite++;
            cnt = 0;
        }
        else
        {
            cnt++;
        }
        (*divided_ite)->push_back(*ite);
        ite++;
    }
}

void PmergeMe::repeat_merge_sort_in_list(std::list<std::list<size_t>* >& divided)
{
    size_t base_size = this->list.size();
    std::list<size_t>* tmp;
    std::list<std::list<size_t>* >::iterator end = divided.end();
    std::list<std::list<size_t>* >::iterator ite = divided.begin();
    while (base_size != (*divided.begin())->size())
    {
        std::list<std::list<size_t>* >::iterator tmp_ite;
        while(ite != end && (*ite)->size() == 0)
            ite++;
        tmp_ite = ite;
        if (ite != end)
            ite++;
        while(ite != end && (*ite)->size() == 0)
            ite++;
        if (ite != end)
        {
            tmp = this->merge_sort_in_list(*tmp_ite, *ite);
            (*ite)->clear();
            delete *tmp_ite;
            *tmp_ite = tmp;
        }
        else
            ite = divided.begin();
    }
    this->sorted_list = divided.front();
}

clock_t PmergeMe::sort_in_list(size_t size)
{
    clock_t begin_time;
    clock_t end_time;

    begin_time = clock();

    std::list<std::list<size_t>* > divided(this->list.size()/size + 1);
    make_divided_list(divided, size);
    std::transform(divided.begin(),divided.end(),divided.begin(), insert_sort_in_list);
    repeat_merge_sort_in_list(divided);
    std::transform(++divided.begin(),divided.end(),divided.begin(), clear_list);

    end_time = clock();
    return (end_time - begin_time);
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

void PmergeMe::print_all(Container container)
{

    if (container == VECTOR)
    {
        std::vector<size_t>::const_iterator ite = this->vector.begin();
        std::vector<size_t>::const_iterator end = this->vector.end();
        for (; ite != end; ite++)
            cout << *ite << " " ;
    }
    else
    {
        std::list<size_t>::const_iterator ite = this->list.begin();
        std::list<size_t>::const_iterator end = this->list.end();
        for (; ite != end; ite++)
            cout << *ite << " " ;
    }
    cout << endl;
}

void PmergeMe::print_all_sorted(Container container)
{
    string tmp = "";
    if (container == VECTOR)
    {
        print_vector(tmp, *(this->sorted_vector));
    }
    else if(container == LIST)
    {
        print_list(tmp, *(this->sorted_list));
    }
    cout << endl;
}

bool PmergeMe::check_sort()
{
    if (sorted_vector == NULL || sorted_list == NULL)
        return (true);
    std::vector<size_t> check;
    check = this->vector;
    std::sort(check.begin(), check.end());

    std::vector<size_t>::const_iterator ite_c = check.begin();
    std::vector<size_t>::const_iterator end_c = check.end();
    std::vector<size_t>::const_iterator ite_v = this->sorted_vector->begin();
    std::vector<size_t>::const_iterator end_v = this->sorted_vector->end();
    //std::vector<size_t>::const_iterator ite_o = this->vector.begin();
    //std::vector<size_t>::const_iterator end_o = this->vector.end();
    while (ite_c != end_c && ite_v != end_v)
    {
        if (*ite_c != *ite_v)
        {
            cout << "Error:sorted data in vector does not match original sort algorithm" << endl;
            return (false);
        }
        ite_v++;
        ite_c++;
    }
    if (ite_v != end_v  || ite_c != end_c)
    {
        cout << "Error:sorted data in vector does not match original sort algorithm" << endl;
        return (false);
    }

    ite_v = this->sorted_vector->begin();
    end_v = this->sorted_vector->end();
    std::list<size_t>::const_iterator ite_l = this->sorted_list->begin();
    std::list<size_t>::const_iterator end_l = this->sorted_list->end();

    while (ite_v != end_v && ite_l != end_l)
    {
        if (*ite_v != *ite_l)
        {
            cout << "Error:sorted data in vector does not match sorted in list" << endl;
            return (false);
        }
        ite_v++;
        ite_l++;
    }
    if (ite_v != end_v  || ite_c != end_c)
    {
        cout << "Error:sorted data in vector does not match sorted in list" << endl;
        return (false);
    }
    return (true);
}
