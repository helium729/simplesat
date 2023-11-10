#ifndef SIMPLE_SAT_SOLVER_H
#define SIMPLE_SAT_SOLVER_H

#include "clause.h"
#include "literal.h"
#include <vector>
#include <utility>
#include <algorithm>

namespace simplesat
{
    /**
     * @brief The solver class provides a SAT solver that can solve a given set of clauses.
     * 
     */
    class solver
    {
    public:
        /**
         * @brief Construct a new solver object with the given clauses, literals and number of literals.
         * 
         * @param clauses A pointer to a list of clauses.
         * @param literals An array of literals.
         * @param num_literals The number of literals in the literals array.
         */
        solver(std::list<clause>* clauses, literal* literals, size_t num_literals);

        /**
         * @brief Destroy the solver object.
         * 
         */
        virtual ~solver();

        /**
         * @brief Solve the set of clauses.
         * 
         * @return true if the set of clauses is satisfiable, false otherwise.
         */
        bool solve();

        /**
         * @brief Get the model of the solved set of clauses.
         * 
         * @return A vector of pairs of size_t and bool representing the literals and their values in the model.
         */
        std::vector<std::pair<size_t, bool>> get_model();

    private:
        literal* literals; // An array of literals.
        std::list<size_t> unknown_literals; // A list of unknown literals.
        size_t num_literals; // The number of literals.
        bool solved; // A flag indicating whether the set of clauses is solved.

        // 0 = strong false, 1 = strong true
        // 2 = weak false, 3 = weak true
        std::vector<std::pair<literal*,int>> decision_stack; // A vector of pairs of literals and their values.

        // -1 = unsatisfiable, 0 = not sure, 1 = satisfied
        std::vector<std::pair<clause*, int>> clauses; // A vector of pairs of clauses and their values.

        /**
         * @brief Eliminate unit clauses from the set of clauses.
         * 
         * @return The number of unit clauses eliminated.
         */
        size_t eliminate_unit_clauses();

        /**
         * @brief Check the clauses in the set of clauses.
         * 
         */
        void check_clauses();

        /**
         * @brief Get the current result of the set of clauses.
         * 
         * @return -1 if the set of clauses is unsatisfiable, 0 if not sure, 1 if satisfied.
         */
        int get_current_result();

        /**
         * @brief Insert an unknown literal into the list of unknown literals.
         * 
         * @param index The index of the literal to be inserted.
         */
        void insert_unknown_literal(size_t index);
    };
    
} // namespace simplesat

#endif //SIMPLE_SAT_SOLVER_H