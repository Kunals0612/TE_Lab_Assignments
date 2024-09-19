import re

SymbolTable = {
    "n": [1, "n", -1],
    "mover": [2, "mover", -1],
    "movem": [3, "movem", -1],
    "again": [4, "again", 104],
    "term": [5, "term", 104],
    "add": [6, "add", -1],
    "comp": [7, "comp", -1],
    "le": [8, "le", 109],
    "div": [9, "div", -1],
    "result": [10, "result", -1]
}
LiteralTable = {}

def extract_code(ipwords):

    lc = ""
    opcode = ""
    op1code = ""
    op2code = ""

    # Debugging: Print ipwords and its length
    print(f"ipwords: {ipwords}")
    print(f"Length of ipwords: {len(ipwords)}")

    if len(ipwords) == 4:
        lc = ipwords[0] 
        try:
            opcode = ipwords[1].split(',')[1].replace(')', "")
            op1code = ipwords[2].replace('(', "").replace(')', "")
            cnt = ipwords[3].split(',')[1].replace(')', "")
            if 'S' in ipwords[3]:
                op2code = next((value for symb, [stcnt, symb, value] in SymbolTable.items() if stcnt == int(cnt)), "")
            elif 'L' in ipwords[3]:
                op2code = next((value for literal, [ltcnt, literal, value] in LiteralTable.items() if ltcnt == int(cnt)), "")
        except IndexError as e:
            print(f"IndexError in 4-element processing: {e}")
            return None

    elif len(ipwords) == 3:
        lc = ipwords[0]
        try:
            opcode = ipwords[1].split(',')[1].replace(')', "")
            cnt = ipwords[2].split(',')[1].replace(')', "")
            if 'C' in ipwords[2]:
                op1code = ipwords[2].split(',')[1].replace(')', "")
                op2code = ""
            elif 'S' in ipwords[2]:
                op1code = next((value for symb, [stcnt, symb, value] in SymbolTable.items() if stcnt == int(cnt)), "")
                op2code = ""
        except IndexError as e:
            print(f"IndexError in 3-element processing: {e}")
            return None

    elif len(ipwords) == 2:
        if "IS" in ipwords:
            lc = ipwords[0]
            try:
                opcode = ipwords[1].split(',')[1].replace(')', "")
            except IndexError as e:
                print(f"IndexError in 2-element IS processing: {e}")
                return None
            op1code = ""
            op2code = ""
        else:
            return None

    else:
        return None

    return lc, opcode, op1code, op2code

with open("output.txt") as file, open("output2.txt", 'a') as outputfile:
    pattern = r'\s+'
    for line in file:
        if line.strip() == '':
            continue
        ipwords = re.split(pattern, line.strip())
        result = extract_code(ipwords)
        if result:
            lc, opcode, op1code, op2code = result
            outputfile.write(f"{lc}\t{opcode}\t{op1code}\t{op2code}\n")

