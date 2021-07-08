from typing import ValuesView
import ply.yacc as yacc
# -*- coding: utf-8 -*-
from lex import tokens
import sys

"""
def p_letlist(p):
    
    letlist : let
            | letlist let
    if (len(p) == 2):
        p[0] = (p[1])
    elif (len(p) == 4):
        l = p[1]
        l.append(p[3])
        p[0] = l
"""

def p_sents(p):
    """
    sents : sent
          | sents sent
    """
    if (len(p) > 2):
        l = list([p[1]])
        l.append([p[2]])
        p[0] = l
    else:
        p[0] = [p[1]]
    
def p_param(p):
    '''
        param : TYPE ID
              | TYPE
    '''
    if (len(p) == 2):
        p[0] = ('PARAM',p[1])
    elif (len(p) == 3):   
        p[0] = ('PARAM',p[1],p[2])

def p_paramlist(p):
    """
    paramlist : param
              | paramlist CONMA param
    """
    if (len(p) == 2):
        p[0] = p[1]
    else:
        p[0] = p[1], p[3]

def p_sent_shiki(p):
    """
    shiki : ID
          | STR
          | NUMBER
    """
    p[0] = ("shiki", p[1])

def p_shiki_plusplus(p):
    """
    shiki : shiki PLUS PLUS
    """
    p[0] = ("add", p[1], p[2], "1")

def p_shiki_conma(p):
    """
    shiki : shiki CONMA shiki
    """
    p[0] = (p[1], p[3])

def p_shiki_calc(p):
    """
    shiki : shiki PLUS shiki
          | shiki MINUS shiki
          | shiki KAKERU shiki
          | shiki WARU shiki
    """
    if p[2] == "+": 
        p[0] = ("add", p[1], p[2], p[3])
    elif p[2] == "-":
        p[0] = ("sub", p[1], p[2], p[3])
    elif p[2] == "/":
        p[0] = ("mul", p[1], p[2], p[3])
    elif p[2] == "*":
        p[0] = ("div", p[1], p[2], p[3])

def p_compa(p):
    """
    compa : shiki EQOLS shiki
          | shiki DAINARI shiki
          | shiki SYOUNARI shiki
    """
    p[0] = ("compa", p[1], p[2], p[3] ) 

def p_sent_defunc(p):
    """
    sent : TYPE ID KAKKO paramlist KOKKA COLON sents
    """
    p[0] = ("defunc", p[1], p[2], p[4], p[7])

def p_sent_if(p):
    """
    sent : IF compa COLON sents END SEMI
    """
    p[0] =("IF", p[2], p[4])

def p_sent_while(p):
    """
    sent : WHILE compa COLON sents END SEMI
    """
    p[0] = ( "WHILE", p[2], p[4] )
def p_sent_def(p):
    """
    sent : shiki EQOL shiki LKAKKO TYPE LKOKKA SEMI
    """
    p[0] = ("defvall", p[1], p[3], p[5])

def p_sent_put(p):
    """
    sent : PUT KAKKO shiki KOKKA SEMI
    """
    p[0] = ( "put", p[3])

def p_sent_call(p):
    """
    sent : ID KAKKO shiki KOKKA SEMI
    """
    p[0] = ("CALL", p[1], p[3])

def p_error(p):
    print ('SyntaxErr : すみません、 %sに当てはまる文法作るのやめてもらっていいすか？' % p)

parser = yacc.yacc(debug=0, write_tables=0)
datalis = []
nowvall = ""
nowvall2 = ""
now = ""
Lcount = 0
Jcount = 0
fincount = 0
spc = 0
idbool = 1
Ldict = {}
valldict = {}

