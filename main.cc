
#include <iostream>
#include <sstream>
#include <list>
#include <fstream>

#include "solver.h"

int main(int argc, char** argv)
{
    size_t n, m;
    std::string line;
    std::string p;
    std::string cnf;
    std::istream* fs;
    std::ostream* os;
    if (argc > 1)
    {
        try {
            fs = new std::ifstream(argv[1]);
        }
        catch (std::exception e)
        {
            std::cout << "Invalid input file" << std::endl;
            return 1;
        }
    }
    else
    {
        fs = &std::cin;
    }
    if (argc > 2)
    {
        try {
            os = new std::ofstream(argv[2]);
        }
        catch (std::exception e)
        {
            std::cout << "Invalid output file" << std::endl;
            return 1;
        }
    }
    else
    {
        os = &std::cout;
    }
    // get line from stdin
    do {
        std::getline(*fs, line);
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
        std::getline(*fs, line);
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
                c.add_literal(literals + lit - 1, false, i);
            }
            else if (lit < 0) {
                lit = 0 - lit;
                c.add_literal(literals + lit - 1, true, i);
            }
        }
        clauses->push_back(c);
    }
    try {
        simplesat::solver s(clauses, literals, n);
        bool result = s.solve();
        if (result)
        {
            *os << "SAT" << std::endl;
            auto model = s.get_model();
            for (auto it = model.begin(); it != model.end(); ++it) {
                if (it->second)
                    *os << it->first << " ";
                else
                    *os << "-" << it->first << " ";
            }
            *os << "0" << std::endl;
        }
        else
            *os << "UNSAT" << std::endl;
        return 0;
    }
    catch (std::string e)
    {
        std::cout << e << std::endl;
        return 1;
    }
    
}