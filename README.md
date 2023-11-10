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
$$
\begin{align}
(p_1 \lor \lnot p_2) \land (p_2 \lor p_3 \lor \lnot p_1)
\end{align}
$$

The problem is to find a truth assignment to the variables such that all the clauses are satisfied. For example, the following assignment satisfies the clauses:
$$
p_1 &= true \\
p_2 &= true \\
p_3 &= true
$$

## Output format
The output first gives if the problem is satisfiable or not. If the problem is satisfiable, the output gives a satisfying assignment. For example, the output for the example above is:
```
SAT
1 2 -3
```
which means the problem is satisfiable and the following assignment satisfies the clauses:
$$
p_1 &= true \\
p_2 &= true \\
p_3 &= false
$$
if the problem is not satisfiable, the output is:
```
UNSAT
```