class Walker:
    def __init__(self):
        pass

    def append( self, data ):
        global datalis
        datalis.append(data+"\n")
    
    def write_code( self ):
        global datalis
        with open( sys.argv[1]+"s", "a" ) as wfile:
            wfile.truncate(0) 
            for item in datalis:
                wfile.write(item)

    def if_compa( self, ast ):
        global nowvall
        if ast[2] == ">":
            return "jle"
        elif ast[2] == "<":
            return "jri"
        else:
            return "je"
    
    def fin( self, item ):
            global Ldict
            i = 0
            try:
                self.append("01L"+str(item))
                self.steps(Ldict["L"+str(item)])
                if  Ldict["L"+str(item)][0] == "IF":
                    self.fin(item+1)
            except:
                pass

    def steps( self, ast ):
        global nowvall, Lcount, Ldict, Jcount, fincount, spc, idbool, valldict, nowvall2, now
        
        appendb = True

        if ast[0] == "defunc":
            poplist = []
            popcount = 0
            spc = 0
            try:
                if ast[3][0] != "void":
                    if type(ast[3]) == str:
                        for item in ast[3]:
                            poplist.append(item[1]+":"+item[2])
                    else:
                        poplist.append(ast[3][1]+":"+ast[3][2])
                else:
                    arg = "void"
            except:
                if ast[3][0] == "PARAM":
                    appendb = False
                else:
                    for item in ast[3]:
                        poplist.append(item[1]+ ":"+ item[2])
            self.append("01"+ast[2])
            for item in poplist:
                if appendb == True:
                    self.append(";04"+item.split(":")[0])
                    self.steps(["shiki", item.split(":")[1]])
                    spc+=1
                self.append(";06"+nowvall+" "+str(popcount))
                popcount+=1
            self.steps(ast[4])
        
        elif ast[0] == "CALL":
            idbool = 3
            data = ""
            if type(ast[2][0]) == tuple:
                for item in ast[2]:
                    self.steps(item)
                    data += nowvall+" "
            else:
                self.steps(ast[2])
                data = nowvall
            self.append(";05"+ast[1]+"["+data+"]")

        elif ast[0] == "IF":
            data = []
            self.steps(ast[1])
            for item in ast[2]:
                data += item
            Ldict["L"+str(Lcount-1)] = data
            fincount+=1
            
        elif ast[0] == "WHILE":
            data = []
            self.steps(ast[1])
            for item in ast[2]:
                data += item
            Ldict["L"+str(Lcount-1)] = data

        elif ast[0] == "defvall":
            idbool = 1
            self.append(";04"+ast[3])
            spc+=1
            self.steps(ast[1])
            vallname = nowvall
            valldict[nowvall2] = vallname
            idbool = 2
            self.steps(ast[2])
            if now == "":
                self.append(";02"+vallname+" "+nowvall)
            else:
                self.append(now+vallname+" "+nowvall)

        elif ast[0] == "add" or ast[0] == "sub" or ast[0] == "div" or ast[0] == "mul":
            #now = ";21"
            if ast[0] == "add":
                symbol = ";21"
            if ast[0] == "sub":
                symbol = ";22"
            if ast[0] == "div":
                symbol = ";23"
            if ast[0] == "mul":
                symbol = ";24"
            
            try:
                self.steps(ast[1])
                l = int(nowvall)
                self.steps(ast[3])
                r = int(nowvall)
            except:
                    self.steps(ast[1])
                    try:
                        l = valldict[nowvall]
                        if type(ast[3]) == tuple:
                            self.steps(ast[3])
                        else:
                            nowvall = ast[3]
                        r = nowvall
                        if r in valldict:
                            self.append(symbol+l+" "+valldict[nowvall])
                        else:
                            self.append(symbol+l+" "+valldict[nowvall])
                        nowvall = l
                        
                    except:
                        try:
                            l = nowvall
                            self.steps(ast[3])
                            r = valldict[nowvall]
                            self.append(";02"+r+" "+l)
                            nowvall = r
                        except:
                            self.steps(ast[1])
                            r = ast[3]
                            nowvall3 = "rax"+str(spc)
                            self.append(";02"+nowvall3+" "+r)
                            self.append(";21"+valldict[nowvall]+" "+nowvall3)
                            nowvall = valldict[nowvall]

        elif ast[0] == "put":
            idbool = 1
            self.steps(ast[1])
            if "\""in nowvall :
                self.append(";11"+nowvall)
            else:
                nowvall = valldict[nowvall2]
                self.append(";11"+nowvall)
                
        elif ast[0] == "shiki":
            self.steps(ast[1])
            if "\"" in ast[1]:
                nowvall = ast[1]
            elif idbool == 1:
                if ast[1] in valldict:
                    nowvall = valldict[ast[1]]
                else:
                    nowvall = "rax"+str(spc)
                    nowvall2 = ast[1]
                    valldict[nowvall2] = nowvall
            elif idbool == 3:
                nowvall = valldict[ast[1]]
            else:
                nowvall = ast[1]

        elif ast[0] == "compa":
            data = self.if_compa(ast)
            self.steps(ast[1])
            left = nowvall
            self.steps(ast[3])
            right = nowvall
            self.append(data+" "+left+" "+right+" L"+str(Lcount))
            Lcount+=1

        elif type(ast[0]) == list or type(ast[0]) == tuple:
            for item in ast:
                self.steps(item) 


class Main:
    def __init__(self, data):
        self.data = data
    
    def main( self ):
        global Jcount, fincount
        self.data = self.data.replace("\n", "").split("fn ")
        for item in self.data:
            if item != None and item != "":
                result = parser.parse( item )
                if result != None and result != "":
                    walker = Walker()
                    walker.steps(result)
        for item in range(len(Ldict)+1):
            walker.fin(item)
            walker.write_code()
        
if __name__ == '__main__':
    data = open( sys.argv[1], "r", encoding="utf_8" ).read()
    Main(data).main()
