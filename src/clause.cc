#include "clause.h"

simplesat::clause::clause()
{
    valid_length = 0;
    clear_cache();
}

simplesat::clause::~clause()
{
}

int simplesat::clause::val()
{
    if (cache)
        return 1;
    bool not_sure = false;
    // if clause is empty, return 1
    if (literal_pointers.empty())
        return 1;
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

void simplesat::clause::add_literal(literal* lit, bool negated, int id)
{
    literal_pointers[lit] = negated;
    if (id >= 0)
        lit->clause_ids.push_back(id);
    valid_length++;
}

std::pair<simplesat::literal*,bool> simplesat::clause::get_single_unknown_literal()
{
    if (valid_length > 1 || valid_length == 0){
        return std::make_pair(nullptr, false);
    }
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

void simplesat::clause::cache_true()
{
    cache = true;
}

void simplesat::clause::clear_cache()
{
    cache = false;
}

bool simplesat::clause::get_negated(simplesat::literal* lit)
{
    // check if lit exists
    if (literal_pointers.find(lit) == literal_pointers.end())
        throw std::string("literal does not exist in clause");
    return literal_pointers[lit];    
}