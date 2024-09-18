import re as regex

# Function to get key from a dictionary based on value
def get_key(val: str, dict: dict) -> any:
    for key, value in dict.items():
        if val == value:
            return key
    # Print debug information if value is not found
    # print(f"Value '{val}' not found in dictionary.")
    return None

inputfile = open('Macro_Assembler/pass1/input/program.asm', 'r')
outputfile = open('Macro_Assembler/pass1/output/output.txt', 'a')

MNTab = {}
PNTab = {}
KPDTab = {}

macroName = ""
kpdtabIndex = 1
kpdtabLoc = 1
mntIndex = 1
mdtLoc = 1

mSign = False
mDef = False

pattern = r'\s+'

for line in inputfile:
    if line == '\n':
        continue
    line = line.strip()

    cmd = regex.split(pattern, line.rstrip())
    # print(cmd)
    if(len(cmd) == 1 and cmd[0] == 'MACRO'):
        mSign = True
        continue

    if mSign:
        macroName = cmd.pop()
        PNTab[macroName] = {}
        parametersCnt = 0

        positionalpara = 0
        keywordpara = 0

        for param in cmd:
            if ',' in param:
                param = param.replace(',', '')
            if '&' in param and '=' not in param:
                parametersCnt += 1
                positionalpara += 1

                paramName = param[1:]

                PNTab[macroName][parametersCnt] = paramName

            elif '&' in param and '=' in param:
                parametersCnt += 1
                
                if keywordpara == 0:
                    kpdtabLoc = kpdtabIndex

                keywordpara += 1
                
                idx = param.index("=")

                paramName = param[1:idx]
                defaultval = param[idx+1:]

                PNTab[macroName][parametersCnt] = paramName

                KPDTab[kpdtabIndex] = {
                    'index': kpdtabIndex, 
                    'name': paramName, 
                    'value': defaultval if defaultval else '---',
                }

                kpdtabIndex += 1
            else:
                pass

        mSign = False
        mDef = True

        MNTab[mntIndex] = {
            'index': mntIndex,
            'name': macroName,
            'positionalpara': positionalpara,
            'keywordpara': keywordpara,
            'mdtp': mdtLoc,
            'kpdtp': kpdtabLoc if keywordpara else '---',
        }

        mntIndex += 1
        continue
    
    if mDef:
        mdtLoc += 1
        definationLine = ""

        for defline in cmd:
            if ',' in defline:
                defline = defline.replace(',', '')
            if '&' in defline:
                key = get_key(defline[1:], PNTab[macroName])
                if key is not None:
                    val = f'(P,{key})'
                    definationLine += val + " "
                else:
                    definationLine += defline + " "
            else:
                definationLine += defline + " "
                
        outputfile.write(definationLine + "\n")
        continue
    
    if len(cmd) == 1 and cmd[0] == 'MEND':  
        mdtLoc += 1
        mDef = False
        outputfile.write('MEND\n')
        continue
    
print("MacroNameTable: ", MNTab, "\n")
print("ParameterNameTable: ", PNTab, "\n")
print("KeywordParamDefaultTable: ", KPDTab, "\n")
