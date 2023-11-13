#ifndef SIMPLESAT_CLAUSE_H
#define SIMPLESAT_CLAUSE_H

#include <list>
#include <utility>
#include "literal.h"
#include <map>

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
         * @param id Id to this clause, use -1 to disable
         */
        void add_literal(literal* lit, bool negated = false, int id = -1);

        /**
         * Returns a single unknown literal in the clause, if one exists.
         * @return A pair containing the unknown literal and whether it is negated.
         */
        std::pair<literal*, bool> get_single_unknown_literal();

        void cache_true();
        void clear_cache();
        bool get_negated(literal*);

    private:
        std::map<literal*,bool> literal_pointers;   
        bool cache;
    };
} // namespace simplesat

#endif