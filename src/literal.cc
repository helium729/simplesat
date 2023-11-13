#include "literal.h"

simplesat::literal::literal()
{
    state = -1;
}

simplesat::literal::~literal()
{
}

int simplesat::literal::get_state()
{
    return state;
}

bool simplesat::literal::get_value()
{
    if (state == 1)
        return true;
    else if (state == 0)
        return false;
    else {
        std::string msg = "literal not assigned";
        throw msg;
    }
}

bool simplesat::literal::is_assigned()
{
    return state != -1;
}

void simplesat::literal::assign(bool value)
{
    if (state != -1)
        throw std::string("literal already assigned");
    if (value)
        state = 1;
    else
        state = 0;
}

void simplesat::literal::unassign()
{
    state = -1;
}
