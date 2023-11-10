#ifndef SIMPLE_SAT_SOLVER_H
#define SIMPLE_SAT_SOLVER_H

#include "clause.h"
#include "literal.h"
#include <vector>
#include <utility>
#include <algorithm>

namespace simplesat
{
    class solver
    {
    public:
        solver(std::list<clause>* clauses, literal* literals, size_t num_literals);
        virtual ~solver();

        bool solve();
        std::vector<std::pair<size_t, bool>> get_model();
    private:
        literal* literals;
        std::list<size_t> unknown_literals;
        size_t num_literals;
        bool solved;

        // 0 = strong false, 1 = strong true
        // 2 = weak false, 3 = weak true
        std::vector<std::pair<literal*,int>> decision_stack;

        // -1 = unsatisfiable, 0 = not sure, 1 = satisfied
        std::vector<std::pair<clause*, int>> clauses;

        size_t eliminate_unit_clauses();
        void check_clauses();

        // -1 = unsatisfiable, 0 = not sure, 1 = satisfied
        int get_current_result();

        void insert_unknown_literal(size_t index);
    };
    
} // namespace simplesat

#endif //SIMPLE_SAT_SOLVER_H