import re as regex
import json
# Directives mapping
directives = {
    "start" : "(AD, 01)",
    "end" : "(AD, 02)",
    "origin" : "(AD, 03)",
    "equ" : "(AD, 04)",
    "ltorg" : "(AD, 05)"
}  

# Mnemonics size mapping
mneumonicSize = {
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
mneumonic = {
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
conditionalCodes = {
    "lt" : 1,
    "le" : 2,
    "eq" : 3,
    "gt" : 4,
    "ge" : 5,
    "any" : 6
}

# Regular expression pattern for splitting lines
pattern = r'\s+'

# Initialize variables
label = ""
instruction = ""
op1 = ""
op2 = ""
op1code = ""
op2code = ""
current = 0
previous = 0
flag = False        
relativeAddresses = []
IC = []
stCnt = 1
ltCnt = 1

# Symbol and literal tables
symbolTable = {}
literalTable = {}

# Open input and output files
file = open('LP1/Assembler/pass1/input/program.asm','r')
outputfile = open('LP1/Assembler/pass1/output/IntermediateCode.txt','a')

# Iterate through each line in the input file
for line in file:
    label = ""
    instruction = ""
    op1 = ""
    op2 = ""
    op1code = ""
    op2code = ""
    var = ""
    
    # Skip empty lines
    if line == '/n':
        continue
    line = line.strip()

    # Split the line into tokens using the regex pattern
    cmd = regex.split(pattern, line.rstrip())
    cmd = list(map(lambda x: x.lower(), cmd))  # Convert tokens to lowercase

    # Determine the number of tokens and parse accordingly
    if len(cmd) == 4:
        label = cmd[0]
        instruction = cmd[1]
        op1 = cmd[2]
        op2 = cmd[3]
    
    elif len(cmd) == 3:
        cmdIndex = -1
        for c in cmd:
            if c in mneumonic:
                if c == "dc" or c == "ds":
                    var = cmd[0]
                    cmdIndex = 1
                    op1 = cmd[2]
                    flag = True
                    break
                else:
                    cmdIndex = cmd.index(c)
                    break

            if c in directives:
                cmdIndex = cmd.index(c)
                break

        instruction = cmd[cmdIndex]
        if cmdIndex == 0:
            op1 = cmd[0]
            op2 = cmd[1]
        elif flag == False:
            op1 = cmd[cmdIndex-1]
            op2 = cmd[cmdIndex+1]

    elif len(cmd) == 2:
        cmdIndex = -1
        for c in cmd:
            if c in directives:
                cmdIndex = cmd.index(c)
            if c in mneumonic:
                cmdIndex = cmd.index(c)
            instruction = cmd[cmdIndex]
            if cmdIndex == 0:
                op1 = cmd[1]
            else:
                label = cmd[0]

    else:
        instruction = cmd[0]

    # Handle directives
    if instruction in directives:
        if instruction == 'start':
            current = int(cmd[1])
            opcode = directives.get(instruction)
            op1code = f"(C,{op1})"
            outputfile.write(f" {opcode} {op1code}\n")
            continue
        elif instruction == 'end':
            op1code = directives.get(instruction)
            outputfile.write(f"   {opcode}\n")
            break
        elif instruction == 'origin':
            op1code = directives.get(instruction)
            op1 = cmd[1]
            if '-' in op1:
                label = op1.split('-')[0]
                offset = op1.split('-')[1]
                op1code = f"(S, {symbolTable.get(label)[0]})-{offset}"
                previous = current
                current = symbolTable.get(label)[2] - int(offset)
                relativeAddresses.append(previous)
                outputfile.write(f"    {opcode} {op1code}\n")
            elif '+' in op1:
                label = op1.split('+')[0]
                offset = op1.split('+')[1]
                op1code = f"(S, {symbolTable.get(label)[0]})+{offset}"
                previous = current
                current = symbolTable.get(label)[2] + int(offset)
                relativeAddresses.append(previous)
                outputfile.write(f"    {opcode} {op1code}\n")
            else:
                op1code = f"(S, {symbolTable.get(op1)[0]})"
                previous = current
                current = symbolTable.get(op1)[2]
                relativeAddresses.append(previous)
                outputfile.write(f"    {opcode} {op1code}\n")

        # elif instruction == 'equ':
        #     op1 = cmd[0]
        #     op2 = cmd[2]
        #     symbolTable[op1][2] = symbolTable[op2][2]

        elif instruction == 'ltorg':
            for literal, [index, lt, value] in literalTable.items():
                if value == -1:
                    previous = current
                    current += 1
                    relativeAddresses.append(previous)
                    literalTable[literal][2] = previous 
                    opcode = "(DL, 01)"
                    op1code = f"(C, {lt})"  
                    outputfile.write(f"{previous} {opcode} {op1code}\n") 
                else:
                    pass

    # Handle mnemonics
    elif instruction in mneumonic:
        if instruction == 'ds':
            op2code = f""
        if instruction == 'dc':
            op2code = f""
        opcode = mneumonic.get(instruction)
        size = int(mneumonicSize.get(instruction))

        previous = current
        current += size

        relativeAddresses.append(previous)

        # Update symbol table
        if label:
            if label in symbolTable:
                symbolTable[label][2] = previous
            else:
                symbolTable[label] = [stCnt, label, previous]
                stCnt += 1  

        # Process operands
        if instruction == 'bc':
            op1code = f'({conditionalCodes.get(op1)})'

        elif op1.isdigit():
            op1code = f'(C,{op1})'
        elif op1 in registers:
            op1code = f'({registers.get(op1)})'
        elif "=" in op1:
            literal = op1.split('=')[1][1]
            if op1 in literalTable:
                op1code = f"(L, {literalTable.get(op1)[0]})"
            else:
                literalTable[ltCnt] = [ltCnt, literal, -1]
                op1code = f"(L, {ltCnt})"
                ltCnt += 1
        elif instruction == 'ds' or instruction == 'dc':
            symbolTable[op1][2] = previous
        else:
            if op1 in symbolTable:
                op1code = f"(S, {symbolTable.get(op1)[0]})"
            elif op1:
                symbolTable[op1] = [stCnt, op1, -1]
                op1code = f"(S, {stCnt})"
                stCnt += 1
        
        # Process second operand
        if op2.isdigit():
            op2code = f'(C, {op2})'

        elif instruction == 'ds' or instruction == 'dc':
            # print("hello")
            pass
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
            elif op2 and instruction != 'dc':
                symbolTable[op2] = [stCnt, op2, previous]
                op2code = f"(S, {stCnt})"
                stCnt += 1
        
        # Append the instruction with operands to the instruction code list
        if instruction != 'stop':
            IC.append((opcode, op1code, op2code))
            outputfile.write(f"{previous} {opcode} {op1code} {op2code}\n")
        else:
            IC.append((opcode))
            outputfile.write(f"{previous} {opcode}\n")

    else:
        # If instruction is neither a directive nor a mnemonic, exit with an error
        print(instruction, "Instruction not defined. Exiting the program...")
        exit(0)

# Process literals that haven't been assigned a value yet
for literal, [index, lt, value] in literalTable.items():
    if value == -1:
        previous = current
        current += 1
        relativeAddresses.append(previous)
        literalTable[literal][2] = previous 

        opcode = "(DL, 01)"
        op1code = f"(C, {lt})"   
        outputfile.write(f"{previous} {opcode} {op1code}\n")

# Output symbol and literal tables
# print("SymbolTable is: ", symbolTable)
# print("LiteralTable is: ", literalTable)
outputfile.write(f"SymbolTable: {json.dumps(symbolTable)}")
outputfile.write(f"LiteralTable:{json.dumps(literalTable)}")
# Close the input and output files
file.close()
outputfile.close()