#include "solver.h"

simplesat::solver::solver(std::list<clause> *clauses, literal *literals, size_t num_literals)
{
    for (auto it = clauses->begin(); it != clauses->end(); it++) {
        this->clauses.push_back(std::make_pair(&(*it), 0));
    }
    this->literals = literals;
    this->num_literals = num_literals;
    this->solved = false;
    for (size_t i = 0; i < num_literals; i++) {
        unknown_literals.push_back(i);
    }
}

simplesat::solver::~solver()
{
}

bool simplesat::solver::solve()
{
    while (true)
    {
        size_t eliminated = eliminate_unit_clauses();
        if (eliminated > 0)
            continue;
        check_clauses();
        int result = get_current_result();
        if (result == 1)
            return true;
        else if (result == -1)
        {
            if (decision_stack.back().second != 2)
            {
                size_t last_weak_index = 0;
                bool all_strong_or_last = true;
                for (auto it = decision_stack.begin(); it != decision_stack.end(); it++) {
                    if (it->second == 2) {
                        all_strong_or_last = false;
                        last_weak_index = it - decision_stack.begin();
                        break;
                    }
                }
                if (all_strong_or_last)
                    return false;
                // backtrack
                while (decision_stack.back().second != 2) {
                    decision_stack.back().first->unassign();
                    insert_unknown_literal(decision_stack.back().first - literals);
                    decision_stack.pop_back();
                }
                // flip last weak decision to weak true
                decision_stack.back().first->assign(true);
                decision_stack.back().second = 3;
            }
            // flip last weak decision to weak true
            decision_stack.back().first->assign(true);
            decision_stack.back().second = 3;
        }
        else
        {
            // make a decision
            size_t index = unknown_literals.front();
            unknown_literals.pop_front();
            literals[index].assign(false);
            decision_stack.push_back(std::make_pair(literals + index, 2));
        }
    }
    return false;
}

size_t simplesat::solver::eliminate_unit_clauses()
{
    size_t count = 0;
    for (auto it = clauses.begin(); it != clauses.end(); it++) {
        auto single = it->first->get_single_unknown_literal();
        if (single.first == nullptr)
            continue;
        single.first->assign(!single.second);
        // unit elimination is always strong
        decision_stack.push_back(std::make_pair(single.first, single.second ? 0 : 1));        
        // remove from unknown_literals
        for (auto it2 = unknown_literals.begin(); it2 != unknown_literals.end(); it2++) {
            if (*it2 == single.first - literals) {
                unknown_literals.erase(it2);
                break;
            }
        }
    }
    return count;
}

void simplesat::solver::check_clauses()
{
    for (auto it = clauses.begin(); it != clauses.end(); it++) {
        int val = it->first->val();
        if (val == 1)
            it->second = 1;
        else if (val == -1)
            it->second = -1;
        else 
            it->second = 0;
    }
}

int simplesat::solver::get_current_result()
{
    int result = 1;
    for (auto it = clauses.begin(); it != clauses.end(); it++) {
        if (it->second == -1)
            return -1;
        result &= it->second;
    }
    return result;
}

void simplesat::solver::insert_unknown_literal(size_t index)
{
    if (index == 0)
    {
        unknown_literals.push_front(index);
        return;
    }
    for (auto it = unknown_literals.begin(); it != unknown_literals.end(); it++) {
        if (*it > index) {
            unknown_literals.insert(it, index);
            return;
        }
    }
    unknown_literals.push_back(index);
}