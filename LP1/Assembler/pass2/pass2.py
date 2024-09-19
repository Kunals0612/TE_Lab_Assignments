import re as regex

# Define symbol and literal tables
symboltable = {
    'a': [1, 'a', 217],
    'loop': [2, 'loop', 202],
    'b': [3, 'b', 218],
    'next': [4, 'next', 214],
    'back': [5, 'back', 202],
    'last': [6, 'last', 216]
}

literaltable = {
    1: [1, '5', 211],
    2: [2, '1', 212],
    3: [3, '1', 219]
}

# Open the input and output files
with open('/home/kunal/TE_Lab_Assignments/LP1/Assembler/pass2/input/IntermediateCode.txt', 'r') as icfile, \
     open('/home/kunal/TE_Lab_Assignments/LP1/Assembler/pass2/output/pass2.txt', 'a') as opfile2:

    # Initialize variables
    opcode = op1code = op2code = ""
    lc = ""
    cnt = -1
    pattern = r'\s+'

    # Process each line in the intermediate code file
    for line in icfile:
        
        
        if line.strip() == '':
            continue
        
        line = line.strip()
        ipwords = regex.split(pattern, line.rstrip())
        
        # Print line for debugging
        print(f"Processing line: {line}")
        print(f"ipwords: {ipwords}")

        if len(ipwords) == 4:
            # LC OPCODE OP1CODE OP2CODE
            lc = ipwords[0]
            
            if ',' in ipwords[1]:
                opcode_parts = ipwords[1].split(',')
                if len(opcode_parts) > 1:
                    opcode = opcode_parts[1].replace(')', "")
                else:
                    print(f"Unexpected format in opcode: {ipwords[1]}")
                    continue
            else:
                print(f"No comma found in opcode: {ipwords[1]}")
                continue

            op1code = ipwords[2].replace('(', "").replace(')', "")
            try:
                cnt = ipwords[3].split(',')[1].replace(')', "")
            except IndexError:
                print(f"Error processing cnt from ipwords[3]: {ipwords[3]}")
                continue
            
            cnt = int(cnt)
            
            if 'S' in ipwords[3]:
                op2code = next((value for symbol, [stcnt, symb, value] in symboltable.items() if stcnt == cnt), "")
            elif 'L' in ipwords[3]:
                op2code = next((value for literal, [ltcnt, literal_value, value] in literaltable.items() if ltcnt == cnt), "")
            print(f"Writing to file: {lc}\t{opcode}\t{op1code}\t{op2code}")
        
            opfile2.write(f"{lc}\t{opcode}\t{op1code}\t{op2code}\n")

        elif len(ipwords) == 3:
            # LC OPCODE CONSTANT*** FOR DL opcode
            lc = ipwords[0]
            
            if ',' in ipwords[1]:
                opcode_parts = ipwords[1].split(',')
                if len(opcode_parts) > 1:
                    opcode = opcode_parts[1].replace(')', "")
                else:
                    print(f"Unexpected format in opcode: {ipwords[1]}")
                    continue
            else:
                print(f"No comma found in opcode: {ipwords[1]}")
                continue

            try:
                cnt = ipwords[2].split(',')[1].replace(')', "")
            except IndexError:
                print(f"Error processing cnt from ipwords[2]: {ipwords[2]}")
                continue
            
            cnt = int(cnt)
            
            if 'C' in ipwords[2]:
                op1code = ipwords[2].split(',')[1].replace(')', "")
            elif 'S' in ipwords[2]:
                op1code = next((value for symbol, [stcnt, symb, value] in symboltable.items() if stcnt == cnt), "")
        
            print(f"Writing to file: {lc}\t{opcode}\t{op1code}\t{op2code}")
        
            opfile2.write(f"{lc}\t{opcode}\t{op1code}\t{op2code}\n")
        elif len(ipwords) == 2:
            if 'IS' in ipwords[1]:
                lc = ipwords[0]
                if ',' in ipwords[1]:
                    opcode_parts = ipwords[1].split(',')
                    if len(opcode_parts) > 1:
                        opcode = opcode_parts[1].replace(')', "")
                    else:
                        print(f"Unexpected format in opcode: {ipwords[1]}")
                        continue
                else:
                    print(f"No comma found in opcode: {ipwords[1]}")
                    continue
            else:
                continue
            print(f"Writing to file: {lc}\t{opcode}\t{op1code}\t{op2code}")
        
            opfile2.write(f"{lc}\t{opcode}\t{op1code}\t{op2code}\n")

        else:
            print(f"Writing to file: {lc}\t{opcode}\t{op1code}\t{op2code}")
        
            opfile2.write(f"{lc}\t{opcode}\t{op1code}\t{op2code}\n")
            continue
        
        # Print the output to be written for debugging
      

# Close files
icfile.close()
opfile2.close()
