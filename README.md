# simplesat
A simple sat solver to demostrate DPLL algorithm.

## Compile
**Note:** The original CMakeLists.txt is for development and tests. To use the code, only the target simplesat is needed. You can comment the lines in the CMakeLists.txt to remove the tests and the development target, which can avoid dependencies on gtest.

```
git clone https://github.com/helium729/simplesat.git
cd simplesat
mkdir build
cd build
cmake ..
make
```

## Usage
Using with stdin and stdout:
```
./simplesat 
```
or with a file input and stdout:
```
./simplesat <input_file>
```
or with a file input and a file output:
```
./simplesat <input_file> <output_file>
```

## Input format
The input uses a cnf file format:
```
c This is a comment line
c Comments start with 'c'
c A line starting with 'p' is the problem line
c The problem line has the format: p cnf <num_vars> <num_clauses>
c The clauses are listed after the problem line
c Each clause is a list of literals, terminated by 0
c A positive literal is a variable, a negative literal is the negation of a variable
c For example, the following is a cnf file with 3 variables and 2 clauses:
p cnf 3 2
1 -2 0
2 3 -1 0
```

In the example above, there are 3 variables $p_1, p_2, p_3$ and 2 clauses $(p_1 \lor \lnot p_2) \land (p_2 \lor p_3 \lor \lnot p_1)$. The problem can be written in a more compact form as:
$ (p_1 \lor \lnot p_2) \land (p_2 \lor p_3 \lor \lnot p_1) $

The problem is to find a truth assignment to the variables such that all the clauses are satisfied. For example, the following assignment satisfies the clauses:
$p_1 = true, p_2 = true, p_3 = true$

## Output format
The output first gives if the problem is satisfiable or not. If the problem is satisfiable, the output gives a satisfying assignment. For example, the output for the example above is:
```
SAT
1 2 -3
```
which means the problem is satisfiable and the following assignment satisfies the clauses:
$ p_1 = true, p_2 = true, p_3 = false$
if the problem is not satisfiable, the output is:
```
UNSAT
```

## Principles of the algorithm
The program is based one two algorithms:
### Unit propagation
Unit propagation is a simple algorithm that can be used to simplify a cnf formula. The algorithm is as follows:
```
while there is a unit clause c in the formula:
    remove c from the formula
    for each clause c' in the formula:
        remove the negation of the literal in c from c'
```
The algorithm can be used to simplify a formula by removing the unit clauses and the negation of the literals in the unit clauses from the other clauses. 
### DPLL
DPLL is a complete algorithm for the satisfiability problem. The algorithm is as follows:
```
DPLL(formula):
    if the formula is empty:
        return true
    if the formula contains an empty clause:
        return false
    if the formula contains a unit clause c:
        remove c from the formula
        for each clause c' in the formula:
            remove the negation of the literal in c from c'
        return DPLL(formula)
    else:
        choose a literal l
        return DPLL(formula with l set to true) or DPLL(formula with l set to false)
```

## Implementation
The implementation of the algorithm is in the file src/solver.cc. The implementation is based on the following data structures:

For more information about the implementation, please refer to the comments in the source code, especially the comments in the files in the include directory.
### Literal
The Literal class represents a literal in the cnf formula. A literal is a variable or the negation of a variable. The Literal class has the following members:
- state: the state of the literal, which can be true, false or undefined

In the solver, an array of literals is used to represent the assignment to the variables. The index of the array is the variable id, and the value of the array is the state of the variable. For example, if the array is [undefined, true, false], it means $p_1 = true, p_2 = false, p_3 = undefined$.

### Clause
The Clause class represents a clause in the cnf formula. The Clause class has the following members:
- literals: a list of literals in the clause
- val: the state of the clause, which can be true, false or undefined

### Solver
The Solver class represents the solver. The Solver class has the following members:
- clauses: a list of clauses in the cnf formula
- decision_stack: a stack of decisions made by the solver

