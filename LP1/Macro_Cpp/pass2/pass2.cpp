#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class MacroPass2 {
public:
    static vector<vector<string>> mnt;         // Macro Name Table
    static vector<string> mdt;                 // Macro Definition Table
    static vector<pair<string, string>> kpdt;  // Keyword Parameter Table
    static vector<vector<string>> pntabs;     // PNTABs for each macro

    static void pass2(const string& filename, const string& outputFilename);
    static void loadTables(const string& mntFile, const string& mdtFile,
                           const string& kpdtFile, const string& pntabFile);

    static void debugTables(); // Helper function to print out the tables for debugging
};

// Initialize static variables
vector<vector<string>> MacroPass2::mnt;
vector<string> MacroPass2::mdt;
vector<pair<string, string>> MacroPass2::kpdt;
vector<vector<string>> MacroPass2::pntabs;

void MacroPass2::debugTables() {
    // Debug: Print the loaded tables
    cout << "--- MNT ---\n";
    for (const auto& entry : mnt) {
        for (const auto& e : entry) {
            cout << e << " ";
        }
        cout << endl;
    }

    cout << "--- MDT ---\n";
    for (const auto& line : mdt) {
        cout << line << endl;
    }

    cout << "--- KPDTP ---\n";
    for (const auto& entry : kpdt) {
        cout << entry.first << " = " << entry.second << endl;
    }

    cout << "--- PNTABs ---\n";
    for (size_t i = 0; i < pntabs.size(); ++i) {
        cout << "PNTAB for Macro " << i + 1 << ":\n";
        for (const auto& p : pntabs[i]) {
            cout << p << endl;
        }
    }
}

