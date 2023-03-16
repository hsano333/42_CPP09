#ifndef RPN_H
#define RPN_H
#include <stack>
#include <string>
#include <cstdio>

class Rpn
{

    public:
        Rpn();
        ~Rpn();
        Rpn(const Rpn& rpn);
        Rpn& operator=(const Rpn& rpn);
        //void load(std::string& str);
        ssize_t calc(std::string& str);
    private:
        bool is_operator(char c);
        void check_overflow(ssize_t a, ssize_t b, char c);
        ssize_t calc_operator(ssize_t a, ssize_t b, char c);
        //std::stack<std::string> stack;
        //std::string literial;
};

#endif
