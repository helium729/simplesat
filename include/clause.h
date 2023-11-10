#ifndef SIMPLESAT_CLAUSE_H
#define SIMPLESAT_CLAUSE_H

#include <list>
#include <utility>
#include "literal.h"

namespace simplesat
{
    /**
     * Represents a clause in a SAT problem.
     */
    class clause {
    public:
        /**
         * Constructs a new clause.
         */
        clause();

        /**
         * Destroys the clause.
         */
        virtual ~clause();

        /**
         * Returns the truth value of the clause.
         * -1 = unsatisfiable, 0 = not sure, 1 = satisfied
         */
        int val();

        /**
         * Adds a literal to the clause.
         * @param lit The literal to add.
         * @param negated Whether the literal is negated.
         */
        void add_literal(literal* lit, bool negated = false);

        /**
         * Returns a single unknown literal in the clause, if one exists.
         * @return A pair containing the unknown literal and whether it is negated.
         */
        std::pair<literal*, bool> get_single_unknown_literal();

    private:
        std::list<std::pair<literal*,bool>> literal_pointers;   
    };
} // namespace simplesat

#endif