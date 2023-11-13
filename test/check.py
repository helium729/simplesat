import os

def check(lines, cnflines):
    if lines[0] == 'UNSAT':
        return 'UNSAT'
    else:
        line = lines[1].split()
        # remove the first line of cnflines
        cnflines = cnflines[1:]
        # for each cnfline, split
        cnflines = [x.split() for x in cnflines]
        for i in range(len(line)):
            if line[i] == '0':
                break
            for x in line:
                # remove cnfline contains x
                cnflines = [y for y in cnflines if x not in y]
        # if cnflines is empty, then PASS
        if len(cnflines) == 0:
            return 'PASS'
        else:
            return 'FAIL'

# get the filename from argv
filename = os.sys.argv[1]
# filename = "test/01-conflict" # for test
# read all lines from .out file
with open(filename + '.out', 'r') as f:
    lines = f.readlines()

# read all lines from .cnf file
with open(filename + '.cnf', 'r') as f:
    cnflines = f.readlines()

# prune the lines
lines = [x.strip() for x in lines]
cnflines = [x.strip() for x in cnflines]

# check the result
result = check(lines, cnflines)

# print the result
print(result)

