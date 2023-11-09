#include "clause.h"

simplesat::clause::clause()
{
}

simplesat::clause::~clause()
{
}

int simplesat::clause::val()
{
    bool not_sure = false;
    // if clause is empty, return -1
    if (literal_pointers.empty())
        return -1;
    // iterate through literals
    for (auto it = literal_pointers.begin(); it != literal_pointers.end(); ++it) {
        // if literal is assigned true, return 1
        if (it->first->is_assigned() && (it->first->get_value() ^ it->second) == true)
            return 1;
        // if literal is assigned false, jump to next literal
        else if (it->first->is_assigned() && (it->first->get_value() ^ it->second) == false)
            continue;
        // if literal is not assigned, set not_sure to true
        else
            not_sure = true;
    }
    // if not_sure is true, return 0
    if (not_sure)
        return 0;
    // if not_sure is false, return -1
    else
        return -1;
}

void simplesat::clause::add_literal(literal* lit, bool negated)
{
    literal_pointers.push_back(std::make_pair(lit, negated));
}

std::pair<simplesat::literal*,bool> simplesat::clause::get_single_unknown_literal()
{
    size_t count = 0;
    simplesat::literal* unknown_literal;
    bool negated = false;
    for (auto it = literal_pointers.begin(); it != literal_pointers.end(); ++it) {
        if (!it->first->is_assigned())
        {
            count++;
            unknown_literal = it->first;
            negated = it->second;
        }
    }
    if (count == 1)
        return std::make_pair(unknown_literal, negated);
    else
        return std::make_pair(nullptr, false);
}
