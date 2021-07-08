import ply.lex as lex

tokens = (
    "STR",
    "NUMBER",
    "ID",
    "IF",
    "ELSE",
    "ELIF",
    "WHILE",
    "PLUS",
    "MINUS",
    "KAKERU",
    "WARU",
    "EQOL",
    "EQOLS",
    "DAINARI",
    "SYOUNARI",
    "CONMA",
    "PIRIOD",
    "KAKKO",
    "KOKKA",
    "LKAKKO",
    "LKOKKA",
    "TYPE",
    "PUT",
    "COLON",
    "SEMI",
    "END",
)

t_CONMA = r"\,"
t_PIRIOD = r"\."
t_PLUS = r"\+"
t_MINUS = r"\-"
t_KAKERU = r"\*"
t_WARU = r"\/"
t_EQOL = r"\="
t_EQOLS = r"\=\="
t_KAKKO = r"\("
t_KOKKA = r"\)"
t_NUMBER = r"\d+"
t_LKAKKO = r"\["
t_LKOKKA = r"\]"
t_ignore = r' \t'
t_COLON = r"\:"
t_SEMI = r"\;"
t_DAINARI = r"\>"
t_SYOUNARI = r"\<"

def t_STR (t):
    r"[\"'][_<>\.,\*+/!?a-zA-Z0-9\"' ]*"
    return t

def t_ID (t):
    r"[a-zA-Z@][a-zA-Z0-9_]*"
    if t.value == "int" or t.value == "str" or t.value == "float" or t.value == "void":
        t.type = "TYPE"
    elif t.value == "put":
        t.type = "PUT"
    elif t.value == "end":
        t.type = "END"
    elif t.value == "if":
        t.type = "IF"
    elif t.value == "else":
        t.type = "ELSE"
    elif t.value == "elif":
        t.type = "ELIF"
    elif t.value == "while":
        t.type = "WHILE"
    else:
        t.type == "ID"
    return t

def t_error(t):
    print("LexErr：%s, それ、あなたの感想ですよね？" % t.value[0])
    t.lexer.skip(1)

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

lexer = lex.lex(debug=0)