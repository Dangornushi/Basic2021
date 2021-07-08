#include "main.hpp"

int main(int args, char** argv) {
    string filename = argv[1];
    string data = "";
    ifstream ifs( filename );
    ofstream ofs( split( filename, "." )[0] );
    
    while ( getline( ifs, data ) ) {
        if ( data != "" ) {
            if ( data.substr(data.length()-1, 1) == ":" ) {
                print(data);
                ofs << "01"+split(data, ":")[0] << endl;
            }
            else {
                string op = "";
                string instr = data.substr(0, 4);
                if (instr=="pop ") {
                    op = "02";
                }
                if (instr=="fode") {
                    op = "03";
                }
                if(instr== "mode") {
                    op = "04";
                }
                if (instr=="call") {
                    op = "05";
                }
                if (instr =="msg ") {
                    op = "11";
                }
                
                ofs << ";"+op+split(data, instr)[1] << endl;
            }
        }
    }
    return 0;
}