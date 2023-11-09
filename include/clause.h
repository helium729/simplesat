#ifndef SIMPLESAT_CLAUSE_H
#define SIMPLESAT_CLAUSE_H

#include <list>
#include <utility>
#include "literal.h"

namespace simplesat
{
    class clause
    {
    public:
        clause();
        virtual ~clause();

        int val(); // -1 = unsatisfiable, 0 = not sure, 1 = satisfied
        void add_literal(literal* lit, bool negated = false);

        std::pair<literal*, bool> get_single_unknown_literal();

    private:
        std::list<std::pair<literal*,bool>> literal_pointers;   
    };  
} // namespace simplesat

#endif