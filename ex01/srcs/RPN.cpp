#include "RPN.hpp"
#include <limits>
#include <stdexcept>
#include <iostream>
using std::string;
using std::numeric_limits;
using std::cout;
using std::endl;


Rpn::Rpn()
{
}
Rpn::~Rpn()
{
}
Rpn::Rpn(const Rpn& rpn)
{
    (void)(rpn);
}
Rpn& Rpn::operator=(const Rpn& rpn)
{
    (void)(rpn);
    return (*this);
    /*
    if (this == &rpn)
        return (*this);
    const std::deque<string> tmp = reinterpret_cast<const std::deque<string> &>(rpn);
    while(this->stack.size())
        this->stack.pop();

    std::deque<string>::const_iterator ite = tmp.begin();
    std::deque<string>::const_iterator end = tmp.end();
    for (; ite != end; ite++)
    {
        this->stack.push(*ite);
    }
    return (*this);
    */
}

bool Rpn::is_operator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return (true);
    return (false);
}

    /*
void Rpn::load(string& literial)
{
    
    size_t pos = literial.find("(");
    if (pos != std::string::npos)
        throw std::exception();
    pos = literial.find(")");
    if (pos != std::string::npos)
        throw std::exception();
    this->literial = literial;
    bool space_flag = true;
    for (int i=0;i<literial.size(); i++)
    {
        if(literial[i] == ' ')
            space_flag = true;
        else if (space_flag && isdigit(literial[i]))
        {
            space_flag = false;
            this->stack.push(literial.substr(i, 1));
        }
        else if (space_flag && is_operator(literial[i]))
        {
            this->stack.push(literial.substr(i, 1));
            space_flag = false;
        }
        else
            throw std::exception();
    }
}
    */

void Rpn::check_overflow(ssize_t a, ssize_t b, char c_operator)
{
    if (c_operator == '+')
    {
        if ((b >= 0 && (numeric_limits<ssize_t>::max() - b) < a) || (b < 0 && (numeric_limits<ssize_t>::min() - b) > a))
        {
            throw std::range_error("Error:Over Flow operator+");
        }
    }
    else if (c_operator == '-')
    {
        if ((b >= 0 && (numeric_limits<ssize_t>::min() + b) > a) || (b < 0 && (numeric_limits<ssize_t>::max() + b) < a))
        {
            throw std::range_error("Error:Over Flow operator-");
        }
    }
    else if (c_operator == '*')
    {
        ssize_t result = a * b;
        if (result > 0 && (numeric_limits<ssize_t>::max() / a) < b)
        {
            throw std::range_error("Error:Over Flow operator*");
        }
        else{
            if (a == numeric_limits<ssize_t>::min() && (b > 1 || b < -1))
                throw std::range_error("Error:Over Flow operator*");
            else if (b == numeric_limits<ssize_t>::min() && (a > 1 || a < -1))
                throw std::range_error("Error:Over Flow operator*");
            if (a < 0)
                a *= -1;
            if (b < 0)
                b *= -1;
            if (result != 0 && (numeric_limits<ssize_t>::max() / a) < b)
                throw std::range_error("Error:Over Flow operator*");
        }
    }
}

ssize_t Rpn::calc_operator(ssize_t a, ssize_t b, char c)
{
    ssize_t result = 0;

    switch(c)
    {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b == 0)
            {
                throw std::range_error("Error:Divided by zero.");
            }
            result = a / b;
            break;
        default:
            throw std::exception();
    }
    check_overflow(a, b, c);
    return (result);
}


ssize_t Rpn::calc(string& str)
{
    bool space_flag = true;
    //string str = this->literial;
    std::stack<ssize_t> stack;
    ssize_t a;
    ssize_t b;
    ssize_t result;
    char c;
    for (size_t i = 0; i< str.size(); i++)
    {
        c = str[i];
        if(str[i] == ' ')
            space_flag = true;
        else if (space_flag && isdigit(c))
        {
            stack.push((c - '0'));
            space_flag = false;
        }
        else if (space_flag && this->is_operator(c))
        {
            b = stack.top();
            stack.pop();
            a = stack.top();
            stack.pop();
            result = calc_operator(a, b, c);
            stack.push(result);
            //stack.push(str.substr(i, 1));
            space_flag = false;
        }
        else
            throw std::exception();
    }
    if (stack.size() != 1)
        throw std::exception();
    return (stack.top());
}
