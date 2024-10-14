from mnemonics import IS,AD,DL, OPCODE
from pass1 import SYMBOL,LITERAL

f1 = open("intermediateCode.txt")
code = []
for line in f1:
    if "AD" in line:
        continue
    else:
        line_array = line.split()
        code.append(line_array)
f1.close()

def declareStatementFunc(line):
    if "(DL,01)" in line:
        word = (line[2])
        word = word.zfill(3)
        f2.write("+ 00 00 " + (word) )
        f2.write("\n")
    else:
        word = int(line[2])
        while word != 0:
            f2.write("+ -- -- --- \n")
            word = word-1

f2 = open("opcodeOutput.txt", "w")
for line in code:
    if "(DL,01)" in line or "(DL,02)" in line:
        declareStatementFunc(line)        
    else:    
        f2.write("+ ")
        for word in line:
            if word in OPCODE:
                f2.write(OPCODE[word] + " ")
            elif word in LITERAL:
                f2.write(LITERAL[word].zfill(3) + " ")
            elif word in SYMBOL:
                f2.write(SYMBOL[word].zfill(3) + " ")        
        f2.write("\n")