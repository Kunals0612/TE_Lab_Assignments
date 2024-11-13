#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;
class MacroPass2{
    public:
       vector<vector<string>> mnt, pntabs;
       vector<string> mdt;
       vector<pair<string,string>> kpdt;
    void loadTables(const string &mntFile, const string &mdtFile, const string &kpdtFile, const string &pntabFile){

        ifstream mntInp(mntFile);
        if(mntInp.is_open()){
            string line;
            while(getline(mntInp,line)){
                istringstream iss(line);
                vector<string>entry;
                string token;
                while(iss >> token){
                    entry.push_back(token);
                }
                mnt.push_back(entry);
            }
            mntInp.close();
        }else{
            cout<<"Error in opening file"<<endl;
        }

        ifstream mdtInp(mdtFile);
        if(mdtInp.is_open()){
            string line;
            while(getline(mdtInp,line)){
                mdt.push_back(line);
            }
        }

        ifstream pntabInp(pntabFile);
            if(pntabInp.is_open()){
                string line;
                vector<string> pntab;
                while(getline(pntabInp, line)){
                    if(line.empty()){
                        pntabs.push_back(pntab);
                        pntab.clear();
                    }else{
                        pntab.push_back(line);
                    }
                }
                if(!pntab.empty()){
                    pntabs.push_back(pntab);
                }
                pntabInp.close();
            }else{
                cout<<"Error in opening file"<<endl;
            }
        
        
        ifstream kpdtInp(kpdtFile);
        if(kpdtInp.is_open()){
            string line;
            while(getline(kpdtInp,line)){
                istringstream iss(line);
                string param, val;
                iss >> param >> val;
                kpdt.push_back({param,val});
            }
            kpdtInp.close();
        }else{
            cout<<"Error in opening file"<<endl;
        }
    }
    void pass2(const string &filename, const string &outputfile){
        ifstream inp(filename);
        ofstream out(outputfile);
        if(!inp.is_open() || !out.is_open()){
            cout<<"Error in opening file"<<endl;
        }
        string line;
        while(getline(inp,line)){
            istringstream iss(line);
            string macroname;
            iss >> macroname;
            bool isMacro = false;
            for(auto &entry : mnt){
                if(entry[1] == macroname){
                    isMacro = true;
                    cout<<"Processing Macro"<<endl;
                    int mdtIndex = stoi(entry[4])-1;
                    int kpdtIndex = stoi(entry[5])-1;
                    int ppCount = stoi(entry[2]);
                    int kpCount = stoi(entry[3]);
                    int totalParams = ppCount + kpCount;

                    vector<string> apTab(totalParams);

                    for(int i=ppCount; i<totalParams; i++){
                        apTab[i] = kpdt[kpdtIndex + (i-ppCount)].second;
                        cout<<"Default APTAB ["<<i<<"]"<<apTab[i]<<endl;
                    }

                    string args;
                    int posCount = 0;
                    while(iss >> args){
                        if(args.back() == ','){
                            args.pop_back();
                        }
                        size_t equPos = args.find("=");
                        if(equPos != string::npos){
                            string paramName = args.substr(0, equPos);
                            string paramVal = args.substr(equPos + 1);
                            cout<<"KeyWordParam: "<<paramName<<" "<<paramVal<<endl;
                            bool matched = false;
                            for(int i=ppCount; i<totalParams; i++){
                                cout<<"Comparing"<<paramName<<"with PNTAB Entry"<<pntabs[stoi(entry[0])-1][i]<<endl;
                                if(pntabs[stoi(entry[0])-1][i] == paramName){
                                    matched = true;
                                    apTab[i] = paramVal;
                                    cout<<"Matched APTAB ["<<i<<"]: "<<apTab[i]<<endl;
                                }
                            }
                            if(!matched){
                                cout<<"No match for keyword param: "<<paramName<<endl;
                            }
                        }else if(posCount < ppCount){
                            apTab[posCount++] = args;
                        }
                    }
                    out<<"APTAB for Macro call"<<macroname<<endl;
                    for(int i=0; i<apTab.size(); i++){
                        out << (i+1) << ":" << apTab[i] << endl;
                    }
                    out<<"Expanded Code: "<<endl;
                    for(int i=mdtIndex; i<mdt.size() && mdt[i] != "MEND"; i++){
                        istringstream mdtLine(mdt[i]);
                        string token;
                        while(mdtLine >> token){
                            if(token.back() == ','){
                                token.pop_back();
                            }
                            if(token.substr(0,3) == "(P,"){
                                int paramIndex = stoi(token.substr(3,token.size()-4))-1;
                                out<<apTab[paramIndex]<<" ";
                            }else{
                                out<<token<<" ";
                            }
                        }
                        out<<"\n";
                    }
                    break;
                }
            }
            if(!isMacro){
                out<<line<<"\n";
            }

        }
        inp.close();
        out.close();
        cout<<"ENDING OF PASS2"<<endl;
    }
};
int main(){
    MacroPass2 mc;
    mc.loadTables("./input/mnt.txt", "./input/mdt.txt", "./input/kpdt.txt", "./input/pnt.txt");
    mc.pass2("./input/p2_input.txt","./output/macro_pass2_output.txt");
    return 0;
}