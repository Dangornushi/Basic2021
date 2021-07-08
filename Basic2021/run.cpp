#include "main.hpp"

map<string, string>funcdict;
vector<string>stack;
string nowmode = "";
string nowvall = "";
string mode = "";
int spc = 0;

void VM( map<string, string>funcdict, string funcname, vector<string>stack  ) {
    vector<string>vec;
    string regis, regis2,base;

    vec = split(funcdict[funcname], ";");
    for ( int i = 0; i < vec.size(); i++ ) {
        if (vec[i] != "") {
            string data = vec[i];
            string instr = data.substr(0, 2);
            base = split( data, instr)[1];
            if (instr=="02") {
                //TODO : mov
                /*
                print(split(split( base, "rax")[1]+to_string(spc), " ")[1]);
                */
                int op1 = atoi( split( split( base, "rax")[1], " " )[0].c_str() );
                string  op2 = split( split( base, "rax")[1], " " )[1];
                if ( base.substr(5, 3) == "rax" ) {
                    stack.insert(stack.begin()+spc, stack[atoi(split(split(base, " ")[1], "rax" )[1].c_str())]);
                }
                else {
                    stack.insert(stack.begin()+spc, op2);
                }
                spc++;
            }

            else if (instr=="05") {
                string call_funcname = split(base, "[")[0];
                vector<string> arg = split( split(base, "[")[1], " ");
                VM(funcdict, call_funcname, stack);
            }

            else if (instr=="21") {
                int op1 = atoi( base.substr(3,1).c_str())-1;
                int op2 = atoi( base.substr(8,1).c_str())-1;
                stack[op1] = to_string( atoi(stack[op1].c_str() ) + atoi(stack[op2].c_str() ) );
            }

            else if (instr=="22") {
                int op1 = atoi( base.substr(4,4).c_str());
                int op2 = atoi( base.substr(8,8).c_str());
                stack[op1] = to_string( atoi(stack[op1].c_str() ) - atoi(stack[op2].c_str() ) );
            }

            else if (instr=="23") {
                int op1 = atoi( base.substr(4,4).c_str());
                int op2 = atoi( base.substr(8,8).c_str());
                stack[op1] = to_string( atoi(stack[op1].c_str() ) * atoi(stack[op2].c_str() ) );
            }

            else if (instr=="24") {
                int op1 = atoi( base.substr(4,4).c_str());
                int op2 = atoi( base.substr(8,8).c_str());
                stack[op1] = to_string( atoi(stack[op1].c_str() ) / atoi(stack[op2].c_str() ) );
            }
            
            else if (instr=="11") {
                if (base.substr(0, 1) == "\"") {
                    cout << replace ( base, "\"" ) << endl;
                }
                else
                if ( base.substr(0, 1) == "'" ) {
                    cout << replace ( base, "'" ) << endl;
                }
                else {
                    cout << stack[atoi(split(base, "rax")[1].c_str())-1] << endl;
                }
            }
            
        }
    }
    return;
}

int main( int args, char **argv ) {
    string filename = argv[1];
    string data, instr, funcname;
    ifstream ifs(filename);
    int *intptr;
    while ( getline( ifs, data  ) ) {
        if ( data.substr(0,2) == "01" ) {
            funcname = split(data, "01")[1];
        }
        else {
            funcdict[funcname] += data;
        }
    }
    vector<string>stack;
    vector<vector<string>>stacks;
    VM(funcdict, "main", stack);

    return 0;
}