# Author: Shantanu Wable, Ruchi Bhale

import re as regex
import json
import os

os.system('cls' if os.name == 'nt' else 'clear')

# Creating the intermediate code file 

# Input Files
directives = {
    "start" : "(AD, 01)",
    "end" : "(AD, 02)",
    "origin" : "(AD, 03)",
    "equ" : "(AD, 04)",
    "ltorg" : "(AD, 05)"
}  

# Mnemonics size mapping
msize = {
    "stop" : 1,
    "add" : 1,
    "sub" : 1,
    "mult" : 1,
    "mover" : 1,
    "movem" : 1,
    "comp" : 1,
    "bc" : 1,
    "div" : 1,
    "read" : 1,
    "print" : 1,
    "start" : 1,
    "end" : 1,
    "origin" : 1,
    "equ" : 1,
    "ltorg" : 1,
    "dc" : 1,
    "ds" : 1
}

# Mnemonics opcode mapping
mnemonics = {
    "stop" : "(IS, 00)",
    "add" : "(IS, 01)",
    "sub" : "(IS, 02)",
    "mult" : "(IS, 03)",
    "mover" : "(IS, 04)",
    "movem" : "(IS, 05)",
    "comp" : "(IS, 06)",
    "bc" : "(IS, 07)",
    "div" : "(IS, 08)",
    "read" : "(IS, 09)",
    "print" : "(IS, 10)",
    "dc" : "(DL, 01)",
    "ds" : "(DL, 02)"
}

# Registers mapping
registers = {
    "areg" : 1,
    "breg" : 2,
    "creg" : 3,
    "dreg" : 4
}

# Conditional codes mapping
conditionCodes = {
    "lt" : 1,
    "le" : 2,
    "eq" : 3,
    "gt" : 4,
    "ge" : 5,
    "any" : 6
}
#input file
file = open("/home/kunal/TE_Lab_Assignments/LP1/Assembler/pass1/input/program.asm",'r')

# Output Files
icFile = open('/home/kunal/TE_Lab_Assignments/LP1/Assembler/pass1/output/IntermediateCode.txt', 'a')

# Regex pattern to split on occurrence of one or more spaces
pattern = r'\s+'

# Global variables to store data
label = ""
instruction = ""
op1 = ""
op2 = ""
op1code = ""
op2code = ""
current = 0
previous = 0
flag = False        # Flag for when DS or DC is encountered
relativeAddresses = []
IC = []
stCnt = 1
ltCnt = 1

# Tables
symbolTable = {}
literalTable = {}

