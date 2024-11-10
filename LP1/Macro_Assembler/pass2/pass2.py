import re as regex

# Define your tables
MacroNameTable = {
    1: {'index': 1, 'name': 'INCR', 'positionalpara': 3, 'keywordpara': 0, 'mdtp': 1, 'kpdtp': '---'}, 
    2: {'index': 2, 'name': 'INCR_M', 'positionalpara': 0, 'keywordpara': 3, 'mdtp': 5, 'kpdtp': 1}, 
    3: {'index': 3, 'name': 'INCR_D', 'positionalpara': 0, 'keywordpara': 3, 'mdtp': 9, 'kpdtp': 4}, 
    4: {'index': 4, 'name': 'TE1', 'positionalpara': 1, 'keywordpara': 1, 'mdtp': 13, 'kpdtp': 7}
}

ParameterNameTable = {
    'INCR': {1: 'MEM_VAL', 2: 'INCR_VAL', 3: 'REG'}, 
    'INCR_M': {1: 'MEM_VAL', 2: 'INCR_VAL', 3: 'REG'}, 
    'INCR_D': {1: 'MEM_VAL', 2: 'INCR_VAL', 3: 'REG'}, 
    'TE1': {1: 'T', 2: 'E'}
}

KeywordParamDefaultTable = {
    1: {'index': 1, 'name': 'MEM_VAL', 'value': '---'}, 
    2: {'index': 2, 'name': 'INCR_VAL', 'value': '---'}, 
    3: {'index': 3, 'name': 'REG', 'value': '---'}, 
    4: {'index': 4, 'name': 'MEM_VAL', 'value': '---'}, 
    5: {'index': 5, 'name': 'INCR_VAL', 'value': '---'}, 
    6: {'index': 6, 'name': 'REG', 'value': 'AREG'}, 
    7: {'index': 7, 'name': 'E', 'value': '---'}
}

# File handling
with open('/home/kunal/TE_Lab_Assignments/LP1/Macro_Assembler/pass2/input/calls.asm', 'r') as callFile, open('/home/kunal/TE_Lab_Assignments/LP1/Macro_Assembler/pass2/input/output.txt', 'r') as mdtFile, open('/home/kunal/TE_Lab_Assignments/LP1/Macro_Assembler/pass2/output/output.asm', 'a') as finalFile:

    def get_key(val: str, dictionary: dict) -> any:
        for key, value in dictionary.items():
            if val == value:
                return key
        return None

    def convert(lst):
        return ' '.join(lst)
    
    def process_params(param: str):
        pattern = r'\(([^,]+),(\d+)\)'
        match = regex.match(pattern, param)
        if match:
            component1 = match.group(1)
            component2 = int(match.group(2))
            return component1, component2
        else:
            return None

    pattern = r'\s+'

    for line in callFile:
        if line.strip() == '':
            continue
        line = line.strip()
        cmd = regex.split(pattern, line.rstrip())
        macroName = cmd[0]
        macroList = cmd[1:]

        mdtPointer = ""
        pp = 0
        kp = 0

        # Find macro details
        for key, value in MacroNameTable.items():
            if value['name'] == macroName:
                pp = value['positionalpara']
                kp = value['keywordpara']
                mdtPointer = value['mdtp']
                break

        if mdtPointer == "":
            print("No such macro exists")
            continue

        APTAB = ParameterNameTable[macroName].copy()
        aptPointer = 1

        # Process macroList
        for para in macroList:
            if para.endswith(','):
                para = para[:-1]  # Remove trailing comma
            if '=' in para:
                idx = para.index('=')
                paraName = para[:idx]
                paraVal = para[idx + 1:]

                key_index = get_key(paraName, APTAB)
                if key_index is not None:
                    APTAB[key_index] = paraVal
                else:
                    print(f"Warning: Parameter '{paraName}' not found in APTAB.")
            else:
                APTAB[aptPointer] = para
                aptPointer += 1

        # Set default keyword parameters
        if kp:
            for key, value in KeywordParamDefaultTable.items():
                param_key = get_key(value['name'], APTAB)
                if param_key is not None and APTAB[param_key] == '---':
                    APTAB[param_key] = value['value']

        expandedlines = []

        # Read macro definition from MDT
        curr = 0
        mdt_lines = []

        for mdtline in mdtFile:
            curr += 1
            if curr == mdtPointer:
                mdt_lines.append(mdtline.strip())
                break

        # Read until MEND
        for mdtLine in mdtFile:
            if 'MEND' in mdtLine:
                break
            mdt_lines.append(mdtLine.strip())

        # Process the macro lines
        for macroStatement in mdt_lines:
            macroCmd = regex.split(pattern, macroStatement)

            for itemIndex in range(len(macroCmd)):
                item = macroCmd[itemIndex]

                # Process parameter reference
                if '(' in item:
                    param_name, pos = process_params(item)
                    if pos in APTAB:  # Check if the position exists
                        macroCmd[itemIndex] = APTAB[pos]
                    else:
                        print(f"Warning: Parameter position '{pos}' not found in APTAB.")

            macroCmd[0] = "+" + macroCmd[0]  # Add a '+' at the beginning to denote expanded code
            expandedlines.append(convert(macroCmd))  # Add the converted command to expanded lines

        for expanded_line in expandedlines:
            finalFile.write(expanded_line + '\n')
    
    print(APTAB)