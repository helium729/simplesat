
#include <iostream>
#include <sstream>
#include <list>

#include "solver.h"

int main()
{
    size_t n, m;
    std::string line;
    std::string p;
    std::string cnf;
    // get line from stdin
    do {
        std::getline(std::cin, line);
    } while (line.empty() || line[0] == 'c');
    // parse line
    std::istringstream iss(line);
    iss >> p >> cnf >> n >> m;
    // check magic number
    if (p != "p" || cnf != "cnf") {
        std::cout << "Invalid input" << std::endl;
        return 1;
    }
    simplesat::literal* literals = new simplesat::literal[n];
    std::list<simplesat::clause>* clauses = new std::list<simplesat::clause>();
    // read in clauses
    for (size_t i = 0; i < m; i++) {
        // get line from stdin
        std::string line;
        simplesat::clause c;
        std::getline(std::cin, line);
        if (line.empty())
        {
            i--;
            continue;
        }
        // parse line
        std::istringstream iss(line);
        long long int lit;
        while (iss >> lit) {
            if (lit > 0) {
                c.add_literal(literals + lit - 1, false);
            }
            else if (lit < 0) {
                lit = 0 - lit;
                c.add_literal(literals + lit - 1, true);
            }
        }
        clauses->push_back(c);
    }
    simplesat::solver s(clauses, literals, n);
    bool result = s.solve();
    if (result)
    {
        std::cout << "SAT" << std::endl;
        auto model = s.get_model();
        for (auto it = model.begin(); it != model.end(); ++it) {
            if (it->second)
                std::cout << it->first << " ";
            else
                std::cout << "-" << it->first << " ";
        }
        std::cout << "0" << std::endl;
    }
    else
        std::cout << "UNSAT" << std::endl;
    return 0;
}