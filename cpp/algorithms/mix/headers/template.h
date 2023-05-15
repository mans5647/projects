#ifndef TEMPLATE_FH
#define TEMPLATE_FH
#include "sum.cpp"

namespace 
{
    template <class arg>

    arg return_sum(arg lhs, arg rhs)
    {
        return sum(lhs, rhs);
    }
}

#endif