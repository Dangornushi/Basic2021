#include "main.hpp"

void print ( string word ) {
    cout << word << endl;
    return;
}

void printint ( int word ) {
    cout << word << endl;
    return;
}

vector<string> import(string funcname, string filename) {

    ifstream ifs ( filename.c_str() ) ;
    string data3;
    vector<string> result;
    int count = 0;
    int count2 = 0;
    int j = 0;
    int j2 = 0;

    while ( getline( ifs, data3 ) ) {
        if ( data3.find( ":" ) != string::npos && funcname == split( data3, "(" )[0] ) {
            count++;
            j = 1;
        }
        if ( data3.find( ":" ) != string::npos && funcname != split( data3, "(" )[0] ) {
            count++;
            j = 0;
        }
        if ( data3.substr( 0, 7 ) == "end;" ) {
            count2++;
            if ( count == count2 ) {
                
            }
        }
        if ( j == 1 ) {
            result.resize(j2+1);
            result[j2] = data3;
            j2++;
        }
    }
    ifs.close();
    return result;
}

vector<int> hex(const char *string) {
    int len = (int)strlen(string);
    vector<int> vec;
    int vi = 0;
    for (int i=0; i<len; i+=2) {
        unsigned int x;
        sscanf((char *)(string + i), "%02x", &x);
        vec[vi] = x;
        vi++;
    }
    return vec;
}

bool intj ( string hoge ) {
    try {
        return true;
    }
    catch (std::out_of_range &e) {
        return false;
    }
}

int intifj( string data, map<string, int> valls, string mark ) {
    string funcname = split( data, ", " )[2], a, b;
    a = split( replace( data, mark+" " ), ", " )[0];
    b = split( data, ", " )[1];
    if ( mark == "jnp" ) {
        if ( intkeyfind( valls, a ) ) {
            if ( intkeyfind( valls, b ) ) {
                if ( valls[a] > valls[b] ) {
                    return 0;
                }
                else {
                    return 1;
                }
            }
            else {
                if ( valls[a] > atoi(b.c_str() ) ) {
                    return 0;
                }
                else {
                    return 1;
                }
            }
        }
        if ( intkeyfind( valls, b ) ) {
            if ( atoi( a.c_str() ) > valls[b] ) {
                return 0;
            }
        }
        else {
            if ( atoi( a.c_str() ) > atoi( b.c_str() ) ) {
                return 0;
            }
            else {
                return 1;
            }
        }
    }
    if ( mark == "ja" ) {
        if ( intkeyfind( valls, a ) ) {
            if ( intkeyfind( valls, b ) ) {
                if ( valls[a] < valls[b] ) {
                    return 0;
                }
                else {
                    return 1;
                }
            }
            else {
                if ( valls[a] < atoi( b.c_str() ) ) {
                    return 0;
                }
                else {
                    return 1;
                }
            }
        }
        if ( intkeyfind( valls, b ) ) {
            if ( atoi( a.c_str() ) < valls[b] ) {
                return 0;
            }
        }
        else {
            if ( atoi( a.c_str() ) < atoi( b.c_str() ) ) {
                return 0;
            }
            else {
                return 1;
            }
        }
    }
    return 1;
}

int ifj( string data, map<string, string> valls, string mark ) {
    string funcname = split( data, ", " )[2], a, b;
    a = split( replace( data, mark ), ", " )[0];
    b = split( data, ", " )[1];
    if ( mark == "jne " ) {
        if ( keyfind( valls, a ) ) {
            if ( keyfind( valls, b ) ) {
                if ( atoi(valls[a].c_str() ) > atoi(valls[b].c_str() ) ) {
                    return 0;
                }
                else {
                    return 1;
                }
            }
            else {
                if ( atoi(valls[a].c_str()) > atoi(b.c_str() ) ) {
                    return 0;
                }
                else {
                    return 1;
                }
            }
        }
    }
    if ( mark == "ja " ) {
        if ( keyfind( valls, a ) ) {
            if ( keyfind( valls, b ) ) {
                if ( atoi( valls[a].c_str() ) < atoi( valls[b].c_str() ) ) {
                    return 0;
                }
                else {
                    return 1;
                }
            }
            else {
                if ( atoi( valls[a].c_str() ) < atoi( b.c_str() ) ) {
                    return 0;
                }
                else {
                    return 1;
                }
            }
        }
        else {
            if ( atoi( a.c_str() ) < atoi( b.c_str() ) ) {
                return 0;
            }
            else {
                return 1;
            }
        }
    }
    return 1;
}