void MacroPass2::loadTables(const string& mntFile, const string& mdtFile,
                            const string& kpdtFile, const string& pntabFile) {
    // Load MNT
    ifstream mntInp(mntFile);
    if (mntInp.is_open()) {
        string line;
        while (getline(mntInp, line)) {
            istringstream iss(line);
            vector<string> entry;
            string token;
            while (iss >> token) {
                entry.push_back(token);
            }
            mnt.push_back(entry);
        }
        mntInp.close();
    } else {
        cerr << "Error: Unable to open MNT file.\n";
    }

    // Load MDT
    ifstream mdtInp(mdtFile);
    if (mdtInp.is_open()) {
        string line;
        while (getline(mdtInp, line)) {
            mdt.push_back(line);
        }
        mdtInp.close();
    } else {
        cerr << "Error: Unable to open MDT file.\n";
    }

    // Load KPDTP
    ifstream kpdtInp(kpdtFile);
    if (kpdtInp.is_open()) {
        string line;
        while (getline(kpdtInp, line)) {
            istringstream iss(line);
            string param, defaultVal;
            iss >> param >> defaultVal;
            kpdt.emplace_back(param, defaultVal);
        }
        kpdtInp.close();
    } else {
        cerr << "Error: Unable to open KPDTP file.\n";
    }

    // Load PNTAB
    ifstream pntabInp(pntabFile);
    if (pntabInp.is_open()) {
        string line;
        vector<string> pntab;
        while (getline(pntabInp, line)) {
            if (line.empty()) {
                pntabs.push_back(pntab);
                pntab.clear();
            } else {
                pntab.push_back(line);
            }
        }
        if (!pntab.empty()) {
            pntabs.push_back(pntab);  // Add the last PNTAB if not empty
        }
        pntabInp.close();
    } else {
        cerr << "Error: Unable to open PNTAB file.\n";
    }
}
void MacroPass2::pass2(const string& filename, const string& outputFilename) {
    cout << "---- STARTING PASS 2 ----\n";
    ifstream inp(filename);
    ofstream out(outputFilename);

    if (!inp.is_open() || !out.is_open()) {
        cerr << "Error: Unable to open input or output file.\n";
        return;
    }

    // Debug print of loaded tables
    debugTables();

    string line;
    while (getline(inp, line)) {
        istringstream iss(line);
        string macroName;
        iss >> macroName;

        bool isMacro = false;
        for (const auto& entry : mnt) {
            if (entry[1] == macroName) {
                cout << "Processing macro call: " << macroName << endl;
                isMacro = true;

                int mdtIndex = stoi(entry[4]) - 1;   // Correct MNT index (1-based to 0-based)
                int kpdtIndex = stoi(entry[5]) - 1;  // Correct KPDTP index (1-based to 0-based)
                int ppCount = stoi(entry[2]);
                int kpCount = stoi(entry[3]);
                int totalParams = ppCount + kpCount;

                vector<string> aptab(totalParams);

                // Initialize APTAB with default values for keyword parameters
                cout << "Initializing APTAB with defaults from KPDTP:\n";
                for (int i = ppCount; i < totalParams; ++i) {
                    aptab[i] = kpdt[kpdtIndex + (i - ppCount)].second;
                    cout << "Default APTAB[" << i << "] = " << aptab[i] << endl;
                }

                // Parse actual arguments from the macro call
                string arg;
                int posCount = 0;
                while (getline(iss, arg, ',')) {
                    arg = arg.substr(arg.find_first_not_of(" \t"), arg.find_last_not_of(" \t") + 1);
                    cout << "Processing argument: '" << arg << "'" << endl;

                    size_t equalPos = arg.find('=');
                    if (equalPos != string::npos) {
                        // Keyword parameter
                        string paramName = arg.substr(0, equalPos);
                        string paramValue = arg.substr(equalPos + 1);

                        cout << "Keyword Parameter: " << paramName << " = " << paramValue << endl;

                        bool matched = false;
                        for (int j = ppCount; j < totalParams; ++j) {
                            cout << "Comparing " << paramName << " with PNTAB entry: " << pntabs[stoi(entry[0]) - 1][j] << endl;
                            if (pntabs[stoi(entry[0]) - 1][j] == paramName) {
                                aptab[j] = paramValue;
                                matched = true;
                                cout << "Matched! APTAB[" << j << "] = " << aptab[j] << endl;
                                break;
                            }
                        }
                        if (!matched) {
                            cout << "No match for keyword parameter: " << paramName << endl;
                        }
                    } else if (posCount < ppCount) {
                        // Positional parameter
                        aptab[posCount++] = arg;
                        cout << "Positional Parameter: " << arg << " at APTAB[" << posCount - 1 << "]" << endl;
                    }
                }

                // Output the constructed APTAB
                out << "\n--- APTAB for Macro Call " << macroName << " ---\n";
                for (int i = 0; i < aptab.size(); ++i) {
                    out << (i + 1) << ": " << aptab[i] << endl;
                }

                // Now expand the macro using MDT
                out << "Expanded Code\n";
                for (int i = mdtIndex; i < mdt.size() && mdt[i] != "MEND"; ++i) {
                    istringstream mdtLine(mdt[i]);
                    string token;
                    while (mdtLine >> token) {
                        if (token.back() == ',') token.pop_back();

                        // Check for (P,n) notation to replace with aptab[n-1]
                        if (token.substr(0, 3) == "(P,") {
                            int paramIndex = stoi(token.substr(3, token.size() - 4)) - 1;
                            out << aptab[paramIndex] << " ";
                        } else {
                            out << token << " ";
                        }
                    }
                    out << "\n";
                }
                break;
            }
        }

        if (!isMacro) {
            out << line << "\n"; // If not a macro, print it as is
        }
    }

    inp.close();
    out.close();
    cout << "---- ENDING PASS 2 ----\n";
}

int main() {
    // Modify the file paths as needed
    MacroPass2::loadTables("mnt.txt", "mdt.txt", "kpdt.txt", "pnt.txt");

    // Execute Pass 2 for the input and output files
    MacroPass2::pass2("p2_input.txt", "macro_pass2_output.txt");

    return 0;
}
