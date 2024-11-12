#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Assembler
{
private:
    map<string, string> Symtab;
    map<string, string> Littab;

public:
    Assembler() {}

    vector<string> tokenize(string s)
    {
        vector<string> v;
        string x;
        stringstream ss(s);
        while (getline(ss, x, ' '))
        {
            if (!x.empty())
                v.push_back(x);
        }
        return v;
    }

    void readTables(string filename)
    {
        ifstream f(filename);
        string s;
        while (getline(f, s))
        {
            vector<string> token = tokenize(s);
            if (filename == "symtab.txt")
            {
                Symtab[token[0]] = token[2]; // Assume that symtab.txt format has: label, type, address
            }
            else
            {
                Littab[token[0]] = token[2]; // Assume that ltab.txt format has: label, type, address
            }
        }
    }

    void pass2()
    {
        ifstream f("./input/input.txt");
        ofstream w("./output/machineCode.txt");
        string s;

        while (getline(f, s))
        {
            int cnt = 0;
            if (s.length() > 0)
            {
                cout << s << endl;
                vector<string> token = tokenize(s);
                string write;
                int n = token.size();
                bool flag = true;

                for (int i = 0; i < n; i++)
                {
                    string op1 = "", op2 = "";
                    bool parsingOp1 = true; // Track whether we are parsing the first operand (before comma) or the second (after comma)

                    for (int j = 0; j < token[i].length(); j++)
                    {
                        if (token[i][j] == '(')
                        {
                            continue;
                        }
                        else if (token[i][j] == ',')
                        {
                            parsingOp1 = false; // After comma, start parsing the second operand
                        }
                        else
                        {
                            if (parsingOp1)
                                op1 += token[i][j];
                            else if (token[i][j] != ')')
                            {
                                op2 += token[i][j];
                            }
                        }
                    }
                    cout << op1 << " " << op2 << " " << cnt << endl;

                    // Processing each operand and generating the corresponding machine code
                    if (cnt == 1)
                    {
                        if (op1 == "RG")
                        {
                            write += "(" + op2 + ")";
                            cnt++;
                            continue;
                        }
                        else
                        {
                            write += "(00)";
                            cnt++;
                        }
                    }

                    // Handle the various operand types
                    if (op1 == "AD")
                    {
                        if (n == 2 || n == 1)
                        {
                            flag = false;
                            break;
                        }
                        else
                        {
                            write += "(00) ";
                            cnt++;
                        }
                    }
                    else if (op1 == "DL")
                    {
                        if (cnt == 0 && op2 == "02")
                        {
                            flag = 0;
                            break;
                        }
                        else
                        {
                            write += "(00)";
                            cnt++;
                        }
                    }
                    else if (op1 == "S")
                    {
                        if (Symtab.find(op2) != Symtab.end() && cnt > 0) // If symbol exists in Symtab
                        {
                            write += "(" + Symtab[op2] + ") ";
                            cout << Symtab[op2] << endl;
                            cnt++;
                        }
                    }
                    else if (op1 == "L")
                    {
                        if (Littab.find(op2) != Littab.end() && cnt > 0) // If literal exists in Littab
                        {
                            write += "(" + Littab[op2] + ") ";
                            cout << Littab[op2] << endl;
                            cnt++;
                        }
                    }
                    else
                    {
                        write += "(" + op2 + ") ";
                        cnt++;
                    }
                }

                if (flag)
                {
                    w << write << endl;
                }
            }
        }
    }
};

int main()
{
    string s = "./input/SymTab.txt"; // Symbol table file
    string l = "./input/LiTab.txt";   // Literal table file
    Assembler a;
    a.readTables(s); // Read symbol table
    a.readTables(l); // Read literal table
    a.pass2();       // Perform pass 2 and write machine code
}