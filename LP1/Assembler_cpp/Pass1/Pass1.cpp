#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

class SymTab
{
private:
    int id;
    string label;
    int add;

public:
    SymTab() : id(0), label(""), add(0) {}
    SymTab(int id, string label) : id(id), label(label), add(0) {}
    friend class Assembler;
};

class LTab
{
private:
    int id;
    string label;
    int add;

public:
    LTab() : id(0), label(""), add(0) {}
    LTab(int id, string label) : id(id), label(label), add(0) {}
    friend class Assembler;
};

class Assembler
{
private:
    map<string, pair<string, string>> mot;
    map<string, int> len;
    map<string, string> reg;

public:
    Assembler()
    {
        mot = {{"STOP", {"IS", "00"}}, {"ADD", {"IS", "01"}}, {"SUB", {"IS", "02"}}, {"MULT", {"IS", "03"}}, {"MOVER", {"IS", "04"}}, {"MOVEM", {"IS", "05"}}, {"COMP", {"IS", "06"}}, {"BC", {"IS", "07"}}, {"DIV", {"IS", "08"}}, {"READ", {"IS", "09"}}, {"PRINT", {"IS", "10"}}, {"START", {"AD", "01"}}, {"END", {"AD", "02"}}, {"ORIGIN", {"AD", "03"}}, {"EQU", {"AD", "04"}}, {"LTORG", {"AD", "05"}}, {"DC", {"DL", "01"}}, {"DS", {"DL", "02"}}};

        len = {{"IS", 1}, {"AD", 0}, {"DL", 0}};
        reg = {{"AREG", "01"}, {"BREG", "02"}, {"CREG", "03"}, {"DREG", "04"}};
    }

    vector<string> tokenize(string s)
    {
        vector<string> v;
        string x;
        for (auto i : s)
        {
            if (i != ' ')
                x += i;
            else
            {
                v.push_back(x);
                x.clear();
            }
        }
        if (!x.empty())
            v.push_back(x);
        return v;
    }

    SymTab &findsym(vector<SymTab> &s, const string &label)
    {
        static SymTab notFound(-1, "NULL");
        for (auto &i : s)
            if (i.label == label)
                return i;
        return notFound;
    }

    void pass1()
    {
        ifstream f("./input/input.txt");
        ofstream ic("./output/output.txt"), sym("./output/SymTab.txt"), lt("./output/LitTab.txt");
        vector<SymTab> symbolTable;
        vector<LTab> literalTable;

        if (!f.is_open())
        {
            cerr << "Error opening file" << endl;
            return;
        }

        int s_id = 0, l_id = 0, lc = 0;
        string s;

        while (getline(f, s))
        {
            string label, instruction, operand1, operand2, op1code, op2code, write;
            vector<string> tokens = tokenize(s);

            if (tokens.size() == 4)
            {
                label = tokens[0], instruction = tokens[1], operand1 = tokens[2], operand2 = tokens[3];
                SymTab st(s_id++, label);
                st.add = lc;
                symbolTable.push_back(st);
                write += to_string(lc) + " " + "(S," + to_string(st.id) + ") ";
                op1code = mot[instruction].first, op2code = mot[instruction].second;
                write += "(" + op1code + "," + op2code + ") ";
                if (reg.find(operand1) != reg.end())
                {
                    write += "(RG," + reg[operand1] + ") ";
                    if (operand2[0] != '=')
                    {
                        SymTab st1(s_id++, operand2);
                        symbolTable.push_back(st1);
                        write += "(S," + to_string(st1.id) + " ) ";
                    }
                    else
                    {
                        LTab lt1(l_id++, operand2);
                        literalTable.push_back(lt1);
                        write += "(L," + to_string(lt1.id) + " ) ";
                    }
                }
                lc++;
            }
            else if (tokens.size() == 3)
            {
                if (mot.find(tokens[0]) != mot.end())
                {
                    instruction = tokens[0], operand1 = tokens[1], operand2 = tokens[2];
                    op1code = mot[instruction].first, op2code = mot[instruction].second;
                    write += to_string(lc) + " " + "(" + op1code + "," + op2code + ") ";
                    if (reg.find(operand1) != reg.end())
                    {
                        write += "(RG," + reg[operand1] + ") ";
                        if (operand2[0] != '=')
                        {
                            SymTab st1(s_id++, operand2);
                            symbolTable.push_back(st1);
                            write += "(S," + to_string(st1.id) + " ) ";
                        }
                        else
                        {
                            LTab lt1(l_id++, operand2);
                            literalTable.push_back(lt1);
                            write += "(L," + to_string(lt1.id) + " ) ";
                        }
                    }
                    lc++;
                }
                else
                {
                    operand1 = tokens[0], instruction = tokens[1], operand2 = tokens[2];
                    SymTab &st = findsym(symbolTable, operand1);
                    if (st.id == -1)
                    {
                        SymTab s2(s_id++, operand1);
                        s2.add = lc;
                        symbolTable.push_back(s2);
                        st = s2;
                    }
                    st.add = lc;
                    write += to_string(lc) + " (S," + to_string(st.id) + ") ";
                    op1code = mot[instruction].first, op2code = mot[instruction].second;
                    write += "(" + op1code + "," + op2code + ") (C," + operand2 + ")";
                    lc++;
                }
            }
            else if (tokens.size() == 2)
            {
                instruction = tokens[0], label = tokens[1];
                if (instruction == "START")
                {
                    lc = stoi(label);
                    op1code = mot[instruction].first, op2code = mot[instruction].second;
                    write = "\t(" + op1code + "," + op2code + ") (C," + label + ")";
                }
                else if (instruction == "ORIGIN")
                {
                    op1code = mot[instruction].first, op2code = mot[instruction].second;
                    write = to_string(lc) + " (" + op1code + "," + op2code + ") ";
                    int offset = stoi(label.substr(label.find_first_of("+-") + 1));
                    string symbol = label.substr(0, label.find_first_of("+-"));
                    SymTab &st = findsym(symbolTable, symbol);
                    lc = (label.find('+') != string::npos) ? st.add + offset : st.add - offset;
                    write += "(C," + to_string(lc) + ")";
                }
                else
                {
                    op1code = mot[instruction].first, op2code = mot[instruction].second;
                    write = to_string(lc) + " (" + op1code + "," + op2code + ")";
                    SymTab &s1 = findsym(symbolTable, label);
                    write += "(S," + to_string(s1.id) + ")";
                    lc++;
                }
            }
            else
            {
                instruction = tokens[0];
                if (instruction == "LTORG")
                {
                    for (auto &i : literalTable)
                    {
                        write += to_string(lc) + " (AD,05) (DL,01) ";
                        write += "(C," + i.label.substr(2, i.label.size() - 3) + ")\n";
                        i.add = lc++;
                    }
                }
                else
                {
                    op1code = mot[instruction].first, op2code = mot[instruction].second;
                    write = to_string(lc) + " (" + op1code + "," + op2code + ")";
                    lc++;
                }
            }
            ic << write << endl;
        }

        for (auto &i : symbolTable)
            sym << i.id << " " << i.label << " " << i.add << endl;
        for (auto &i : literalTable)
            lt << i.id << " " << i.label << " " << i.add << endl;
    }
};

int main()
{
    Assembler a;
    a.pass1();
    return 0;
}