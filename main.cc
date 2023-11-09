
#include <iostream>
#include <sstream>
#include <list>

#include "solver.h"

int main()
{
    size_t n, m;
    std::string line;
    // get line from stdin
    std::getline(std::cin, line);
    // parse line
    std::istringstream iss(line);
    iss >> n >> m;
    simplesat::literal* literals = new simplesat::literal[n];
    std::list<simplesat::clause>* clauses = new std::list<simplesat::clause>();
    // read in clauses
    for (size_t i = 0; i < m; i++) {
        // get line from stdin
        std::string line;
        simplesat::clause c;
        std::getline(std::cin, line);
        // parse line
        std::istringstream iss(line);
        int lit;
        while (iss >> lit) {
            if (lit > 0) {
                c.add_literal(literals + lit - 1, false);
            }
            else {
                lit = 0 - lit;
                c.add_literal(literals + lit - 1, true);
            }
        }
        clauses->push_back(c);
    }
    simplesat::solver s(clauses, literals, n);
    bool result = s.solve();
    if (result)
        std::cout << "sat" << std::endl;
    else
        std::cout << "unsat" << std::endl;

    return 0;
}