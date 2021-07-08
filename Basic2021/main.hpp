/* 2/5~ */
#pragma once
#include <fstream>
#include <array>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <utility>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>
//----------------------

using namespace std;

//----------------------

void run ( string filename );
vector <string> split( string str, string separator ) ; 
map <string, string> todict ( string sent, map <string, string> dict ) ;
void print ( string word ) ;
void printint ( int word) ;
vector<string> import( string funcname, string filename ) ;
string replace( string data, string replace_word ) ;
vector<string> remove(vector<string> vector, int index) ;
bool keyfind(map<string, string> m, string v) ;
string calc( string data, map<string, string> valls, string mark ) ;
int ifj( string data, map<string, string> valls, string mark ) ;
void VM ( map<string, string> func, string funcname, int loopj ) ;
vector<string> inc ( string callfunc );
vector<int> hex(const char *string) ;
unsigned int binToUInt(const string &str) ;
bool intj ( string hoge )  ;
bool intkeyfind(map<string, int> m, string v) ;
string hextostring( string hex ) ;
string strspli( string a ) ;
string strpri( string a ) ;
int intifj( string data, map<string, int> valls, string mark ) ;
map <string, int> calcproc( map<string, int>intvall, string mark, string mode, string vdata ) ;
vector<string> include_pack( string file, string name ) ;
string edit( string data, map<string, string> funcs, string maindata, int whilen, map<string, int>intvall ) ;
string setdata ( string data, map<string, string> funcs, int whilen ) ;
int vecindex( vector< string >list, string word ) ;
double fib(int n) ;
string lblock( string word ) ;
bool isParam (string line) ;