string calc( string data, map<string, string> valls, string mark ) {
    ostringstream oss;
    string a = split( data, ", " )[1].c_str();
    string b = split( data, ", " )[2].c_str();
    string x = replace( split( data, ", " )[0], mark );
    int y = atoi( split( data, ", " )[1].c_str() );
    int z = atoi( split( data, ", " )[2].c_str() );
    
    if ( keyfind(valls, a) ) {
        if ( keyfind(valls, b) ) {
            if ( mark == "add " ) { oss << atoi(valls[a].c_str()) + atoi(valls[b].c_str()); }
            if ( mark == "sub " ) { oss << atoi(valls[a].c_str()) - atoi(valls[b].c_str()); }
            if ( mark == "mul " ) { oss << atoi(valls[a].c_str()) * atoi(valls[b].c_str()); }
            if ( mark == "div " ) { oss << atoi(valls[a].c_str()) / atoi(valls[b].c_str()); }
        }
        else {
            if ( mark == "add " ) { oss << atoi(valls[a].c_str()) + z; }
            if ( mark == "sub " ) { oss << atoi(valls[a].c_str()) - z; }
            if ( mark == "mul " ) { oss << atoi(valls[a].c_str()) * z; }
            if ( mark == "div " ) { oss << atoi(valls[a].c_str()) / z; }
        }
    }
    else {
        if ( keyfind(valls, b) ) {
            if ( mark == "add " ) { oss << y + atoi(valls[b].c_str()); }
            if ( mark == "sub " ) { oss << y - atoi(valls[b].c_str()); }
            if ( mark == "mul " ) { oss << y * atoi(valls[b].c_str()); }
            if ( mark == "div " ) { oss << y / atoi(valls[b].c_str()); }
        }
        else {
            if ( mark == "add " ) { oss << y + z; }
            if ( mark == "sub " ) { oss << y - z; }
            if ( mark == "mul " ) { oss << y * z; }
            if ( mark == "div " ) { oss << y / z; }
        }
    }
    valls[x] += oss.str().c_str();
    return valls[x];
}

string replace( string datadata, string replace_word ) {
    string data;
    data = regex_replace( datadata, regex( replace_word ), "" );
    return data;
}

vector<string> split(string str, string separator) {
    vector<string> result;
    string tstr = str + separator;
    long l = tstr.length(), sl = separator.length();
    string::size_type pos = 0, prev = 0;
    
    for (;pos < l && (pos = tstr.find(separator, pos)) != string::npos; prev = (pos += sl)) {
        result.emplace_back(tstr, prev, pos - prev);
    }
    return result;
}

string hextostring( string hex ) {
    string word;
    map<string, string> hexs;
    hexs["41"] = "A";
    hexs["42"] = "B";
    hexs["43"] = "C";
    hexs["44"] = "D";
    hexs["45"] = "E";
    hexs["46"] = "F";
    hexs["47"] = "G";
    hexs["48"] = "H";
    hexs["49"] = "I";
    hexs["4a"] = "J";
    hexs["4b"] = "K";
    hexs["4c"] = "L";
    hexs["4d"] = "M";
    hexs["4e"] = "N";
    hexs["4f"] = "O";
    hexs["50"] = "P";
    hexs["51"] = "Q";
    hexs["52"] = "R";
    hexs["53"] = "S";
    hexs["54"] = "T";
    hexs["55"] = "U";
    hexs["56"] = "V";
    hexs["57"] = "W";
    hexs["58"] = "X";
    hexs["59"] = "Y";
    hexs["5a"] = "Z";
    hexs["61"] = "a";
    hexs["62"] = "b";
    hexs["63"] = "c";
    hexs["64"] = "d";
    hexs["65"] = "e";
    hexs["66"] = "f";
    hexs["67"] = "g";
    hexs["68"] = "h";
    hexs["69"] = "i";
    hexs["6a"] = "j";
    hexs["6b"] = "k";
    hexs["6c"] = "l";
    hexs["6d"] = "m";
    hexs["6e"] = "n";
    hexs["6f"] = "o";
    hexs["70"] = "p";
    hexs["71"] = "q";
    hexs["72"] = "r";
    hexs["73"] = "s";
    hexs["74"] = "t";
    hexs["75"] = "u";
    hexs["76"] = "v";
    hexs["77"] = "w";
    hexs["78"] = "x";
    hexs["79"] = "y";
    hexs["7a"] = "z";
    hexs["30"] = "0";
    hexs["31"] = "1";
    hexs["32"] = "2";
    hexs["33"] = "3";
    hexs["34"] = "4";
    hexs["35"] = "5";
    hexs["36"] = "6";
    hexs["37"] = "7";
    hexs["38"] = "8";
    hexs["39"] = "9";
    hexs["20"] = " ";
    hexs["21"] = "!";
    hexs["2c"] = ",";
    hexs["00"] = " ";
    hexs["3c"] = "<";
    hexs["3e"] = ">";
    hexs["5b"] = "[";
    hexs["5d"] = "]";
    hexs["3f"] = "?";
    hexs["22"] = "\"";
    hexs["27"] = "'";
    hexs["2e"] = ".";
    hexs["5c"] = "\n";

    word = hexs[hex];

    return word;
}