# Loop through lines in file
for line in file:

    # Clearing variables from previous iteration
    label = ""
    instruction = ""
    op1 = ""
    op2 = ""
    op1code = ""
    op2code = ""
    var = ""

    # Skip blank lines and remove beginning and trailing whitespace(s)
    if line == '\n': continue
    line = line.strip()

    # Split the line into words and convert them to lowercase to avoid casing issues
    cmd = regex.split(pattern, line.rstrip())
    cmd = list(map(lambda x: x.lower(), cmd))

    # ------------ TOKENIZATION ------------

    if len(cmd) == 4:
        """
            Command is of the format: 
            LABEL INSTRUCTION OP1 OP2
        """
        
        label = cmd[0]
        instruction = cmd[1]
        op1 = cmd[2]
        op2 = cmd[3]

    elif len(cmd) == 3:
        """
            Command is of the format: 
            OP1 INSTRUCTION OP2
                    or
            INSTRUCTION OP1 OP2
        """
        cmdIndex = -1
        for command in cmd:
            if command in mnemonics:
                if command == "ds" or command == "dc":
                    var = cmd[0]
                    cmdIndex = 1
                    op1 = cmd[2]
                    flag = True
                    break
                else:    
                    cmdIndex = cmd.index(command)
                    break
            if command in directives:
                cmdIndex = cmd.index(command)
                break
        
        instruction = cmd[cmdIndex]
        if cmdIndex == 0:
            op1 = cmd[1]
            op2 = cmd[2]
        
        elif flag == False:
            op1 = cmd[cmdIndex - 1]
            op2 = cmd[cmdIndex + 1]
    
    elif len(cmd) == 2:
        """
            Command is of the format: 
            INSTRUCTION OP1
                    or
            LABEL INSTRUCTION
        """
        cmdIndex = -1
        for command in cmd:
            if command in directives:    
                cmdIndex = cmd.index(command)
                break
            if command in mnemonics:  #**********edited
                cmdIndex = cmd.index(command)
                break
        instruction = cmd[cmdIndex]
        if cmdIndex == 0:
            op1 = cmd[1]
        else:
            label = cmd[0]

    else:
        """
            Command is of the format: INSTRUCTION
        """
        instruction = cmd[0]

    # ------------ INSTRUCTION MATCHING ------------

    if instruction in directives:
        if instruction == 'start':
            current = int(cmd[1])
            opcode = directives.get(instruction)
            op1code = f"(C, {current})"
            icFile.write(f"    {opcode} {op1code}\n")
            continue

        elif instruction == 'end':
            opcode = directives.get(instruction)
            # size = int(msize.get(instruction))
            icFile.write(f'    {opcode}\n')
            break

        elif instruction == 'origin':
            opcode = directives.get(instruction)
            op1 = cmd[1]
            if "-" in op1:
                label = op1.split('-')[0]
                offset = op1.split('-')[1]
                op1code = f"(S, {symbolTable.get(label)[0]})-{offset}"
                previous = current
                current = symbolTable.get(label)[2] - int(offset)
                relativeAddresses.append(previous)
                icFile.write(f"    {opcode} {op1code}\n")

            elif "+" in op1:
                label = op1.split('+')[0]
                offset = op1.split('+')[1]
                op1code = f"(S, {symbolTable.get(label)[0]})+{offset}"
                previous = current
                current = symbolTable.get(label)[2] + int(offset)
                relativeAddresses.append(previous)
                icFile.write(f"    {opcode} {op1code}\n")

            else:
                op1code = f"(S, {symbolTable.get(op1)[0]})"
                previous = current
                current = symbolTable.get(op1)[2]
                relativeAddresses.append(previous)
                icFile.write(f"    {opcode} {op1code}\n")
            
        elif instruction == 'equ':
            op1 = cmd[0]
            op2 = cmd[2]
            symbolTable[op1][2] = symbolTable[op2][2]

        elif instruction == 'ltorg':
            for literal, [index, lt, value] in literalTable.items():
                if value == -1:
                    
                    previous = current
                    current += 1
                    relativeAddresses.append(previous)

                    literalTable[literal][2] = previous #//////////changes current to previous
                    opcode = "(DL, 01)"
                    op1code = f"(C, {lt})"    #****changed value to lt because val gives memory add and lt is value of literal
                    icFile.write(f"{previous} {opcode} {op1code}\n") #added prev for lc

                else:
                    pass

    elif instruction in mnemonics:
        
        # added these to avoid printing of (S,n) for the variables in the DS DC instructions
        if instruction=='ds': 
            # op1code=f"(C,{op2})"
            op2code=f""
        if instruction=='dc':
            # op1code=f"(C,{op2[1]})"
            op2code=f""
            
        opcode = mnemonics.get(instruction)
        size = int(msize.get(instruction))

        previous = current
        current += size

        relativeAddresses.append(previous)

        if label:
            if label in symbolTable:
                symbolTable[label][2] = previous
            else:
                symbolTable[label] = [stCnt, label, previous]
                stCnt += 1

        # ------------ Operand 1 ------------

        if instruction == 'bc':
            op1code = f'({conditionCodes.get(op1)})'

        elif op1.isdigit():
            op1code = f'(C, {op1})'

        elif op1 in registers:
            op1code = f"({registers.get(op1)})"

        elif "=" in op1:
            literal = op1.split('=')[1][1]
            if op1 in literalTable:
                op1code = f"(L, {literalTable.get(op1)[0]})"
            else:
                literalTable[ltCnt] = [ltCnt, literal, -1]
                op1code = f"(L, {ltCnt})"
                ltCnt += 1

         # Added this so that symbol table has value of that LC where the variable is declared using DC DS
        elif instruction=='ds' or instruction=='dc':
            symbolTable[op1][2]=previous
        else :
            if op1 in symbolTable:
                op1code = f"(S, {symbolTable.get(op1)[0]})"
            elif op1:
                symbolTable[op1] = [stCnt, op1, -1]
                op1code = f"(S, {stCnt})"
                stCnt += 1

        # ------------ Operand 2 ------------

        if op2.isdigit():
            op2code = f'(C, {op2})'

        elif instruction == 'ds' or instruction == 'dc':
            symbolTable[var][2] = previous

        elif op2 in registers:
            op2code =  f"({registers.get(op2)})"
            
        elif "=" in op2:
            literal = op2.split('=')[1][1]
            if op2 in literalTable:
                op2code = f"(L, {literalTable.get(op2)[0]})"
            else:
                literalTable[ltCnt] = [ltCnt, literal, -1]
                op2code = f"(L, {ltCnt})"
                ltCnt += 1

        else:
            if op2 in symbolTable:
                op2code = f"(S, {symbolTable.get(op2)[0]})"
            elif op2 and instruction!='dc': #*** to avoid the literal entry in symbol table
                symbolTable[op2] = [stCnt, op2, previous]
                op2code = f"(S, {stCnt})"
                stCnt += 1
                
        if instruction!='stop':
            IC.append((opcode, op1code, op2code))
            icFile.write(f"{previous} {opcode} {op1code} {op2code}\n") 
        else:
            IC.append((opcode))
            icFile.write(f"{previous} {opcode}\n")

    else:
        print(instruction, "Instruction not defined. Exiting the program...")
        exit(0)
        
# added this to avoid literals without memory location
for literal, [index, lt, value] in literalTable.items():
    if value == -1:
        previous = current
        current += 1
        relativeAddresses.append(previous)
        literalTable[literal][2] = previous #////////changes current to previous

        opcode = "(DL, 01)"
        op1code = f"(C, {lt})"   
        icFile.write(f"{previous} {opcode} {op1code}\n")
                                       
print(symbolTable)
print(literalTable)