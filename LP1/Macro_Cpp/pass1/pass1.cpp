#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string> 

using namespace std;

class Macro{
    public:
    int mntc=0, mdtc=0, kptc=0;
    vector<vector<string>> MNT, KPDT, PNTABS;
    vector<string> MDT;
    unordered_map<string , int> AlaIndexMap;

    void pass1(string filename){
        ifstream inp(filename);
        if(!inp.is_open()){
            cerr<<"error opening file"<<endl;
            return;
        }
        string line;
        while(getline(inp, line)){
            if(line=="MACRO"){
                string macroname;
                getline(inp, line);
                istringstream iss(line);
                iss>>macroname;
                vector<string> pntab;
                int ppcnt =0 , kpcnt=0;
                string param;
                while(iss>>param){
                    if(param.back()==',') param.pop_back();
                    size_t equPos = param.find('=');
                    if(equPos == string::npos){
                        AlaIndexMap[param]= ppcnt+kpcnt;
                        pntab.push_back(param);
                        ppcnt++;
                    }else{
                        string pname, pval;
                        pname = param.substr(0, equPos);
                        pval = param.substr(equPos + 1);
                        AlaIndexMap[pname]= ppcnt +kpcnt;
                        pntab.push_back(pname);
                        kpcnt++;
                        KPDT.push_back({pname, pval});
                    }
                }
                MNT.push_back({to_string(++mntc), macroname, to_string(ppcnt), to_string(kpcnt), to_string(mdtc+1), to_string(kpcnt ? kptc+1: 0)});
                kptc += kpcnt;
                PNTABS.push_back(pntab);
                while(getline(inp, line)){
                    if(line == "MEND"){
                        MDT.push_back("MEND");
                        mdtc++;
                        break;
                    }
                    istringstream mdtline(line);
                    string token, processline;
                    while(mdtline >> token){
                        if(token.back()==',') token.pop_back();
                        if(AlaIndexMap.find(token) != AlaIndexMap.end()){
                            processline += "(P," + to_string(AlaIndexMap[token]+1) + ") ";
                        }else{
                            processline += token+" ";
                        }
                    }
                    MDT.push_back(processline);
                    mdtc++;
                }
            }
        }
        inp.close();

    }

    void saveMNT(string filename){
        ofstream out(filename);
        for(auto line: MNT){
            for(auto field: line){
                out<<field<<" ";
            }
            out<<endl;
        }
        out.close();
    }

    void saveMDT(string filename){
        ofstream out(filename);
        for(auto line: MDT){
            out<<line<<" \n";
        }
        out.close();
    }

    void saveKPDTAB(string filename){
        ofstream out(filename);
        int index=1;
        for(auto entry: KPDT){
            out<<index++ <<" "<< entry[0]<<" "<<(entry[1].empty() ? "-----" : entry[1]) <<"\n";
        }
        out.close();
    }

    void savePNTAB(string filename){
        ofstream out(filename);
        for(auto pntab: PNTABS){
            int index=1;
            for(auto param: pntab){
                out<< index++ <<" "<<param<<"\n";
            }
        }
        out.close();
    }
};

int main(){
    string file="input.txt";
    Macro mc;
    mc.pass1(file);
    mc.saveMNT("mnt.txt");
    mc.saveMDT("mdt.txt");
    mc.saveKPDTAB("kpdtab.txt");
    mc.savePNTAB("pntab.txt");
    return 0;
}