string strspli( string a ) {
    a = a.insert( 2, ":" ); 
    return a;
}

string strpri( string a ) {
    int size = a.size();
    string data, word;
    word = a;
    vector <string> vec;
    for ( int i = 0; i < size/2; i++ ) {
        vec.resize(i+1);
        word = strspli( word );
        data += hextostring( split( word, ":" )[0] );
        word = split( word, ":" )[1];
    }
    return data;
}

vector<string> remove(vector<string> vector, int index) {
    vector.erase(vector.begin() + index);
    return vector;
}

bool keyfind(map<string, string> m, string v) {
    return m.find(v) != m.end(); // findを使ったいつものやつ
}

bool intkeyfind(map<string, int> m, string v) {
    return m.find(v) != m.end(); // findを使ったいつものやつ
}

int vecindex( vector< string >list, string word ) {
    for ( int i = 0; i < list.size(); i++ ) {
        if ( word == list[i] ) {
            return i;
        }
    }
    return 0;
}

map <string, int> calcproc( map<string, int>intvall, string mark, string mode, string vdata ) {
    
    if ( vdata.find( "00" ) != string::npos ) {
        vdata = regex_replace( vdata, regex( "00" ), "" );
    }
    if ( vdata.find( "20" ) != string::npos ) {
        vdata = regex_replace( vdata, regex( "20" ), "" );
    }

    if ( mark == "73756" ) { mark = "737562"; }
    string a = strpri ( split( split( vdata, "2c" )[0], mark )[1] ); 
    string b = strpri ( split( vdata, "2c" )[1] ) ;
    string ans = strpri( split( split( vdata, "2c" )[0], mark )[1] ) ;

    // TODO : 内容確認用 : cout << a << ":" << b << ":" << ans << ":" << strpri( vdata ) << ":" << vdata << endl;

    if ( a.find( " " ) != string::npos ) { a = regex_replace( a, regex( " " ), "" ); }
    
    if ( intkeyfind( intvall, a ) ) {
;
    
        if ( mark == "616464" ) { intvall[ans] = intvall[a] + atoi( b.c_str() ); }
    
        if ( mark == "737562" ) { intvall[ans] = intvall[a] - atoi( b.c_str() ); }
    
        if ( mark == "646976" ) { intvall[ans] = intvall[a] * atoi( b.c_str() ); }
    
        if ( mark == "6d756c" ) { intvall[ans] = intvall[a] / atoi( b.c_str() ); }
    }
    return intvall;
}

double fib(int n) {
    double v;
    if (n <= 0) {
        v = 0.0;
    }
    else if (n == 1) {
        v = 1.0;
    }
    else {
        v = fib(n - 2) + fib(n - 1);
    }
    return v;
}

bool isParam (string line)
{
    if (isdigit(atoi(line.c_str())))
        return true;

    return false;
}

string lblock( string word ) {
    if ( word.substr( 0, 1 ) == "L" and isParam(split( word, "L")[1]) ) {
        print(word);
    }
    return word;
}
