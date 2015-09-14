#include <iostream>
#include <fstream>
#include <deque>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <wchar.h>


// Accumulator
std::deque<char> acc;

// Token enum
typedef enum {
    // Tokens
    _ID, _NUM, _STR, _PROG, _CONST, _INT, _REAL, _STRING, _GOTO, _WHILE,
    _IF, _THEN, _ELSE, _READ, _WRITE, _TRUE, _FALSE, _BOOL, _DO, _CHAR,
    _BEGIN, _END, _VAR, _LABEL, _CONC, _LEN, _REPL, _SUBS, _SRCH, _FUNC,
    _OPER, _NEWW, _L, _N, _PLUS, _MINUS, _MULT, _DIV, _NOT, _AND, _OR,
    _REL, _EQ, _DOT, _OBRACK, _CBRACK, _SEMCOL, _COLUM, _COMMA,
    _RC, _CC, _EPS,
    // Non terminals
    PROG, VARS, VAR, CONSTS, CONST, LABELS, TYPE, ID, L, N, AEXP, TERM,
    MULT, SIGN, LEXP, LTERM, LMULT, REL, C, DEC, NN, RC, DC, EXP, CC,
    BC, SC, NLN, OP, UMOP, AOP, GOP, WOP, MSG, ROP, COP, IFOP, FOROP,
    LENOP, CONOP, REPOP, SEOP, SUBOP, FUNOP, HFUN, NEWOP, IFAOP, OPOP,
    OVAR1, OVAR2, OVAR, OOP, FUNCS, CLV, OPROG, OCOP, RVAR, RID, RCONST,
    RLTERM, RECUROP, ALEXP, RMSG, ZOMOP, IDSC, IDNN, OEAOP,
    // Special fucking hrenoten'
    _C, _HASH
} token_t;

std::string pTT(token_t t) {if(t==_ID)return std::string("_ID");else if(t==_NUM)return std::string("_NUM");else if(t==_STR)return std::string("_STR");else if(t==_PROG)return std::string("_PROG");else if(t==_CONST)return std::string("_CONST");else if(t==_INT)return std::string("_INT");else if(t==_REAL)return std::string("_REAL");else if(t==_STRING)return std::string("_STRING");else if(t==_GOTO)return std::string("_GOTO");else if(t==_WHILE)return std::string("_WHILE");else if(t==_IF)return std::string("_IF");else if(t==_THEN)return std::string("_THEN");else if(t==_ELSE)return std::string("_ELSE");else if(t==_READ)return std::string("_READ");else if(t==_WRITE)return std::string("_WRITE");else if(t==_TRUE)return std::string("_TRUE");else if(t==_FALSE)return std::string("_FALSE");else if(t==_BOOL)return std::string("_BOOL");else if(t==_DO)return std::string("_DO");else if(t==_CHAR)return std::string("_CHAR");else if(t==_BEGIN)return std::string("_BEGIN");else if(t==_END)return std::string("_END");else if(t==_VAR)return std::string("_VAR");else if(t==_LABEL)return std::string("_LABEL");else if(t==_CONC)return std::string("_CONC");else if(t==_LEN)return std::string("_LEN");else if(t==_REPL)return std::string("_REPL");else if(t==_SUBS)return std::string("_SUBS");else if(t==_SRCH)return std::string("_SRCH");else if(t==_FUNC)return std::string("_FUNC");else if(t==_OPER)return std::string("_OPER");else if(t==_NEWW)return std::string("_NEWW");else if(t==_L)return std::string("_L");else if(t==_N)return std::string("_N");else if(t==_PLUS)return std::string("_PLUS");else if(t==_MINUS)return std::string("_MINUS");else if(t==_MULT)return std::string("_MULT");else if(t==_DIV)return std::string("_DIV");else if(t==_NOT)return std::string("_NOT");else if(t==_AND)return std::string("_AND");else if(t==_OR)return std::string("_OR");else if(t==_REL)return std::string("_REL");else if(t==_EQ)return std::string("_EQ");else if(t==_DOT)return std::string("_DOT");else if(t==_OBRACK)return std::string("_OBRACK");else if(t==_CBRACK)return std::string("_CBRACK");else if(t==_SEMCOL)return std::string("_SEMCOL");else if(t==_COLUM)return std::string("_COLUM");else if(t==_COMMA)return std::string("_COMMA");else if(t==_RC)return std::string("_RC");else if(t==_CC)return std::string("_CC");else if(t==_EPS)return std::string("_EPS");else if(t==PROG)return std::string("PROG");else if(t==VARS)return std::string("VARS");else if(t==VAR)return std::string("VAR");else if(t==CONSTS)return std::string("CONSTS");else if(t==CONST)return std::string("CONST");else if(t==LABELS)return std::string("LABELS");else if(t==TYPE)return std::string("TYPE");else if(t==ID)return std::string("ID");else if(t==L)return std::string("L");else if(t==N)return std::string("N");else if(t==AEXP)return std::string("AEXP");else if(t==TERM)return std::string("TERM");else if(t==MULT)return std::string("MULT");else if(t==SIGN)return std::string("SIGN");else if(t==LEXP)return std::string("LEXP");else if(t==LTERM)return std::string("LTERM");else if(t==LMULT)return std::string("LMULT");else if(t==REL)return std::string("REL");else if(t==C)return std::string("C");else if(t==DEC)return std::string("DEC");else if(t==NN)return std::string("NN");else if(t==RC)return std::string("RC");else if(t==DC)return std::string("DC");else if(t==EXP)return std::string("EXP");else if(t==CC)return std::string("CC");else if(t==BC)return std::string("BC");else if(t==SC)return std::string("SC");else if(t==NLN)return std::string("NLN");else if(t==OP)return std::string("OP");else if(t==UMOP)return std::string("UMOP");else if(t==AOP)return std::string("AOP");else if(t==GOP)return std::string("GOP");else if(t==WOP)return std::string("WOP");else if(t==MSG)return std::string("MSG");else if(t==ROP)return std::string("ROP");else if(t==COP)return std::string("COP");else if(t==IFOP)return std::string("IFOP");else if(t==FOROP)return std::string("FOROP");else if(t==LENOP)return std::string("LENOP");else if(t==CONOP)return std::string("CONOP");else if(t==REPOP)return std::string("REPOP");else if(t==SEOP)return std::string("SEOP");else if(t==SUBOP)return std::string("SUBOP");else if(t==FUNOP)return std::string("FUNOP");else if(t==HFUN)return std::string("HFUN");else if(t==NEWOP)return std::string("NEWOP");else if(t==IFAOP)return std::string("IFAOP");else if(t==OPOP)return std::string("OPOP");else if(t==OVAR1)return std::string("OVAR1");else if(t==OVAR2)return std::string("OVAR2");else if(t==OVAR)return std::string("OVAR");else if(t==OOP)return std::string("OOP");else if(t==FUNCS)return std::string("FUNCS");else if(t==CLV)return std::string("CLV");else if(t==OPROG)return std::string("OPROG");else if(t==OCOP)return std::string("OCOP");else if(t==RVAR)return std::string("RVAR");else if(t==RID)return std::string("RID");else if(t==RCONST)return std::string("RCONST");else if(t==RLTERM)return std::string("RLTERM");else if(t==RECUROP)return std::string("RECUROP");else if(t==ALEXP)return std::string("ALEXP");else if(t==RMSG)return std::string("RMSG");else if(t==ZOMOP)return std::string("ZOMOP");else if(t==IDSC)return std::string("IDSC");else if(t==IDNN)return std::string("IDNN");else if(t==OEAOP)return std::string("OEAOP");else if(t==_C)return std::string("_C");else if(t==_HASH)return std::string("_HASH");}


void pT(token_t t) {if(t==_ID)std::cout << "_ID";else if(t==_NUM)std::cout << "_NUM";else if(t==_STR)std::cout << "_STR";else if(t==_PROG)std::cout << "_PROG";else if(t==_CONST)std::cout << "_CONST";else if(t==_INT)std::cout << "_INT";else if(t==_REAL)std::cout << "_REAL";else if(t==_STRING)std::cout << "_STRING";else if(t==_GOTO)std::cout << "_GOTO";else if(t==_WHILE)std::cout << "_WHILE";else if(t==_IF)std::cout << "_IF";else if(t==_THEN)std::cout << "_THEN";else if(t==_ELSE)std::cout << "_ELSE";else if(t==_READ)std::cout << "_READ";else if(t==_WRITE)std::cout << "_WRITE";else if(t==_TRUE)std::cout << "_TRUE";else if(t==_FALSE)std::cout << "_FALSE";else if(t==_BOOL)std::cout << "_BOOL";else if(t==_DO)std::cout << "_DO";else if(t==_CHAR)std::cout << "_CHAR";else if(t==_BEGIN)std::cout << "_BEGIN";else if(t==_END)std::cout << "_END";else if(t==_VAR)std::cout << "_VAR";else if(t==_LABEL)std::cout << "_LABEL";else if(t==_CONC)std::cout << "_CONC";else if(t==_LEN)std::cout << "_LEN";else if(t==_REPL)std::cout << "_REPL";else if(t==_SUBS)std::cout << "_SUBS";else if(t==_SRCH)std::cout << "_SRCH";else if(t==_FUNC)std::cout << "_FUNC";else if(t==_OPER)std::cout << "_OPER";else if(t==_NEWW)std::cout << "_NEWW";else if(t==_L)std::cout << "_L";else if(t==_N)std::cout << "_N";else if(t==_PLUS)std::cout << "_PLUS";else if(t==_MINUS)std::cout << "_MINUS";else if(t==_MULT)std::cout << "_MULT";else if(t==_DIV)std::cout << "_DIV";else if(t==_NOT)std::cout << "_NOT";else if(t==_AND)std::cout << "_AND";else if(t==_OR)std::cout << "_OR";else if(t==_REL)std::cout << "_REL";else if(t==_EQ)std::cout << "_EQ";else if(t==_DOT)std::cout << "_DOT";else if(t==_OBRACK)std::cout << "_OBRACK";else if(t==_CBRACK)std::cout << "_CBRACK";else if(t==_SEMCOL)std::cout << "_SEMCOL";else if(t==_COLUM)std::cout << "_COLUM";else if(t==_COMMA)std::cout << "_COMMA";else if(t==_RC)std::cout << "_RC";else if(t==_CC)std::cout << "_CC";else if(t==_EPS)std::cout << "_EPS";else if(t==PROG)std::cout << "PROG";else if(t==VARS)std::cout << "VARS";else if(t==VAR)std::cout << "VAR";else if(t==CONSTS)std::cout << "CONSTS";else if(t==CONST)std::cout << "CONST";else if(t==LABELS)std::cout << "LABELS";else if(t==TYPE)std::cout << "TYPE";else if(t==ID)std::cout << "ID";else if(t==L)std::cout << "L";else if(t==N)std::cout << "N";else if(t==AEXP)std::cout << "AEXP";else if(t==TERM)std::cout << "TERM";else if(t==MULT)std::cout << "MULT";else if(t==SIGN)std::cout << "SIGN";else if(t==LEXP)std::cout << "LEXP";else if(t==LTERM)std::cout << "LTERM";else if(t==LMULT)std::cout << "LMULT";else if(t==REL)std::cout << "REL";else if(t==C)std::cout << "C";else if(t==DEC)std::cout << "DEC";else if(t==NN)std::cout << "NN";else if(t==RC)std::cout << "RC";else if(t==DC)std::cout << "DC";else if(t==EXP)std::cout << "EXP";else if(t==CC)std::cout << "CC";else if(t==BC)std::cout << "BC";else if(t==SC)std::cout << "SC";else if(t==NLN)std::cout << "NLN";else if(t==OP)std::cout << "OP";else if(t==UMOP)std::cout << "UMOP";else if(t==AOP)std::cout << "AOP";else if(t==GOP)std::cout << "GOP";else if(t==WOP)std::cout << "WOP";else if(t==MSG)std::cout << "MSG";else if(t==ROP)std::cout << "ROP";else if(t==COP)std::cout << "COP";else if(t==IFOP)std::cout << "IFOP";else if(t==FOROP)std::cout << "FOROP";else if(t==LENOP)std::cout << "LENOP";else if(t==CONOP)std::cout << "CONOP";else if(t==REPOP)std::cout << "REPOP";else if(t==SEOP)std::cout << "SEOP";else if(t==SUBOP)std::cout << "SUBOP";else if(t==FUNOP)std::cout << "FUNOP";else if(t==HFUN)std::cout << "HFUN";else if(t==NEWOP)std::cout << "NEWOP";else if(t==IFAOP)std::cout << "IFAOP";else if(t==OPOP)std::cout << "OPOP";else if(t==OVAR1)std::cout << "OVAR1";else if(t==OVAR2)std::cout << "OVAR2";else if(t==OVAR)std::cout << "OVAR";else if(t==OOP)std::cout << "OOP";else if(t==FUNCS)std::cout << "FUNCS";else if(t==CLV)std::cout << "CLV";else if(t==OPROG)std::cout << "OPROG";else if(t==OCOP)std::cout << "OCOP";else if(t==RVAR)std::cout << "RVAR";else if(t==RID)std::cout << "RID";else if(t==RCONST)std::cout << "RCONST";else if(t==RLTERM)std::cout << "RLTERM";else if(t==RECUROP)std::cout << "RECUROP";else if(t==ALEXP)std::cout << "ALEXP";else if(t==RMSG)std::cout << "RMSG";else if(t==ZOMOP)std::cout << "ZOMOP";else if(t==IDSC)std::cout << "IDSC";else if(t==IDNN)std::cout << "IDNN";else if(t==OEAOP)std::cout << "OEAOP";else if(t==_C)std::cout << "_C";else if(t==_HASH)std::cout << "_HASH";}

// Transition rules
typedef enum {
    _S, _R, _A, _E
} trans_t;

struct TransRule {
    std::vector<token_t> inStack;
    token_t input;
    trans_t rule;
};

struct FoldRule {
    std::vector<token_t> inStack;
    int ruleNum;
};

class Symbol;

class OutFoldRule {
public:
    OutFoldRule(int g, int r) : gNum(g), rNum(r) {};
    int gNum;
    int rNum;
    std::vector<Symbol> symbols;
};

std::vector<OutFoldRule> outFoldRules;

class Gramm {
public:
    Gramm(int id);
    ~Gramm();
    // Gramm id
    int id;
	// Start non terminal
	token_t startNonTerm;
    // List of non terminals
    std::vector<token_t> nonTerms;
    // List of terminals
    std::set<token_t> terms;
    // Rules
    std::vector<token_t>* rules;
    // Rules count
    int rulesCount;
    // Transition rules
    std::vector<struct TransRule> transRules;
    // Fold rules
    std::vector<struct FoldRule> foldRules;
};

Gramm::Gramm(int id) {
    this->id = id;
    rules = NULL;
    rulesCount = 0;
}

Gramm::~Gramm() {
    // if (rules) delete rules;
    rulesCount = 0;
}

std::vector<Gramm> grams;

void initGramm0() {
    Gramm g(0);
    token_t nonTerms[] = {CLV, COP, ID, OCOP, OPROG, PROG};
    token_t Terms[] = {_DOT, _SEMCOL, _PROG};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 6);
    g.terms.insert(Terms, Terms + 3);
	g.startNonTerm = PROG;
    g.rulesCount = 5;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {PROG, _PROG, ID, _SEMCOL, OPROG};
    token_t r1t[] = {PROG, OPROG};
    token_t r2t[] = {OPROG, OCOP};
    token_t r3t[] = {OPROG, CLV, _SEMCOL, OCOP};
    token_t r4t[] = {OCOP, COP, _DOT};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_PROG); fr.inStack.push_back(PROG); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(PROG); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(PROG); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(PROG); fr.ruleNum = 3; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(PROG); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(PROG); fr.ruleNum = 3; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(PROG); fr.inStack.push_back(_DOT); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(PROG); fr.inStack.push_back(_DOT); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _DOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _PROG; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _DOT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _PROG; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_PROG); tr.inStack.push_back(_C); tr.input = _DOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PROG); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PROG); tr.inStack.push_back(_C); tr.input = _PROG; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PROG); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _DOT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _PROG; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(PROG); tr.input = _DOT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(PROG); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(PROG); tr.input = _PROG; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(PROG); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm1() {
    Gramm g(1);
    token_t nonTerms[] = {ID, RID, RVAR, TYPE, VAR, VARS};
    token_t Terms[] = {_COMMA, _SEMCOL, _COLUM, _VAR};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 6);
    g.terms.insert(Terms, Terms + 4);
	g.startNonTerm = VARS;
    g.rulesCount = 6;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {VARS, _VAR, RVAR};
    token_t r1t[] = {RVAR, VAR, _SEMCOL, RVAR};
    token_t r2t[] = {RVAR, VAR};
    token_t r3t[] = {VAR, RID, _COLUM, TYPE};
    token_t r4t[] = {RID, ID, _COMMA, RID};
    token_t r5t[] = {RID, ID};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    std::vector<token_t> r5 (r5t, r5t + sizeof(r5t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    g.rules[5] = r5;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_VAR); fr.inStack.push_back(VARS); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(VARS); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(VARS); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_VAR); fr.inStack.push_back(VARS); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(VARS); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(VARS); fr.inStack.push_back(_COLUM); fr.inStack.push_back(VARS); fr.ruleNum = 3; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_VAR); fr.inStack.push_back(VARS); fr.inStack.push_back(_COLUM); fr.inStack.push_back(VARS); fr.ruleNum = 3; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_COMMA); fr.inStack.push_back(VARS); fr.inStack.push_back(_COMMA); fr.inStack.push_back(VARS); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(VARS); fr.inStack.push_back(_COMMA); fr.inStack.push_back(VARS); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_VAR); fr.inStack.push_back(VARS); fr.inStack.push_back(_COMMA); fr.inStack.push_back(VARS); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _VAR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _VAR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _VAR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_VAR); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_VAR); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_VAR); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_VAR); tr.inStack.push_back(_C); tr.input = _VAR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_VAR); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _VAR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(VARS); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(VARS); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(VARS); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(VARS); tr.input = _VAR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(VARS); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm2() {
    Gramm g(2);
    token_t nonTerms[] = {C, CONST, CONSTS, ID, RCONST};
    token_t Terms[] = {_SEMCOL, _REL, _CONST};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 5);
    g.terms.insert(Terms, Terms + 3);
	g.startNonTerm = CONSTS;
    g.rulesCount = 5;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {CONSTS, _CONST, CONST, _SEMCOL, RCONST};
    token_t r1t[] = {CONSTS, _CONST, CONST};
    token_t r2t[] = {RCONST, CONST, _SEMCOL, RCONST};
    token_t r3t[] = {RCONST, CONST};
    token_t r4t[] = {CONST, ID, _REL, C};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_CONST); fr.inStack.push_back(CONSTS); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(CONSTS); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_CONST); fr.inStack.push_back(CONSTS); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(CONSTS); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(CONSTS); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(CONSTS); fr.inStack.push_back(_REL); fr.inStack.push_back(CONSTS); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_CONST); fr.inStack.push_back(CONSTS); fr.inStack.push_back(_REL); fr.inStack.push_back(CONSTS); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _CONST; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _CONST; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CONST); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CONST); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CONST); tr.inStack.push_back(_C); tr.input = _CONST; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CONST); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CONST; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(CONSTS); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(CONSTS); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(CONSTS); tr.input = _CONST; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(CONSTS); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm3() {
    Gramm g(3);
    token_t nonTerms[] = {LABELS, RID, ID};
    token_t Terms[] = {_LABEL, _COMMA};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 3);
    g.terms.insert(Terms, Terms + 2);
	g.startNonTerm = LABELS;
    g.rulesCount = 3;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {LABELS, _LABEL, RID};
    token_t r1t[] = {RID, ID, _COMMA, RID};
    token_t r2t[] = {RID, ID};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_LABEL); fr.inStack.push_back(LABELS); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_COMMA); fr.inStack.push_back(LABELS); fr.inStack.push_back(_COMMA); fr.inStack.push_back(LABELS); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_LABEL); fr.inStack.push_back(LABELS); fr.inStack.push_back(_COMMA); fr.inStack.push_back(LABELS); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _LABEL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_LABEL); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_LABEL); tr.inStack.push_back(_C); tr.input = _LABEL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_LABEL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _LABEL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LABELS); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LABELS); tr.input = _LABEL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LABELS); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm4() {
    Gramm g(4);
    token_t nonTerms[] = {COP, FUNCS, FUNOP, HFUN, ID, OPOP, TYPE, VARS};
    token_t Terms[] = {_COLUM, _SEMCOL, _FUNC};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 8);
    g.terms.insert(Terms, Terms + 3);
	g.startNonTerm = FUNCS;
    g.rulesCount = 5;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {FUNCS, FUNOP};
    token_t r1t[] = {FUNCS, OPOP};
    token_t r2t[] = {FUNOP, HFUN, _SEMCOL, COP};
    token_t r3t[] = {FUNOP, HFUN, _SEMCOL, VARS, _SEMCOL, COP};
    token_t r4t[] = {HFUN, _FUNC, ID, _COLUM, TYPE};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(FUNCS); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(FUNCS); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(FUNCS); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(FUNCS); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(FUNCS); fr.ruleNum = 3; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_FUNC); fr.inStack.push_back(FUNCS); fr.inStack.push_back(_COLUM); fr.inStack.push_back(FUNCS); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _FUNC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _FUNC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_FUNC); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_FUNC); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_FUNC); tr.inStack.push_back(_C); tr.input = _FUNC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_FUNC); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _FUNC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(FUNCS); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(FUNCS); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(FUNCS); tr.input = _FUNC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(FUNCS); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm5() {
    Gramm g(5);
    token_t nonTerms[] = {TYPE};
    token_t Terms[] = {_BOOL, _CHAR, _INT, _REAL, _STRING};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 1);
    g.terms.insert(Terms, Terms + 5);
	g.startNonTerm = TYPE;
    g.rulesCount = 5;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {TYPE, _INT};
    token_t r1t[] = {TYPE, _REAL};
    token_t r2t[] = {TYPE, _BOOL};
    token_t r3t[] = {TYPE, _CHAR};
    token_t r4t[] = {TYPE, _STRING};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_INT); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_REAL); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_BOOL); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_CHAR); fr.ruleNum = 3; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_STRING); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_BOOL); tr.inStack.push_back(_C); tr.input = _BOOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_BOOL); tr.inStack.push_back(_C); tr.input = _CHAR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_BOOL); tr.inStack.push_back(_C); tr.input = _INT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_BOOL); tr.inStack.push_back(_C); tr.input = _REAL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_BOOL); tr.inStack.push_back(_C); tr.input = _STRING; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_BOOL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CHAR); tr.inStack.push_back(_C); tr.input = _BOOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CHAR); tr.inStack.push_back(_C); tr.input = _CHAR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CHAR); tr.inStack.push_back(_C); tr.input = _INT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CHAR); tr.inStack.push_back(_C); tr.input = _REAL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CHAR); tr.inStack.push_back(_C); tr.input = _STRING; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CHAR); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_INT); tr.inStack.push_back(_C); tr.input = _BOOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_INT); tr.inStack.push_back(_C); tr.input = _CHAR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_INT); tr.inStack.push_back(_C); tr.input = _INT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_INT); tr.inStack.push_back(_C); tr.input = _REAL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_INT); tr.inStack.push_back(_C); tr.input = _STRING; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_INT); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_REAL); tr.inStack.push_back(_C); tr.input = _BOOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REAL); tr.inStack.push_back(_C); tr.input = _CHAR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REAL); tr.inStack.push_back(_C); tr.input = _INT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REAL); tr.inStack.push_back(_C); tr.input = _REAL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REAL); tr.inStack.push_back(_C); tr.input = _STRING; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REAL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_STRING); tr.inStack.push_back(_C); tr.input = _BOOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STRING); tr.inStack.push_back(_C); tr.input = _CHAR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STRING); tr.inStack.push_back(_C); tr.input = _INT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STRING); tr.inStack.push_back(_C); tr.input = _REAL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STRING); tr.inStack.push_back(_C); tr.input = _STRING; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STRING); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _BOOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CHAR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _INT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _REAL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _STRING; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(TYPE); tr.input = _BOOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(TYPE); tr.input = _CHAR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(TYPE); tr.input = _INT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(TYPE); tr.input = _REAL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(TYPE); tr.input = _STRING; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(TYPE); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm6() {
    Gramm g(6);
    token_t nonTerms[] = {ID};
    token_t Terms[] = {_ID};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 1);
    g.terms.insert(Terms, Terms + 1);
	g.startNonTerm = ID;
    g.rulesCount = 1;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {ID, _ID};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    
    g.rules[0] = r0;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_ID); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_ID); tr.inStack.push_back(_C); tr.input = _ID; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_ID); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _ID; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(ID); tr.input = _ID; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(ID); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm7() {
    Gramm g(7);
    token_t nonTerms[] = {AEXP, ID, MULT, TERM};
    token_t Terms[] = {_OBRACK, _CBRACK, _MULT, _PLUS, _MINUS, _DIV, _NUM, _RC};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 4);
    g.terms.insert(Terms, Terms + 8);
	g.startNonTerm = AEXP;
    g.rulesCount = 12;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {AEXP, TERM};
    token_t r1t[] = {AEXP, _PLUS, TERM};
    token_t r2t[] = {AEXP, _MINUS, TERM};
    token_t r3t[] = {AEXP, AEXP, _PLUS, TERM};
    token_t r4t[] = {AEXP, AEXP, _MINUS, TERM};
    token_t r5t[] = {TERM, MULT};
    token_t r6t[] = {TERM, TERM, _MULT, MULT};
    token_t r7t[] = {TERM, TERM, _DIV, MULT};
    token_t r8t[] = {MULT, _OBRACK, AEXP, _CBRACK};
    token_t r9t[] = {MULT, ID};
    token_t r10t[] = {MULT, _NUM};
    token_t r11t[] = {MULT, _RC};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    std::vector<token_t> r5 (r5t, r5t + sizeof(r5t) / sizeof(token_t));
    std::vector<token_t> r6 (r6t, r6t + sizeof(r6t) / sizeof(token_t));
    std::vector<token_t> r7 (r7t, r7t + sizeof(r7t) / sizeof(token_t));
    std::vector<token_t> r8 (r8t, r8t + sizeof(r8t) / sizeof(token_t));
    std::vector<token_t> r9 (r9t, r9t + sizeof(r9t) / sizeof(token_t));
    std::vector<token_t> r10 (r10t, r10t + sizeof(r10t) / sizeof(token_t));
    std::vector<token_t> r11 (r11t, r11t + sizeof(r11t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    g.rules[5] = r5;
    g.rules[6] = r6;
    g.rules[7] = r7;
    g.rules[8] = r8;
    g.rules[9] = r9;
    g.rules[10] = r10;
    g.rules[11] = r11;
    
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_PLUS); fr.inStack.push_back(AEXP); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_PLUS); fr.inStack.push_back(AEXP); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_MINUS); fr.inStack.push_back(AEXP); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_MINUS); fr.inStack.push_back(AEXP); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(AEXP); fr.inStack.push_back(_PLUS); fr.inStack.push_back(AEXP); fr.ruleNum = 3; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(AEXP); fr.inStack.push_back(_PLUS); fr.inStack.push_back(AEXP); fr.ruleNum = 3; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(AEXP); fr.inStack.push_back(_MINUS); fr.inStack.push_back(AEXP); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(AEXP); fr.inStack.push_back(_MINUS); fr.inStack.push_back(AEXP); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(AEXP); fr.inStack.push_back(_MULT); fr.inStack.push_back(AEXP); fr.ruleNum = 6; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_PLUS); fr.inStack.push_back(AEXP); fr.inStack.push_back(_MULT); fr.inStack.push_back(AEXP); fr.ruleNum = 6; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_MINUS); fr.inStack.push_back(AEXP); fr.inStack.push_back(_MULT); fr.inStack.push_back(AEXP); fr.ruleNum = 6; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(AEXP); fr.inStack.push_back(_MULT); fr.inStack.push_back(AEXP); fr.ruleNum = 6; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(AEXP); fr.inStack.push_back(_DIV); fr.inStack.push_back(AEXP); fr.ruleNum = 7; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_PLUS); fr.inStack.push_back(AEXP); fr.inStack.push_back(_DIV); fr.inStack.push_back(AEXP); fr.ruleNum = 7; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_MINUS); fr.inStack.push_back(AEXP); fr.inStack.push_back(_DIV); fr.inStack.push_back(AEXP); fr.ruleNum = 7; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(AEXP); fr.inStack.push_back(_DIV); fr.inStack.push_back(AEXP); fr.ruleNum = 7; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(AEXP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 8; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_MULT); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(AEXP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 8; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_PLUS); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(AEXP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 8; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_MINUS); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(AEXP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 8; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_DIV); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(AEXP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 8; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(AEXP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 8; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_NUM); fr.ruleNum = 10; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_MULT); fr.inStack.push_back(_NUM); fr.ruleNum = 10; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_PLUS); fr.inStack.push_back(_NUM); fr.ruleNum = 10; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_MINUS); fr.inStack.push_back(_NUM); fr.ruleNum = 10; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_DIV); fr.inStack.push_back(_NUM); fr.ruleNum = 10; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_NUM); fr.ruleNum = 10; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_RC); fr.ruleNum = 11; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_MULT); fr.inStack.push_back(_RC); fr.ruleNum = 11; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_PLUS); fr.inStack.push_back(_RC); fr.ruleNum = 11; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_MINUS); fr.inStack.push_back(_RC); fr.ruleNum = 11; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_DIV); fr.inStack.push_back(_RC); fr.ruleNum = 11; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_RC); fr.ruleNum = 11; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _MULT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _PLUS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _MINUS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _DIV; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _NUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _RC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(AEXP); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(AEXP); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(AEXP); tr.input = _MULT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(AEXP); tr.input = _PLUS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(AEXP); tr.input = _MINUS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(AEXP); tr.input = _DIV; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(AEXP); tr.input = _NUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(AEXP); tr.input = _RC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(AEXP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm8() {
    Gramm g(8);
    token_t nonTerms[] = {AEXP, ID, LEXP, LMULT, LTERM, RLTERM};
    token_t Terms[] = {_OBRACK, _CBRACK, _AND, _NOT, _OR, _REL, _STR};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 6);
    g.terms.insert(Terms, Terms + 7);
	g.startNonTerm = LEXP;
    g.rulesCount = 11;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {LEXP, LTERM};
    token_t r1t[] = {LEXP, LTERM, _OR, RLTERM};
    token_t r2t[] = {RLTERM, LTERM, _OR, RLTERM};
    token_t r3t[] = {RLTERM, LTERM};
    token_t r4t[] = {LTERM, LTERM, _AND, LMULT};
    token_t r5t[] = {LTERM, LMULT};
    token_t r6t[] = {LMULT, ID};
    token_t r7t[] = {LMULT, AEXP, _REL, AEXP};
    token_t r8t[] = {LMULT, _STR, _REL, _STR};
    token_t r9t[] = {LMULT, _NOT, LMULT};
    token_t r10t[] = {LMULT, _OBRACK, LEXP, _CBRACK};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    std::vector<token_t> r5 (r5t, r5t + sizeof(r5t) / sizeof(token_t));
    std::vector<token_t> r6 (r6t, r6t + sizeof(r6t) / sizeof(token_t));
    std::vector<token_t> r7 (r7t, r7t + sizeof(r7t) / sizeof(token_t));
    std::vector<token_t> r8 (r8t, r8t + sizeof(r8t) / sizeof(token_t));
    std::vector<token_t> r9 (r9t, r9t + sizeof(r9t) / sizeof(token_t));
    std::vector<token_t> r10 (r10t, r10t + sizeof(r10t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    g.rules[5] = r5;
    g.rules[6] = r6;
    g.rules[7] = r7;
    g.rules[8] = r8;
    g.rules[9] = r9;
    g.rules[10] = r10;
    
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(LEXP); fr.inStack.push_back(_OR); fr.inStack.push_back(LEXP); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OR); fr.inStack.push_back(LEXP); fr.inStack.push_back(_OR); fr.inStack.push_back(LEXP); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(LEXP); fr.inStack.push_back(_OR); fr.inStack.push_back(LEXP); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(LEXP); fr.inStack.push_back(_AND); fr.inStack.push_back(LEXP); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OR); fr.inStack.push_back(LEXP); fr.inStack.push_back(_AND); fr.inStack.push_back(LEXP); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(LEXP); fr.inStack.push_back(_AND); fr.inStack.push_back(LEXP); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(LEXP); fr.inStack.push_back(_REL); fr.inStack.push_back(LEXP); fr.ruleNum = 7; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_AND); fr.inStack.push_back(LEXP); fr.inStack.push_back(_REL); fr.inStack.push_back(LEXP); fr.ruleNum = 7; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_NOT); fr.inStack.push_back(LEXP); fr.inStack.push_back(_REL); fr.inStack.push_back(LEXP); fr.ruleNum = 7; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OR); fr.inStack.push_back(LEXP); fr.inStack.push_back(_REL); fr.inStack.push_back(LEXP); fr.ruleNum = 7; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(LEXP); fr.inStack.push_back(_REL); fr.inStack.push_back(LEXP); fr.ruleNum = 7; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_STR); fr.inStack.push_back(_REL); fr.inStack.push_back(_STR); fr.ruleNum = 8; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_AND); fr.inStack.push_back(_STR); fr.inStack.push_back(_REL); fr.inStack.push_back(_STR); fr.ruleNum = 8; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_NOT); fr.inStack.push_back(_STR); fr.inStack.push_back(_REL); fr.inStack.push_back(_STR); fr.ruleNum = 8; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OR); fr.inStack.push_back(_STR); fr.inStack.push_back(_REL); fr.inStack.push_back(_STR); fr.ruleNum = 8; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_STR); fr.inStack.push_back(_REL); fr.inStack.push_back(_STR); fr.ruleNum = 8; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_NOT); fr.inStack.push_back(LEXP); fr.ruleNum = 9; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_AND); fr.inStack.push_back(_NOT); fr.inStack.push_back(LEXP); fr.ruleNum = 9; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_NOT); fr.inStack.push_back(_NOT); fr.inStack.push_back(LEXP); fr.ruleNum = 9; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OR); fr.inStack.push_back(_NOT); fr.inStack.push_back(LEXP); fr.ruleNum = 9; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_NOT); fr.inStack.push_back(LEXP); fr.ruleNum = 9; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(LEXP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 10; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_AND); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(LEXP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 10; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_NOT); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(LEXP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 10; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OR); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(LEXP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 10; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(LEXP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 10; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _AND; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _NOT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _OR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _AND; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _NOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _OR; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_AND); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_AND); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_AND); tr.inStack.push_back(_C); tr.input = _AND; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_AND); tr.inStack.push_back(_C); tr.input = _NOT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_AND); tr.inStack.push_back(_C); tr.input = _OR; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_AND); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_AND); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_AND); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_NOT); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NOT); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NOT); tr.inStack.push_back(_C); tr.input = _AND; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NOT); tr.inStack.push_back(_C); tr.input = _NOT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NOT); tr.inStack.push_back(_C); tr.input = _OR; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NOT); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NOT); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NOT); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_OR); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OR); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OR); tr.inStack.push_back(_C); tr.input = _AND; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OR); tr.inStack.push_back(_C); tr.input = _NOT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OR); tr.inStack.push_back(_C); tr.input = _OR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OR); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OR); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OR); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _AND; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _NOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _OR; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _AND; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _NOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _OR; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _AND; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _NOT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _OR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _REL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LEXP); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LEXP); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LEXP); tr.input = _AND; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LEXP); tr.input = _NOT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LEXP); tr.input = _OR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LEXP); tr.input = _REL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LEXP); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LEXP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);

}
void initGramm9() {
    Gramm g(9);
    token_t nonTerms[] = {BC, C, DEC};
    token_t Terms[] = {_PLUS, _MINUS, _DOT, _CC, _FALSE, _NUM, _RC, _STR, _TRUE};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 3);
    g.terms.insert(Terms, Terms + 9);
	g.startNonTerm = C;
    g.rulesCount = 10;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {C, DEC};
    token_t r1t[] = {C, _CC};
    token_t r2t[] = {C, BC};
    token_t r3t[] = {C, _RC};
    token_t r4t[] = {DEC, _PLUS, _NUM};
    token_t r5t[] = {DEC, _MINUS, _NUM};
    token_t r6t[] = {DEC, _NUM};
    token_t r7t[] = {BC, _TRUE};
    token_t r8t[] = {BC, _FALSE};
    token_t r9t[] = {C, _STR};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    std::vector<token_t> r5 (r5t, r5t + sizeof(r5t) / sizeof(token_t));
    std::vector<token_t> r6 (r6t, r6t + sizeof(r6t) / sizeof(token_t));
    std::vector<token_t> r7 (r7t, r7t + sizeof(r7t) / sizeof(token_t));
    std::vector<token_t> r8 (r8t, r8t + sizeof(r8t) / sizeof(token_t));
    std::vector<token_t> r9 (r9t, r9t + sizeof(r9t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    g.rules[5] = r5;
    g.rules[6] = r6;
    g.rules[7] = r7;
    g.rules[8] = r8;
    g.rules[9] = r9;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_CC); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_RC); fr.ruleNum = 3; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_PLUS); fr.inStack.push_back(_NUM); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_MINUS); fr.inStack.push_back(_NUM); fr.ruleNum = 5; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_NUM); fr.ruleNum = 6; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_TRUE); fr.ruleNum = 7; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_FALSE); fr.ruleNum = 8; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_STR); fr.ruleNum = 9; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _DOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _CC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _FALSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _TRUE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _DOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _CC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _FALSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _TRUE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _DOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _CC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _FALSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _TRUE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DOT); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CC); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CC); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CC); tr.inStack.push_back(_C); tr.input = _DOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CC); tr.inStack.push_back(_C); tr.input = _CC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CC); tr.inStack.push_back(_C); tr.input = _FALSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CC); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CC); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CC); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CC); tr.inStack.push_back(_C); tr.input = _TRUE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CC); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_FALSE); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_FALSE); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_FALSE); tr.inStack.push_back(_C); tr.input = _DOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_FALSE); tr.inStack.push_back(_C); tr.input = _CC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_FALSE); tr.inStack.push_back(_C); tr.input = _FALSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_FALSE); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_FALSE); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_FALSE); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_FALSE); tr.inStack.push_back(_C); tr.input = _TRUE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_FALSE); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _DOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _CC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _FALSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _TRUE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _DOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _CC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _FALSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _TRUE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_RC); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _DOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _CC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _FALSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _TRUE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_TRUE); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_TRUE); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_TRUE); tr.inStack.push_back(_C); tr.input = _DOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_TRUE); tr.inStack.push_back(_C); tr.input = _CC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_TRUE); tr.inStack.push_back(_C); tr.input = _FALSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_TRUE); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_TRUE); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_TRUE); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_TRUE); tr.inStack.push_back(_C); tr.input = _TRUE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_TRUE); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _PLUS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _MINUS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _DOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _FALSE; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _NUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _RC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _TRUE; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(_C); tr.input = _DOT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(_C); tr.input = _CC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(_C); tr.input = _FALSE; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(_C); tr.input = _RC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(_C); tr.input = _TRUE; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm10() {
    Gramm g(10);
    token_t nonTerms[] = {AOP, CONOP, COP, FOROP, GOP, ID, IFAOP, IFOP, NEWOP, OP, REPOP, ROP, SEOP, SUBOP, UMOP, WOP, LENOP};
    token_t Terms[] = {_COLUM};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 17);
    g.terms.insert(Terms, Terms + 1);
    g.startNonTerm = OP;
    g.rulesCount = 16;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {OP, ID, _COLUM, UMOP};
    token_t r1t[] = {OP, UMOP};
    token_t r2t[] = {UMOP, AOP};
    token_t r3t[] = {UMOP, GOP};
    token_t r4t[] = {UMOP, WOP};
    token_t r5t[] = {UMOP, ROP};
    token_t r6t[] = {UMOP, COP};
    token_t r7t[] = {UMOP, IFOP};
    token_t r8t[] = {UMOP, FOROP};
    token_t r9t[] = {UMOP, CONOP};
    token_t r10t[] = {UMOP, REPOP};
    token_t r11t[] = {UMOP, SEOP};
    token_t r12t[] = {UMOP, SUBOP};
    token_t r13t[] = {UMOP, NEWOP};
    token_t r14t[] = {UMOP, IFAOP};
    token_t r15t[] = {UMOP, LENOP};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    std::vector<token_t> r5 (r5t, r5t + sizeof(r5t) / sizeof(token_t));
    std::vector<token_t> r6 (r6t, r6t + sizeof(r6t) / sizeof(token_t));
    std::vector<token_t> r7 (r7t, r7t + sizeof(r7t) / sizeof(token_t));
    std::vector<token_t> r8 (r8t, r8t + sizeof(r8t) / sizeof(token_t));
    std::vector<token_t> r9 (r9t, r9t + sizeof(r9t) / sizeof(token_t));
    std::vector<token_t> r10 (r10t, r10t + sizeof(r10t) / sizeof(token_t));
    std::vector<token_t> r11 (r11t, r11t + sizeof(r11t) / sizeof(token_t));
    std::vector<token_t> r12 (r12t, r12t + sizeof(r12t) / sizeof(token_t));
    std::vector<token_t> r13 (r13t, r13t + sizeof(r13t) / sizeof(token_t));
    std::vector<token_t> r14 (r14t, r14t + sizeof(r14t) / sizeof(token_t));
    std::vector<token_t> r15 (r15t, r15t + sizeof(r15t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    g.rules[5] = r5;
    g.rules[6] = r6;
    g.rules[7] = r7;
    g.rules[8] = r8;
    g.rules[9] = r9;
    g.rules[10] = r10;
    g.rules[11] = r11;
    g.rules[12] = r12;
    g.rules[13] = r13;
    g.rules[14] = r14;
    g.rules[15] = r15;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(OP); fr.inStack.push_back(_COLUM); fr.inStack.push_back(OP); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _COLUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OP); tr.input = _COLUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm11() {
    Gramm g(11);
    token_t nonTerms[] = {AEXP, ALEXP, AOP, C, ID, LEXP};
    token_t Terms[] = {_EQ};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 6);
    g.terms.insert(Terms, Terms + 1);
	g.startNonTerm = AOP;
    g.rulesCount = 4;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {AOP, ID, _EQ, ALEXP};
    token_t r1t[] = {ALEXP, C};
    token_t r2t[] = {ALEXP, AEXP};
    token_t r3t[] = {ALEXP, LEXP};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(AOP); fr.inStack.push_back(_EQ); fr.inStack.push_back(AOP); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_EQ); tr.inStack.push_back(_C); tr.input = _EQ; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_EQ); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EQ; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(AOP); tr.input = _EQ; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(AOP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm12() {
    Gramm g(12);
    token_t nonTerms[] = {GOP, ID};
    token_t Terms[] = {_GOTO};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 2);
    g.terms.insert(Terms, Terms + 1);
	g.startNonTerm = GOP;
    g.rulesCount = 1;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {GOP, _GOTO, ID};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    
    g.rules[0] = r0;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_GOTO); fr.inStack.push_back(GOP); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_GOTO); tr.inStack.push_back(_C); tr.input = _GOTO; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_GOTO); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _GOTO; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(GOP); tr.input = _GOTO; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(GOP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm13() {
    Gramm g(13);
    token_t nonTerms[] = {AEXP, LEXP, MSG, RMSG, WOP};
    token_t Terms[] = {_OBRACK, _CBRACK, _COMMA, _WRITE, _STR};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 5);
    g.terms.insert(Terms, Terms + 5);
	g.startNonTerm = WOP;
    g.rulesCount = 6;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {WOP, _WRITE, _OBRACK, RMSG, _CBRACK};
    token_t r1t[] = {RMSG, MSG, _COMMA, RMSG};
    token_t r2t[] = {RMSG, MSG};
    token_t r3t[] = {MSG, AEXP};
    token_t r4t[] = {MSG, LEXP};
    token_t r5t[] = {MSG, _STR};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    std::vector<token_t> r5 (r5t, r5t + sizeof(r5t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    g.rules[5] = r5;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_WRITE); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(WOP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(WOP); fr.inStack.push_back(_COMMA); fr.inStack.push_back(WOP); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_COMMA); fr.inStack.push_back(WOP); fr.inStack.push_back(_COMMA); fr.inStack.push_back(WOP); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_STR); fr.ruleNum = 5; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_COMMA); fr.inStack.push_back(_STR); fr.ruleNum = 5; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _WRITE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _WRITE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _WRITE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _WRITE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_WRITE); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_WRITE); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_WRITE); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_WRITE); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_WRITE); tr.inStack.push_back(_C); tr.input = _WRITE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_WRITE); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _WRITE; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(WOP); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(WOP); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(WOP); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(WOP); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(WOP); tr.input = _WRITE; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(WOP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm14() {
    Gramm g(14);
    token_t nonTerms[] = {ID, RID, ROP};
    token_t Terms[] = {_OBRACK, _CBRACK, _COMMA, _READ};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 3);
    g.terms.insert(Terms, Terms + 4);
	g.startNonTerm = ROP;
    g.rulesCount = 3;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {ROP, _READ, _OBRACK, RID, _CBRACK};
    token_t r1t[] = {RID, ID, _COMMA, RID};
    token_t r2t[] = {RID, ID};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_READ); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(ROP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(ROP); fr.inStack.push_back(_COMMA); fr.inStack.push_back(ROP); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_COMMA); fr.inStack.push_back(ROP); fr.inStack.push_back(_COMMA); fr.inStack.push_back(ROP); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _READ; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _READ; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _READ; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_READ); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_READ); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_READ); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_READ); tr.inStack.push_back(_C); tr.input = _READ; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_READ); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _READ; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(ROP); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(ROP); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(ROP); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(ROP); tr.input = _READ; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(ROP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm15() {
    Gramm g(15);
    token_t nonTerms[] = {COP, OP, ZOMOP};
    token_t Terms[] = {_SEMCOL, _BEGIN, _END};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 3);
    g.terms.insert(Terms, Terms + 3);
	g.startNonTerm = COP;
    g.rulesCount = 4;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {COP, _BEGIN, ZOMOP, _END};
    token_t r1t[] = {COP, _BEGIN, _END};
    token_t r2t[] = {ZOMOP , OP, _SEMCOL, ZOMOP};
    token_t r3t[] = {ZOMOP , OP, _SEMCOL};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_BEGIN); fr.inStack.push_back(COP); fr.inStack.push_back(_END); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_BEGIN); fr.inStack.push_back(_END); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(COP); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(COP); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_BEGIN); fr.inStack.push_back(COP); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(COP); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(COP); fr.inStack.push_back(_SEMCOL); fr.ruleNum = 3; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_BEGIN); fr.inStack.push_back(COP); fr.inStack.push_back(_SEMCOL); fr.ruleNum = 3; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _BEGIN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _END; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_BEGIN); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_BEGIN); tr.inStack.push_back(_C); tr.input = _BEGIN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_BEGIN); tr.inStack.push_back(_C); tr.input = _END; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_BEGIN); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_END); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_END); tr.inStack.push_back(_C); tr.input = _BEGIN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_END); tr.inStack.push_back(_C); tr.input = _END; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_END); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _BEGIN; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _END; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(COP); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(COP); tr.input = _BEGIN; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(COP); tr.input = _END; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(COP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm16() {
    Gramm g(16);
    token_t nonTerms[] = {COP, IFOP, LEXP, OCOP, OP};
    token_t Terms[] = {_ELSE, _IF, _THEN};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 5);
    g.terms.insert(Terms, Terms + 3);
	g.startNonTerm = IFOP;
    g.rulesCount = 4;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {IFOP, _IF, LEXP, _THEN, OCOP};
    token_t r1t[] = {IFOP, _IF, LEXP, _THEN, OCOP, _ELSE, OCOP};
    token_t r2t[] = {OCOP, COP};
    token_t r3t[] = {OCOP, OP};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_IF); fr.inStack.push_back(IFOP); fr.inStack.push_back(_THEN); fr.inStack.push_back(IFOP); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_IF); fr.inStack.push_back(IFOP); fr.inStack.push_back(_THEN); fr.inStack.push_back(IFOP); fr.inStack.push_back(_ELSE); fr.inStack.push_back(IFOP); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_ELSE); tr.inStack.push_back(_C); tr.input = _ELSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_ELSE); tr.inStack.push_back(_C); tr.input = _IF; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_ELSE); tr.inStack.push_back(_C); tr.input = _THEN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_ELSE); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_IF); tr.inStack.push_back(_C); tr.input = _ELSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_IF); tr.inStack.push_back(_C); tr.input = _IF; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_IF); tr.inStack.push_back(_C); tr.input = _THEN; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_IF); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_THEN); tr.inStack.push_back(_C); tr.input = _ELSE; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_THEN); tr.inStack.push_back(_C); tr.input = _IF; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_THEN); tr.inStack.push_back(_C); tr.input = _THEN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_THEN); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _ELSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _IF; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _THEN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(IFOP); tr.input = _ELSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(IFOP); tr.input = _IF; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(IFOP); tr.input = _THEN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(IFOP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm17() {
    Gramm g(17);
    token_t nonTerms[] = {COP, FOROP, LEXP, OCOP, OP};
    token_t Terms[] = {_DO, _WHILE};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 5);
    g.terms.insert(Terms, Terms + 2);
	g.startNonTerm = FOROP;
    g.rulesCount = 3;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {FOROP, _WHILE, LEXP, _DO, OCOP};
    token_t r1t[] = {OCOP, COP};
    token_t r2t[] = {OCOP, OP};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_WHILE); fr.inStack.push_back(FOROP); fr.inStack.push_back(_DO); fr.inStack.push_back(FOROP); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_DO); tr.inStack.push_back(_C); tr.input = _DO; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DO); tr.inStack.push_back(_C); tr.input = _WHILE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DO); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_WHILE); tr.inStack.push_back(_C); tr.input = _DO; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_WHILE); tr.inStack.push_back(_C); tr.input = _WHILE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_WHILE); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _DO; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _WHILE; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(FOROP); tr.input = _DO; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(FOROP); tr.input = _WHILE; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(FOROP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm18() {
    Gramm g(18);
    token_t nonTerms[] = {ID, IDSC, LENOP};
    token_t Terms[] = {_OBRACK, _CBRACK, _LEN, _STR};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 3);
    g.terms.insert(Terms, Terms + 4);
	g.startNonTerm = LENOP;
    g.rulesCount = 3;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {LENOP, _LEN, _OBRACK, IDSC, _CBRACK};
    token_t r1t[] = {IDSC, ID};
    token_t r2t[] = {IDSC, _STR};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_LEN); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(LENOP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_STR); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _LEN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _LEN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_LEN); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_LEN); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_LEN); tr.inStack.push_back(_C); tr.input = _LEN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_LEN); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_LEN); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _LEN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _LEN; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LENOP); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LENOP); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LENOP); tr.input = _LEN; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LENOP); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(LENOP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm19() {
    Gramm g(19);
    token_t nonTerms[] = {CONOP, ID, IDSC};
    token_t Terms[] = {_OBRACK, _CBRACK, _COMMA, _CONC, _STR};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 3);
    g.terms.insert(Terms, Terms + 5);
	g.startNonTerm = CONOP;
    g.rulesCount = 3;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {CONOP, _CONC, _OBRACK, IDSC, _COMMA, IDSC, _CBRACK};
    token_t r1t[] = {IDSC, ID};
    token_t r2t[] = {IDSC, _STR};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_CONC); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(CONOP); fr.inStack.push_back(_COMMA); fr.inStack.push_back(CONOP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_STR); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_COMMA); fr.inStack.push_back(_STR); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _CONC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _CONC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _CONC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CONC); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CONC); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CONC); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CONC); tr.inStack.push_back(_C); tr.input = _CONC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CONC); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CONC); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _CONC; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CONC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(CONOP); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(CONOP); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(CONOP); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(CONOP); tr.input = _CONC; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(CONOP); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(CONOP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm20() {
    Gramm g(20);
    token_t nonTerms[] = {ID, IDSC, REPOP};
    token_t Terms[] = {_OBRACK, _CBRACK, _COMMA, _REPL, _STR};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 3);
    g.terms.insert(Terms, Terms + 5);
	g.startNonTerm = REPOP;
    g.rulesCount = 3;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {REPOP, _REPL, _OBRACK, IDSC, _COMMA, IDSC, _COMMA, IDSC, _CBRACK};
    token_t r1t[] = {IDSC, ID};
    token_t r2t[] = {IDSC, _STR};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_REPL); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(REPOP); fr.inStack.push_back(_COMMA); fr.inStack.push_back(REPOP); fr.inStack.push_back(_COMMA); fr.inStack.push_back(REPOP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_STR); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_COMMA); fr.inStack.push_back(_STR); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _REPL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _REPL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _REPL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_REPL); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REPL); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REPL); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REPL); tr.inStack.push_back(_C); tr.input = _REPL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REPL); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REPL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _REPL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _REPL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(REPOP); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(REPOP); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(REPOP); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(REPOP); tr.input = _REPL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(REPOP); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(REPOP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm21() {
    Gramm g(21);
    token_t nonTerms[] = {ID, IDSC, SEOP};
    token_t Terms[] = {_OBRACK, _CBRACK, _COMMA, _SRCH, _STR};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 3);
    g.terms.insert(Terms, Terms + 5);
	g.startNonTerm = SEOP;
    g.rulesCount = 3;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {SEOP, _SRCH, _OBRACK, IDSC, _COMMA, IDSC, _CBRACK};
    token_t r1t[] = {IDSC, ID};
    token_t r2t[] = {IDSC, _STR};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_SRCH); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(SEOP); fr.inStack.push_back(_COMMA); fr.inStack.push_back(SEOP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_STR); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_COMMA); fr.inStack.push_back(_STR); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _SRCH; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _SRCH; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _SRCH; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_SRCH); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SRCH); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SRCH); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SRCH); tr.inStack.push_back(_C); tr.input = _SRCH; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SRCH); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SRCH); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _SRCH; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _SRCH; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(SEOP); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(SEOP); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(SEOP); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(SEOP); tr.input = _SRCH; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(SEOP); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(SEOP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm22() {
    Gramm g(22);
    token_t nonTerms[] = {ID, IDNN, IDSC, SUBOP};
    token_t Terms[] = {_OBRACK, _CBRACK, _COMMA, _NUM, _SUBS, _STR};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 4);
    g.terms.insert(Terms, Terms + 6);
	g.startNonTerm = SUBOP;
    g.rulesCount = 5;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {SUBOP, _SUBS, _OBRACK, IDSC, _COMMA, IDNN, _COMMA, IDNN, _CBRACK};
    token_t r1t[] = {IDNN, ID};
    token_t r2t[] = {IDNN, _NUM};
    token_t r3t[] = {IDSC, ID};
    token_t r4t[] = {IDSC, _STR};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_SUBS); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(SUBOP); fr.inStack.push_back(_COMMA); fr.inStack.push_back(SUBOP); fr.inStack.push_back(_COMMA); fr.inStack.push_back(SUBOP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_COMMA); fr.inStack.push_back(_NUM); fr.ruleNum = 2; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(_STR); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _SUBS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _SUBS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _SUBS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _SUBS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NUM); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _SUBS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_STR); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_SUBS); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SUBS); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SUBS); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SUBS); tr.inStack.push_back(_C); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SUBS); tr.inStack.push_back(_C); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SUBS); tr.inStack.push_back(_C); tr.input = _SUBS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SUBS); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _SUBS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(SUBOP); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(SUBOP); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(SUBOP); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(SUBOP); tr.input = _NUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(SUBOP); tr.input = _STR; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(SUBOP); tr.input = _SUBS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(SUBOP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm23() {
    Gramm g(23);
    token_t nonTerms[] = {CLV, CONSTS, FUNCS, LABELS, VARS};
    token_t Terms[] = {_SEMCOL};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 5);
    g.terms.insert(Terms, Terms + 1);
	g.startNonTerm = CLV;
    g.rulesCount = 8;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {CLV, CONSTS};
    token_t r1t[] = {CLV, CONSTS, _SEMCOL, CLV};
    token_t r2t[] = {CLV, LABELS};
    token_t r3t[] = {CLV, LABELS, _SEMCOL, CLV};
    token_t r4t[] = {CLV, VARS};
    token_t r5t[] = {CLV, VARS, _SEMCOL, CLV};
    token_t r6t[] = {CLV, FUNCS};
    token_t r7t[] = {CLV, FUNCS, _SEMCOL, CLV};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    std::vector<token_t> r5 (r5t, r5t + sizeof(r5t) / sizeof(token_t));
    std::vector<token_t> r6 (r6t, r6t + sizeof(r6t) / sizeof(token_t));
    std::vector<token_t> r7 (r7t, r7t + sizeof(r7t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    g.rules[5] = r5;
    g.rules[6] = r6;
    g.rules[7] = r7;
    
    { struct FoldRule fr; fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(CLV); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(CLV); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(CLV); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(CLV); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(CLV); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(CLV); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm24() {
    Gramm g(24);
    token_t nonTerms[] = {ID, NEWOP};
    token_t Terms[] = {_OBRACK, _CBRACK, _NEWW};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 2);
    g.terms.insert(Terms, Terms + 3);
	g.startNonTerm = NEWOP;
    g.rulesCount = 1;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {NEWOP, _NEWW, _OBRACK, ID, _CBRACK};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    
    g.rules[0] = r0;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_NEWW); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(NEWOP); fr.inStack.push_back(_CBRACK); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _NEWW; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _NEWW; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_NEWW); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NEWW); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NEWW); tr.inStack.push_back(_C); tr.input = _NEWW; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_NEWW); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _NEWW; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(NEWOP); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(NEWOP); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(NEWOP); tr.input = _NEWW; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(NEWOP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm25() {
    Gramm g(25);
    token_t nonTerms[] = {AOP, IFAOP, LEXP, OEAOP};
    token_t Terms[] = {_ELSE, _IF, _THEN};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 4);
    g.terms.insert(Terms, Terms + 3);
	g.startNonTerm = IFAOP;
    g.rulesCount = 2;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {IFAOP, _IF, LEXP, _THEN, AOP};
    token_t r1t[] = {IFAOP, _IF, LEXP, _THEN, AOP, _ELSE, AOP};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_IF); fr.inStack.push_back(IFAOP); fr.inStack.push_back(_THEN); fr.inStack.push_back(IFAOP); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_IF); fr.inStack.push_back(IFAOP); fr.inStack.push_back(_THEN); fr.inStack.push_back(IFAOP); fr.inStack.push_back(_ELSE); fr.inStack.push_back(IFAOP); fr.ruleNum = 1; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_ELSE); tr.inStack.push_back(_C); tr.input = _ELSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_ELSE); tr.inStack.push_back(_C); tr.input = _IF; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_ELSE); tr.inStack.push_back(_C); tr.input = _THEN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_ELSE); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_IF); tr.inStack.push_back(_C); tr.input = _ELSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_IF); tr.inStack.push_back(_C); tr.input = _IF; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_IF); tr.inStack.push_back(_C); tr.input = _THEN; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_IF); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_THEN); tr.inStack.push_back(_C); tr.input = _ELSE; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_THEN); tr.inStack.push_back(_C); tr.input = _IF; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_THEN); tr.inStack.push_back(_C); tr.input = _THEN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_THEN); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _ELSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _IF; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _THEN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(IFAOP); tr.input = _ELSE; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(IFAOP); tr.input = _IF; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(IFAOP); tr.input = _THEN; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(IFAOP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGramm26() {
    Gramm g(26);
    token_t nonTerms[] = {COP, ID, OOP, OPOP, OVAR, OVAR1, OVAR2, TYPE};
    token_t Terms[] = {_OBRACK, _CBRACK, _MULT, _PLUS, _COMMA, _MINUS, _DIV, _COLUM, _SEMCOL, _OPER, _REL};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 8);
    g.terms.insert(Terms, Terms + 11);
	g.startNonTerm = OPOP;
    g.rulesCount = 10;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {OPOP, _OPER, OOP, _OBRACK, OVAR, _CBRACK, ID, _COLUM, TYPE, _SEMCOL, COP};
    token_t r1t[] = {OVAR, OVAR1};
    token_t r2t[] = {OVAR, OVAR2};
    token_t r3t[] = {OVAR1, ID, _COLUM, TYPE, _SEMCOL, ID, _COLUM, TYPE};
    token_t r4t[] = {OVAR2, ID, _COMMA, ID, _COLUM, TYPE};
    token_t r5t[] = {OOP, _REL};
    token_t r6t[] = {OOP, _PLUS};
    token_t r7t[] = {OOP, _MINUS};
    token_t r8t[] = {OOP, _MULT};
    token_t r9t[] = {OOP, _DIV};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    std::vector<token_t> r5 (r5t, r5t + sizeof(r5t) / sizeof(token_t));
    std::vector<token_t> r6 (r6t, r6t + sizeof(r6t) / sizeof(token_t));
    std::vector<token_t> r7 (r7t, r7t + sizeof(r7t) / sizeof(token_t));
    std::vector<token_t> r8 (r8t, r8t + sizeof(r8t) / sizeof(token_t));
    std::vector<token_t> r9 (r9t, r9t + sizeof(r9t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    g.rules[5] = r5;
    g.rules[6] = r6;
    g.rules[7] = r7;
    g.rules[8] = r8;
    g.rules[9] = r9;
    
    { struct FoldRule fr; fr.inStack.push_back(_HASH); fr.inStack.push_back(_OPER); fr.inStack.push_back(OPOP); fr.inStack.push_back(_OBRACK); fr.inStack.push_back(OPOP); fr.inStack.push_back(_CBRACK); fr.inStack.push_back(OPOP); fr.inStack.push_back(_COLUM);fr.inStack.push_back(OPOP); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(OPOP); fr.ruleNum = 0; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(OPOP); fr.inStack.push_back(_COLUM); fr.inStack.push_back(OPOP); fr.inStack.push_back(_SEMCOL); fr.inStack.push_back(OPOP); fr.inStack.push_back(_COLUM); fr.inStack.push_back(OPOP);fr.ruleNum = 3; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OBRACK); fr.inStack.push_back(OPOP); fr.inStack.push_back(_COMMA); fr.inStack.push_back(OPOP); fr.inStack.push_back(_COLUM); fr.inStack.push_back(OPOP); fr.ruleNum = 4; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OPER); fr.inStack.push_back(_REL); fr.ruleNum = 5; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OPER); fr.inStack.push_back(_PLUS); fr.ruleNum = 6; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OPER); fr.inStack.push_back(_MINUS); fr.ruleNum = 7; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OPER); fr.inStack.push_back(_MULT); fr.ruleNum = 8; g.foldRules.push_back(fr); }
    { struct FoldRule fr; fr.inStack.push_back(_OPER); fr.inStack.push_back(_DIV); fr.ruleNum = 9; g.foldRules.push_back(fr); }
    
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _OPER; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _OPER; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_CBRACK); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _OPER; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MULT); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _OPER; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_PLUS); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _OPER; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COMMA); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _OPER; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_MINUS); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _OPER; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_DIV); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _OPER; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_COLUM); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _OPER; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_SEMCOL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _R; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_OPER); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OPER); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OPER); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OPER); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OPER); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OPER); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OPER); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OPER); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OPER); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OPER); tr.inStack.push_back(_C); tr.input = _OPER; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OPER); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_OPER); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _OBRACK; tr.rule = _R; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _MULT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _DIV; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _OPER; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_REL); tr.inStack.push_back(_C); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _MULT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _DIV; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _OPER; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.input = _EPS; tr.rule = _E; g.transRules.push_back(tr); }

    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OPOP); tr.input = _OBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OPOP); tr.input = _CBRACK; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OPOP); tr.input = _MULT; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OPOP); tr.input = _PLUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OPOP); tr.input = _COMMA; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OPOP); tr.input = _MINUS; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OPOP); tr.input = _DIV; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OPOP); tr.input = _COLUM; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OPOP); tr.input = _SEMCOL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OPOP); tr.input = _OPER; tr.rule = _S; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OPOP); tr.input = _REL; tr.rule = _E; g.transRules.push_back(tr); }
    { struct TransRule tr; tr.inStack.push_back(_HASH); tr.inStack.push_back(OPOP); tr.input = _EPS; tr.rule = _A; g.transRules.push_back(tr); }
    
    grams.push_back(g);
}
void initGrams() {
    grams.clear();
    initGramm0();
	initGramm1();
    initGramm2();
    initGramm3();
    initGramm4();
    initGramm5();
    initGramm6();
    initGramm7();
    initGramm8();
    initGramm9();
    initGramm10();
    initGramm11();
    initGramm12();
    initGramm13();
    initGramm14();
    initGramm15();
    initGramm16();
    initGramm17();
    initGramm18();
    initGramm19();
    initGramm20();
    initGramm21();
    initGramm22();
    initGramm23();
    initGramm24();
    initGramm25();
    initGramm26();
}

class Symbol {
public:
    Symbol(token_t id, std::string& str, bool isToken);
    Symbol(token_t id, const char* str, bool isToken);
    // ID from token enum
    token_t id;
    // String representation
    std::string str;
    // True if token, false if non terminal
    bool isToken;
};

Symbol::Symbol(token_t id, std::string& str, bool isToken) {
    this->id = id;
    this->str = str;
    this->isToken = isToken;
}

Symbol::Symbol(token_t id, const char* str, bool isToken) {
    this->id = id;
    this->str = std::string(str);
    this->isToken = isToken;
}

// Class current gramm
class CurGram {
public:
    CurGram (int i, int f) : id(i), firstElemInCS(f) {};
	// ID of Gramm
	int id;
	// Pointer of first element by gramm in common stack
	int firstElemInCS;
};

// Input token sequence (from lexical analizer).
std::vector<Symbol> tokens;
// Common stack
std::stack<Symbol> commonStack;
// Stack of gramms
std::stack<CurGram> gramsStack;
// Output stack

// States
typedef enum {
    S_START, S_ERROR,
    S_150, S_151, S_152,
    S_B, S_67, S_68, S_69, S_70, S_71, S_72, S_80, S_81, S_82, S_83,
    S_C, S_76, S_77, S_78, S_CO, S_CON, S_98, S_99, S_100, S_11, S_12,
    S_73, S_74,
    S_E, S_46, S_47, S_48, S_85, S_86,
    S_F, S_62, S_63, S_64, S_65, S_127, S_128, S_129, S_130, S_131, S_132, S_133,
    S_30, S_31, S_32, S_33,
    S_I, S_40, S_14, S_15, S_16, S_17, S_18, S_19,
    S_L, S_91, S_92, S_93, S_94, S_102, S_103, S_104, S_105, S_106,
    S_N, S_143, S_144, S_146, S_147,
    S_O, S_135, S_136, S_137, S_138, S_139, S_140, S_141, S_149,
    S_1, S_2, S_3, S_4, S_5, S_6, S_7,
    S_R, S_RE, S_REA, S_52, S_23, S_109, S_110, S_111, S_112, S_113,
    S_S, S_25, S_26, S_27, S_28, S_29, S_115, S_116, S_117, S_118, S_119, S_121, S_122, S_123, S_124, S_125,
    S_T, S_58, S_59, S_60, S_42, S_43, S_44,
    S_87, S_88, S_89,
    S_W, S_54, S_55, S_56, S_57, S_35, S_36, S_37, S_38,
    S_160,
    S_163, S_164, S_165, S_166, S_167,
    S_168, S_169, S_170, S_171, S_172,
    S_155, S_156, S_157, S_158, S_200, S_201,
    S_153, S_154
} state_t;

bool isNum(char c) {
    return (c == '0' || c == '1' || c == '2' || c == '3' ||
            c == '4' || c == '5' || c == '6' || c == '7' ||
            c == '8' || c == '9');
}
bool isLetter(char c) {
    return (c == 'A' || c == 'a' ||
            c == 'B' || c == 'b' ||
            c == 'C' || c == 'c' ||
            c == 'D' || c == 'd' ||
            c == 'E' || c == 'e' ||
            c == 'F' || c == 'f' ||
            c == 'G' || c == 'g' ||
            c == 'H' || c == 'h' ||
            c == 'I' || c == 'i' ||
            c == 'J' || c == 'j' ||
            c == 'K' || c == 'k' ||
            c == 'L' || c == 'l' ||
            c == 'M' || c == 'm' ||
            c == 'N' || c == 'n' ||
            c == 'O' || c == 'o' ||
            c == 'P' || c == 'p' ||
            c == 'Q' || c == 'q' ||
            c == 'R' || c == 'r' ||
            c == 'S' || c == 's' ||
            c == 'T' || c == 't' ||
            c == 'U' || c == 'u' ||
            c == 'V' || c == 'v' ||
            c == 'W' || c == 'w' ||
            c == 'X' || c == 'x' ||
            c == 'Y' || c == 'y' ||
            c == 'Z' || c == 'z' ||
            c == '_');
}
bool isSpace(char c) {
    return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
}
bool isPunct(char c) {
    return (c == '+' || c == '-' ||
            c == '*' || c == '/' ||
            c == '<' || c == '>' ||
            c == '=' || c == ':' ||
            c == ';' || c == ',' ||
            c == '.' || c == '(' ||
            c == ')' || c == '[' ||
            c == ']' || c == '!' ||
            c == '?');
}
void printHelp() {
    std::cout << "Usage: kurs <file_name>\n";
}
void unrecErr(char c) {
    std::cout << "\nUnrecognized symbol: '" << c << "'" << std::endl;
    exit(1);
}

void saveCurrentId() {
    std::string str = "_ID[";
	acc.pop_back();
    while (acc.size()) { str += acc.front(); acc.pop_front(); }
	str += "]";
    std::cout << str << "  ";
	acc.clear();
	
	Symbol symbol(_ID, str, 1);
	tokens.push_back(symbol);
}
void saveAnd() {
	std::string str = "_AND";
    std::cout << "_AND  ";
    acc.clear();
	
	Symbol symbol(_AND, str, 1);
	tokens.push_back(symbol);
}
void saveBoolean() {
	std::string str = "_BOOL";
    std::cout << "_BOOL  ";
    acc.clear();
	
	Symbol symbol(_BOOL, str, 1);
	tokens.push_back(symbol);
}
void saveBegin() {
	std::string str = "_BEGIN";
    std::cout << "_BEGIN  ";
    acc.clear();
	
	Symbol symbol(_BEGIN, str, 1);
	tokens.push_back(symbol);
}
void saveChar() {
	std::string str = "_CHAR";
    std::cout << "_CHAR  ";
    acc.clear();
	
	Symbol symbol(_CHAR, str, 1);
	tokens.push_back(symbol);
}
void saveConcat() {
	std::string str = "_CONC";
    std::cout << "_CONC  ";
    acc.clear();
	
	Symbol symbol(_CONC, str, 1);
	tokens.push_back(symbol);
}
void saveConst() {
	std::string str = "_CONST";
    std::cout << "_CONST  ";
    acc.clear();
	
	Symbol symbol(_CONST, str, 1);
	tokens.push_back(symbol);
}
void saveDo() {
	std::string str = "_DO";
    std::cout << "_DO  ";
    acc.clear();
	
	Symbol symbol(_DO, str, 1);
	tokens.push_back(symbol);
}
void saveElse() {
	std::string str = "_ELSE";
    std::cout << "_ELSE  ";
    acc.clear();
	
	Symbol symbol(_ELSE, str, 1);
	tokens.push_back(symbol);
}
void saveEnd() {
	std::string str = "_END";
    std::cout << "_END  ";
    acc.clear();
	
	Symbol symbol(_END, str, 1);
	tokens.push_back(symbol);
}
void saveFalse() {
	std::string str = "_FALSE";
    std::cout << "_FALSE  ";
    acc.clear();
	
	Symbol symbol(_FALSE, str, 1);
	tokens.push_back(symbol);
}
void saveFunction() {
	std::string str = "_FUNC";
    std::cout << "_FUNC  ";
    acc.clear();
	
	Symbol symbol(_FUNC, str, 1);
	tokens.push_back(symbol);
}
void saveGoto() {
	std::string str = "_GOTO";
    std::cout << "_GOTO  ";
    acc.clear();
	
	Symbol symbol(_GOTO, str, 1);
	tokens.push_back(symbol);
}
void saveIf() {
	std::string str = "_IF";
    std::cout << "_IF  ";
    acc.clear();
	
	Symbol symbol(_IF, str, 1);
	tokens.push_back(symbol);
}
void saveInteger() {
	std::string str = "_INT";
    std::cout << "_INT  ";
    acc.clear();
	
	Symbol symbol(_INT, str, 1);
	tokens.push_back(symbol);
}
void saveLabel() {
	std::string str = "_LABEL";
    std::cout << "_LABEL  ";
    acc.clear();
	
	Symbol symbol(_LABEL, str, 1);
	tokens.push_back(symbol);
}
void saveLength() {
	std::string str = "_LEN";
    std::cout << "_LEN  ";
    acc.clear();
	
	Symbol symbol(_LEN, str, 1);
	tokens.push_back(symbol);
}
void saveNew() {
	std::string str = "_NEW";
    std::cout << "_NEW  ";
    acc.clear();
	
	Symbol symbol(_NEWW, str, 1);
	tokens.push_back(symbol);
}
void saveNot() {
	std::string str = "_NOT";
    std::cout << "_NOT  ";
    acc.clear();
	
	Symbol symbol(_NOT, str, 1);
	tokens.push_back(symbol);
}
void saveOperator() {
	std::string str = "_OPER";
    std::cout << "_OPER  ";
    acc.clear();
	
	Symbol symbol(_OPER, str, 1);
	tokens.push_back(symbol);
}
void saveOr() {
	std::string str = "_OR";
    std::cout << "_OR  ";
    acc.clear();
	
	Symbol symbol(_OR, str, 1);
	tokens.push_back(symbol);
}
void saveProgram() {
	std::string str = "_PROG";
    std::cout << "_PROG  ";
    acc.clear();
	
	Symbol symbol(_PROG, str, 1);
	tokens.push_back(symbol);
}
void saveRead() {
	std::string str = "_READ";
    std::cout << "_READ  ";
    acc.clear();
	
	Symbol symbol(_READ, str, 1);
	tokens.push_back(symbol);
}
void saveReal() {
	std::string str = "_REAL";
    std::cout << "_REAL  ";
    acc.clear();
	
	Symbol symbol(_REAL, str, 1);
	tokens.push_back(symbol);
}
void saveReplace() {
	std::string str = "_REPL";
    std::cout << "_REPL  ";
    acc.clear();
	
	Symbol symbol(_REPL, str, 1);
	tokens.push_back(symbol);
}
void saveString() {
	std::string str = "_STRING";
    std::cout << "_STRING  ";
    acc.clear();
	
	Symbol symbol(_STRING, str, 1);
	tokens.push_back(symbol);
}
void saveSubstr() {
	std::string str = "_SUBS";
    std::cout << "_SUBS  ";
    acc.clear();
	
	Symbol symbol(_SUBS, str, 1);
	tokens.push_back(symbol);
}
void saveSearch() {
	std::string str = "_SRCH";
    std::cout << "_SRCH  ";
    acc.clear();
	
	Symbol symbol(_SRCH, str, 1);
	tokens.push_back(symbol);
}
void saveTrue() {
	std::string str = "_TRUE";
    std::cout << "_TRUE  ";
    acc.clear();
	
	Symbol symbol(_TRUE, str, 1);
	tokens.push_back(symbol);
}
void saveThen() {
	std::string str = "_THEN";
    std::cout << "_THEN  ";
    acc.clear();
	
	Symbol symbol(_THEN, str, 1);
	tokens.push_back(symbol);
}
void saveWrite() {
	std::string str = "_WRITE";
    std::cout << "_WRITE  ";
    acc.clear();
	
	Symbol symbol(_WRITE, str, 1);
	tokens.push_back(symbol);
}
void saveWhile() {
	std::string str = "_WHILE";
    std::cout << "_WHILE  ";
    acc.clear();
	
	Symbol symbol(_WHILE, str, 1);
	tokens.push_back(symbol);
}
void saveColumn() {
	std::string str = ":";
    std::cout << ":  ";
    acc.clear();
	
	Symbol symbol(_COLUM, str, 1);
	tokens.push_back(symbol);
}
void saveEq() {
	std::string str = "_EQ";
    std::cout << "_EQ  ";
    acc.clear();
	
	Symbol symbol(_EQ, str, 1);
	tokens.push_back(symbol);
}
void saveLess() {
	std::string str = "_REL[<]";
    std::cout << "_REL[<]  ";
    acc.clear();
	
	Symbol symbol(_REL, str, 1);
	tokens.push_back(symbol);
}
void saveNotEqual() {
	std::string str = "_REL[<>]";
    std::cout << "_REL[<>]  ";
    acc.clear();
	
	Symbol symbol(_REL, str, 1);
	tokens.push_back(symbol);
}
void saveLessEqual() {
	std::string str = "_REL[<=]";
    std::cout << "_REL[<=]  ";
    acc.clear();
	
	Symbol symbol(_REL, str, 1);
	tokens.push_back(symbol);
}
void saveEqual() {
	std::string str = "_REL[=]";
    std::cout << "_REL[=]  ";
    acc.clear();
	
	Symbol symbol(_REL, str, 1);
	tokens.push_back(symbol);
}
void saveGreater() {
	std::string str = "_REL[>]";
    std::cout << "_REL[>]  ";
    acc.clear();
	
	Symbol symbol(_REL, str, 1);
	tokens.push_back(symbol);
}
void saveGreaterEqual() {
	std::string str = "_REL[>=]";
    std::cout << "_REL[>=]  ";
    acc.clear();
	
	Symbol symbol(_REL, str, 1);
	tokens.push_back(symbol);
}
void saveNum() {
	std::string str = "_NUM[";
    acc.pop_back();
    while (acc.size()) { str += acc.front(); acc.pop_front(); }
	str += "]";
    std::cout << str << "  ";
    acc.clear();
	
	Symbol symbol(_NUM, str, 1);
	tokens.push_back(symbol);
}
void saveRc() {
	std::string str = "_RC[";
    acc.pop_back();
    while (acc.size()) { str += acc.front(); acc.pop_front(); }
	str += "]";
    std::cout << str << "  ";
    acc.clear();
	
	Symbol symbol(_RC, str, 1);
	tokens.push_back(symbol);
}
void saveStr() {
	std::string str = "_STR[";
    acc.pop_back();
    while (acc.size()) { str += acc.front(); acc.pop_front(); }
	str += "]";
    std::cout << str << "  ";
    acc.clear();
	
	Symbol symbol(_STR, str, 1);
	tokens.push_back(symbol);
}
void savePunct(char c) {
	std::string str = "";
	token_t t;
	switch(c) {
        case '+':
            str = "+";
			t = _PLUS;
			break;                
        case '-':
            str = "-";
			t = _MINUS;
			break; 
		case '*':
            str = "*";
			t = _MULT;
			break;
		case '/':
            str = "/";
			t = _DIV;
			break;
		case ';':
            str = ";";
			t = _SEMCOL;
			break;
		case ',':
            str = ",";
			t = _COMMA;
			break;
		case '.':
            str = ".";
			t = _DOT;
			break;
		case '(':
            str = "(";
			t = _OBRACK;
			break;
		case ')':
            str = ")";
			t = _CBRACK;
			break;
	}
    std::cout << c << "  ";
    acc.clear();
	
	Symbol symbol(t, str, 1);
	tokens.push_back(symbol);
}
void saveVar() {
	std::string str = "_VAR";
    std::cout << "_VAR  ";
    acc.clear();
	
	Symbol symbol(_VAR, str, 1);
	tokens.push_back(symbol);
}

bool isTokenInGram(int gi, token_t t) {
    std::set<token_t>::iterator it = grams[gi].terms.find(t);
    bool r = (it != grams[gi].terms.end());
    return r; 
}

// Is A token exist before B token in tokens vector.
bool isAtB(token_t a, token_t b) {
    bool r = false;
    int i;
    for (i = 0; i < tokens.size(); i++) {
        if (tokens[i].id == b) break;
        else if (tokens[i].id == a) {
            r = true;
            break;
        }
    }
    return r;
}

int findTokenInGram(int gi, token_t t) {
    std::cout << "findTokenInGram(gi=" << gi << ", t="; pT(t); std::cout  << ")" << std::endl;
	Gramm& g = grams[gi];
    // std::cout << "1\n";
	// Если текущий символ есть в текущей грамматике
    if (isTokenInGram(gi, t)) {
        // std::cout << "2\n";
        //tokensUsedInFindGram.clear();
        // std::cout << "3\n";
		// Возможно символ все-таки принадлежит не этой грамматике
		token_t nextT = tokens[1].id;
		switch(gi) {
			case 1:
                // Может надо проверять, что t == _SEMCOL ?
				if (t == _SEMCOL && (nextT == _BEGIN || nextT == _VAR || nextT == _CONST || nextT == _LABEL || nextT == _FUNC)) return -1;
				break;
			case 2:
				if (t == _SEMCOL && (nextT == _BEGIN || nextT == _VAR || nextT == _CONST || nextT == _LABEL || nextT == _FUNC)) return -1;
				break;
			case 3:
				if (t == _SEMCOL && (nextT == _BEGIN || nextT == _VAR || nextT == _CONST || nextT == _LABEL || nextT == _FUNC)) return -1;
				break;
			case 4:
				if (t == _SEMCOL && commonStack.top().id == FUNCS) {
                    Symbol s1 = commonStack.top();
                    commonStack.pop();
                    Symbol s2 = commonStack.top();
                    commonStack.push(s1);
                    if (s2.id == _SEMCOL || s2.id == _HASH) return -1;
                }
				break;
            case 7:
                if (t == _CBRACK && commonStack.top().id == AEXP) {
                    Symbol s1 = commonStack.top();
                    commonStack.pop();
                    Symbol s2 = commonStack.top();
                    commonStack.push(s1);
                    if (s2.id == _HASH) return -1;
                }
                break;
            case 15:
				if (t == _SEMCOL && commonStack.top().id == _END) return -1;
				else if (t == _SEMCOL && commonStack.top().id == COP) {
                    Symbol s1 = commonStack.top();
                    commonStack.pop();
                    Symbol s2 = commonStack.top();
                    commonStack.push(s1);
                    if (s2.id == _HASH) return -1;
                }
                break;
			case 23:
				if (t == _SEMCOL && (nextT == _BEGIN)) return -1;
				break;
            case 26:
                if (t == _SEMCOL && commonStack.top().id == OPOP) {
                    Symbol s1 = commonStack.top();
                    commonStack.pop();
                    Symbol s2 = commonStack.top();
                    commonStack.push(s1);
                    if (s2.id == _SEMCOL || s2.id == _HASH) return -1;
                }
                break;
		}
        return gi;
    }
	// Поиск грамматики, в которую надо перейти
    else {
		switch(gi) {
			case 0:
				if (t == _ID) return 6;
				else if (t == _CONST) return 23;
				else if (t == _VAR) return 23;
				else if (t == _LABEL) return 23;
				else if (t == _FUNC) return 23;
				else if (t == _BEGIN) return 15;
                else if (t == _OPER) return 26;
				break;
			case 1:
				if (t == _ID) return 6;
				else if (t == _INT) return 5;
				else if (t == _REAL) return 5;
				else if (t == _BOOL) return 5;
				else if (t == _CHAR) return 5;
				else if (t == _STRING) return 5;
				break;
			case 2:
				if (t == _ID) return 6;
				else return 9;
				break;
			case 3:
				if (t == _ID) return 6;
				break;
			case 4:
				if (t == _OPER) return 26;
				else if (t == _BEGIN) return 15;
				else if (t == _VAR) return 1;
				else if (t == _ID) return 6;
				else if (t == _INT) return 5;
				else if (t == _REAL) return 5;
				else if (t == _BOOL) return 5;
				else if (t == _CHAR) return 5;
				else if (t == _STRING) return 5;
				break;
			/* case 5:
				
				break; */
			/* case 6:
				
				break; */
			case 7:
				if (t == _ID) return 6;
				break;
			case 8:
				// if (t != _STR && tokens[1].id == _REL) return 7;
				if ((t == _PLUS || t == _MINUS || t == _OBRACK || t == _ID || t == _NUM || t == _RC) && isAtB(_REL, _SEMCOL) &&
                    !(isAtB(_AND, _REL) || isAtB(_OR, _REL))) return 7;
                else if (t != _STR && commonStack.top().id == _REL) return 7;
                else if (t == _ID) return 6;
				break;
			/* case 9:
				
				break; */
			case 10:
				if (t == _ID && tokens[1].id == _COLUM) return 6;
				else if (t == _ID && tokens[1].id == _EQ) return 11;
				else if (t == _GOTO) return 12;
				else if (t == _WRITE) return 13;
				else if (t == _READ) return 14;
				else if (t == _BEGIN) return 15;
				else if (t == _IF) return 16;
				else if (t == _WHILE) return 17;
				else if (t == _LEN) return 18;
				else if (t == _CONC) return 19;
				else if (t == _REPL) return 20;
				else if (t == _SRCH) return 21;
				else if (t == _SUBS) return 22;
				else if (t == _NEWW) return 24;
				break;
			case 11:
				// TODO ////////////////////////////////////////////////
				if (t == _ID && tokens[1].id == _EQ) return 6;
                else if (isAtB(_NOT, _SEMCOL) || isAtB(_OR, _SEMCOL) || isAtB(_AND, _SEMCOL) ||
                         isAtB(_REL, _SEMCOL)) return 8;
                else if (t == _CC || t == _TRUE || t == _FALSE || t == _STR) return 9;
                else if (t == _PLUS || t == _MINUS || t == _OBRACK || t == _ID || t == _NUM || t == _RC) return 7;
				break;
			case 12:
				if (t == _ID) return 6;
				break;
			case 13:
				// TODO ////////////////////////////////////////////////
                if (isAtB(_NOT, _SEMCOL) || isAtB(_OR, _SEMCOL) || isAtB(_AND, _SEMCOL) ||
                         isAtB(_REL, _SEMCOL)) return 8;
                else if (t == _PLUS || t == _MINUS || t == _OBRACK || t == _ID || t == _NUM || t == _RC) return 7;
				break;
			case 14:
				if (t == _ID) return 6;
				break;
			case 15:
				if (commonStack.top().id == _END || commonStack.top().id == COP) return -1;
				//if (t != _BEGIN && t != _END && t != _SEMCOL) return 10;
				return 10;
				break;
			case 16:
				if (commonStack.top().id == _IF) return 8;
				else if ((commonStack.top().id == _THEN || commonStack.top().id == _ELSE) && t == _BEGIN) return 15;
				else if (commonStack.top().id == _THEN || commonStack.top().id == _ELSE) return 10;
				break;
			case 17:
				if (commonStack.top().id == _WHILE) return 8;
				else if (commonStack.top().id == _DO && t == _BEGIN) return 15;
				else if (commonStack.top().id == _DO) return 10;
				break;
			case 18:
				if (t == _ID) return 6;
				break;
			case 19:
				if (t == _ID) return 6;
				break;
			case 20:
				if (t == _ID) return 6;
				break;
			case 21:
				if (t == _ID) return 6;
				break;
			case 22:
				if (t == _ID) return 6;
				break;
			case 23:
				if (t == _CONST) return 2;
				else if (t == _VAR) return 1;
				else if (t == _LABEL) return 3;
				else if (t == _FUNC) return 4;
				else if (t == _OPER) return 4;
				break;
			case 24:
				if (t == _ID) return 6;
				break;
            case 25:
				if (commonStack.top().id == _IF) return 8;
				else if (commonStack.top().id == _THEN || commonStack.top().id == _ELSE) return 11;
				break;
            case 26:
                if (t == _ID) return 6;
                else if (t == _INT) return 5;
				else if (t == _REAL) return 5;
				else if (t == _BOOL) return 5;
				else if (t == _CHAR) return 5;
				else if (t == _STRING) return 5;
                else if (t == _BEGIN) return 15;
                break;
            default:
                break;
		}
		
        return -1;
    }
}

void pGramStack() {
    std::cout << "Grams stack: [\n";
    for (std::stack<CurGram> dump = gramsStack; !dump.empty(); dump.pop())
        std::cout << "  " << dump.top().id << '\n';
    std::cout << "]\n";
}
void pCommonStack() {
    std::cout << "Common stack: [";
    
    std::stack<Symbol> dummyStack = commonStack;
    std::vector<Symbol> dummyVector;
    dummyVector.clear();
    while (dummyStack.size() > 0) {
        dummyVector.push_back(dummyStack.top()); dummyStack.pop();
    }
    // std::reverse(dummyVector.begin(), dummyVector.end());
    for (int i = dummyVector.size() - 1; i >= 0; i--)
        std::cout << "'" << dummyVector[i].str << "'  ";
    
    std::cout << "]\n";
}
void pTokens() {
    std::cout << "Tokens: [";
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << tokens[i].str << "  ";
    }
    std::cout << "]\n";
}

// Придется создать здесь класс дерева. В очередной раз.
class Node {
public:
    Node(Symbol t, Node* p) : data(t), parent(p) {};
    ~Node();
    
    Symbol data;
    Node* parent;
    std::vector<Node*> children;
};

Node::~Node() {
    while (children.size() > 0) {
        delete children[0];
        children[0] = NULL;
        children.erase(children.begin());
    }
}

// Функция, определяющая по токену, является ли он терминалом или нет.
bool isTokenTerm (token_t t) {
    return (t == _ID || t == _NUM || t == _STR || t == _PROG || t == _CONST || t == _INT || t == _REAL || t == _STRING || t == _GOTO || t == _WHILE || t == _IF || t == _THEN || t == _ELSE || t == _READ || t == _WRITE || t == _TRUE || t == _FALSE || t == _BOOL || t == _DO || t == _CHAR || t == _BEGIN || t == _END || t == _VAR || t == _LABEL || t == _CONC || t == _LEN || t == _REPL || t == _SUBS || t == _SRCH || t == _FUNC || t == _OPER || t == _NEWW || t == _L || t == _N || t == _PLUS || t == _MINUS || t == _MULT || t == _DIV || t == _NOT || t == _AND || t == _OR || t == _REL || t == _EQ || t == _DOT || t == _OBRACK || t == _CBRACK || t == _SEMCOL || t == _COLUM || t == _COMMA || t == _RC || t == _CC || t == _EPS);
}

// Функция ищет самый правый нетерминал без детей.
Node* findRightestNonTerm(Node* n) {
    // Если есть дети, смотрим их справа-налево
    if (n->children.size() > 0) {
        for (int i = n->children.size() - 1; i >= 0; i--) {
            Node* r = findRightestNonTerm(n->children[i]);
            if (r) return r;
        }
        return NULL;
    }
    // Иначе, если детишек нет и текущий узел - нетерминал, возвращаем его
    else if (!n->data.isToken) {
        return n;
    }
    // Иначе, если детишек нет и текущий узел - терминал, возвращаем NULL.
    else {
        return NULL;
    }
}

#define TAB_WIDTH 8
void printTab(int count, char c) {
    for (int k = 0; k < count; ++k) {
        std::cout << c;
    }
}

void printDash(int count) {
    for (int k = 0; k < count; ++k) {
        printf("─");
    }
}

void printPerp() {
    //putchar(0xC3);
    //putwchar(0x251C);
    //char block[] = { 0xe2, 0x94, 0x9C, '\0' };
    //printf("%s", block);
    printf("├");
}

void printPipe() {
    //putchar(0xB3);
    //putwchar(0x2502);
    //char block[] = { 0xe2, 0x94, 0x82, '\0' };
    //printf("%s", block);
    printf("│");
}

void printCurv() {
    //putchar(0xC0);
    //putwchar(0x2570);
    //char block[] = { 0xe2, 0x95, 0xBF, '\0' };
    //printf("%s", block);
    printf("╰");
}

unsigned int pipes;
int tabs;
void showNode(Node* n, bool isLastChild) {

    if (tabs > 0) {
        if (!isLastChild) {
            pipes |= (unsigned int)(1 << (tabs - 1));
        }
        else {
            pipes &= ~((unsigned int)(1 << (tabs - 1)));
        }
    }

    // Печатаем отступ до себя
    for (int k = 0; k < tabs - 1; ++k) {
        if (pipes & (unsigned int)(1 << k)) {
            printPipe();
            printTab(TAB_WIDTH - 1, ' ');
        }
        else {
            printTab(TAB_WIDTH, ' ');
        }
    }
    // Если это не корневой узел, печатаем разветвление
    if (tabs > 0) {
        // Если это последний ребенок родителя, печатаем └
        if (isLastChild) {
            printCurv();
        }
        // Иначе печатаем ├
        else {
            printPerp();
        }
        printDash(TAB_WIDTH - 1);
    }
    // Печатаем себя
    std::cout << n->data.str;
    // Переходим на следующую строку
    std::cout << std::endl;
    // Если есть детишки, печатаем их.
    if (!n->children.empty()) {
        tabs++;
        for (int i = 0; i < n->children.size(); i++) {
            showNode(n->children[i], bool(i == n->children.size() - 1));
        }
        tabs--;
    }
    
}
void treeToString(Node* root) {
    tabs = 0;
    pipes = 1;
    return showNode(root, false);
}

void pOutFoldRules() {
    std::cout << "Fold Rules: [";
    for (int i = 0; i < outFoldRules.size(); i++) {
        std::cout << "(g=" << outFoldRules[i].gNum << ", r=" << outFoldRules[i].rNum << ") ";
    }
    std::cout << "]\n";
    
    // Print in tree view
    // Create tree
    // При построении дерева по правилам свертки, каждое очередное правило разворачивает
    // самый правый нетерминал в дереве.
    Symbol tmp_s (PROG, pTT(PROG).c_str(), isTokenTerm(PROG));
    Node* root = new Node(tmp_s, NULL);
    // Обходим правила свертки в обратном порядке
    for (int i = outFoldRules.size() - 1; i >= 0; i--) {
        // Берем правило свертки
        OutFoldRule ofr = outFoldRules[i];
        // Берем грамматику
        Gramm& g = grams[ofr.gNum];
        // Берем правило из грамматики
        std::vector<token_t>& r = g.rules[ofr.rNum];
        // Находим самый правый нетерминал в существующем дереве
        Node* n = findRightestNonTerm(root);
        // Нашли
        if (n) {
            // Раскрываем этот нетерминал, добавляя ему детишек
            for (int j = 1; j < r.size(); j++) {
                Symbol s (r[j], pTT(r[j]).c_str(), isTokenTerm(r[j]));
                if (r[j] == _ID || r[j] == _NUM || r[j] == _RC || r[j] == _REL) {
                    s.str = ofr.symbols[j].str;
                }
                Node* ch = new Node(s, n);
                n->children.push_back(ch);
            }
        }
        // Если не нашли, то построение дерева закончено и цикл завершится сам собой.
    }
    
    // Теперь напечатаем дерево.
    treeToString(root);
    std::cout << std::endl;
}

int doTransRule(CurGram cg, Symbol s) {
    std::cout << "doTransRule(cg.id=" << cg.id << ", Symbol s = " << pTT(s.id) << ")\n";
    Gramm& g = grams[cg.id];
    
    // If there are two nonterminals in common stack together.
    if (commonStack.size() >= 2) {
        Symbol s1 = commonStack.top();
        commonStack.pop();
        Symbol s2 = commonStack.top();
        commonStack.push(s1);
        if (s1.isToken == false && s2.isToken == false && s2.id != _HASH) return 2;
    }
    
    for (int i = 0; i < g.transRules.size(); i++) {
        TransRule& tr = g.transRules[i];
        if (tr.input == s.id) {
            if (commonStack.size() - cg.firstElemInCS >= tr.inStack.size()) {
                
                bool isEqual = true;
                
                if (tr.inStack.size() == 2 && tr.inStack[1] == _C) {
                    if (commonStack.top().isToken && tr.inStack[0] != commonStack.top().id) {
                        isEqual = false;
                    }
                    if (!commonStack.top().isToken) {
                        std::stack<Symbol> dummyStack = commonStack;
                        dummyStack.pop();
                        if (dummyStack.top().id != tr.inStack[0])
                            isEqual = false;
                    }
                }
                else {
                    std::stack<Symbol> dummyStack = commonStack;
                    std::vector<Symbol> dummyVector;
                    for (int j = 0; j < tr.inStack.size(); j++) {
                        dummyVector.push_back(dummyStack.top()); dummyStack.pop();
                    }
                    std::reverse(dummyVector.begin(), dummyVector.end());
                    for (int j = 0; j < tr.inStack.size(); j++) {
                        if (tr.inStack[j] != dummyVector[j].id) {
                            isEqual = false; break;
                        }
                    }
                }
                
                if (isEqual) {
                    if (tr.rule == _S) {
                        std::cout << ">> _S\n";
                        tokens.erase(tokens.begin());
                        commonStack.push(s);
                    }
                    else if (tr.rule == _A) {
                        std::cout << ">> _A\n";
                        if (gramsStack.size() == 1) {
                            gramsStack.pop();
                        }
                        else {
                            commonStack.pop();
                            commonStack.pop();
                            gramsStack.pop();
                            Gramm& tg = grams[gramsStack.top().id];
                            std::string stri = pTT(tg.startNonTerm);
                            Symbol ns (tg.startNonTerm, stri, 0);
                            commonStack.push(ns);
                        }
                    }
                    else if (tr.rule == _R) {
                        std::cout << ">> _R\n";
						bool foldRuleFound = false;
                        for (int i = 0; i < g.foldRules.size(); i++) {
                            FoldRule& fr = g.foldRules[i];
                            // std::cout << ">>   commonStack.size() - cg.firstElemInCS = " << (commonStack.size() - cg.firstElemInCS) << "; fr.inStack.size() = " << fr.inStack.size() << std::endl;
                            if (commonStack.size() - cg.firstElemInCS >= fr.inStack.size()) {
                                std::stack<Symbol> dummyStack = commonStack;
                                std::vector<Symbol> dummyVector;
                                for (int j = 0; j < fr.inStack.size(); j++) {
                                    dummyVector.push_back(dummyStack.top()); dummyStack.pop();
                                }
                                std::reverse(dummyVector.begin(), dummyVector.end());
                                
                                bool isEqual = true;
                                
                                for (int j = 0; j < fr.inStack.size(); j++) {
                                    if (dummyVector[j].id != fr.inStack[j]) {
                                        isEqual = false; break;
                                    }
                                }
                                
                                if (isEqual) {
									foldRuleFound = true;
                                    for (int i = 0; i < fr.inStack.size() - 1; i++) {
                                        commonStack.pop();
                                    }
                                    std::string stri = pTT(g.startNonTerm);
                                    Symbol ns (g.startNonTerm, stri, 0);
                                    commonStack.push(ns);
                                    
                                    OutFoldRule ofr (g.id, fr.ruleNum);
                                    ofr.symbols = dummyVector;
                                    outFoldRules.push_back(ofr);
                                    std::cout << ">> Compare common stack and fr.inStack:\n";
                                    for (int j = 0; j < fr.inStack.size(); j++) {
                                        std::cout << "  " << j << ") " << pTT(dummyVector[j].id) <<
                                            "\t" << pTT(fr.inStack[j]) << std::endl;
                                    }
                                    std::cout << ">> Add OutFoldRule: g.id = " << g.id << ", rNum = " <<
                                        fr.ruleNum << std::endl;
                                    
                                    break;
                                }
                            }
                        }
						// Если не найдены правила свертки
						if (!foldRuleFound) {
                            std::cout << "    foldRuleFound IS FALSE !!!\n";
                            return 2;
                        }
                    }
                    else if (tr.rule == _E) {
                        return 2;
                    }
                    
                    return 1;
                }
                
                
                
            }
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printHelp();
    }
    std::cout << "1\n";
    initGrams();
    std::cout << "2\n";
    std::ifstream in (argv[1]);
    if (!in.is_open()) {
        std::cout << "Cannot open " << argv[1] << ".\n";
		return 0;
    }
    
    acc.clear();
    // Current char
    char c;
    // Current state
    state_t s = S_START;
    while (!in.eof()) {
        if (s == S_ERROR) {
            std::cout << "Error occured while lexical analize\n";
            break;
        }
        c = in.get();
        //std::cout << c;
        acc.push_back(c);
        switch(s) {
            case S_START:
                if      (c == 'A' || c == 'a') { s = S_150; }
                else if (c == 'B' || c == 'b') { s = S_B; }
                else if (c == 'C' || c == 'c') { s = S_C; }
                else if (c == 'D' || c == 'd') { s = S_73; }
                else if (c == 'E' || c == 'e') { s = S_E; }
                else if (c == 'F' || c == 'f') { s = S_F; }
                else if (c == 'G' || c == 'g') { s = S_30; }
                else if (c == 'I' || c == 'i') { s = S_I; }
                else if (c == 'L' || c == 'l') { s = S_L; }
                else if (c == 'N' || c == 'n') { s = S_N; }
                else if (c == 'O' || c == 'o') { s = S_O; }
                else if (c == 'P' || c == 'p') { s = S_1; }
                else if (c == 'R' || c == 'r') { s = S_R; }
                else if (c == 'S' || c == 's') { s = S_S; }
                else if (c == 'T' || c == 't') { s = S_T; }
                else if (c == 'V' || c == 'v') { s = S_87; }
                else if (c == 'W' || c == 'w') { s = S_W; }
                else if (c == ':') { s = S_153; }
                else if (c == '<') { s = S_155; }
                else if (c == '=') { s = S_157; }
                else if (c == '>') { s = S_158; }
                else if (c == '\'') { s = S_163; }
                else if (isNum(c)) { s = S_168; }
                else if (isSpace(c)) { s = S_START; acc.clear(); }
                else if (c == 'H' || c == 'h' || c == 'J' || c == 'j' ||
                         c == 'K' || c == 'k' || c == 'M' || c == 'm' ||
                         c == 'Q' || c == 'q' || c == 'U' || c == 'u' ||
                         c == 'X' || c == 'x' || c == 'Y' || c == 'y' ||
                         c == 'Z' || c == 'z') { s = S_160; }
                else if (c == '+' || c == '-' || c == '*' || c == '/' ||
                         c == ';' || c == ',' || c == '.' || c == '(' ||
                         c == ')') { savePunct(c); s = S_START; }
                else if (c == EOF) { s = S_START; }
                else { unrecErr(c); } break;
                
            case S_150:
                if      (c == 'N' || c == 'n') { s = S_151; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_151:
                if      (c == 'D' || c == 'd') { s = S_152; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_152:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveAnd(); in.putback(c); s = S_START; } break;
                
            case S_B:
                if      (c == 'O' || c == 'o') { s = S_67; }
                else if (c == 'E' || c == 'e') { s = S_80; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_67:
                if      (c == 'O' || c == 'o') { s = S_68; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_68:
                if      (c == 'L' || c == 'l') { s = S_69; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_69:
                if      (c == 'E' || c == 'e') { s = S_70; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_70:
                if      (c == 'A' || c == 'a') { s = S_71; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_71:
                if      (c == 'N' || c == 'n') { s = S_72; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_72:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveBoolean(); in.putback(c); s = S_START; } break;
                
            case S_80:
                if      (c == 'G' || c == 'g') { s = S_81; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_81:
                if      (c == 'I' || c == 'i') { s = S_82; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_82:
                if      (c == 'N' || c == 'n') { s = S_83; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_83:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveBegin(); in.putback(c); s = S_START; } break;
            
            case S_C:
                if      (c == 'H' || c == 'h') { s = S_76; }
                else if (c == 'O' || c == 'o') { s = S_CO; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_76:
                if      (c == 'A' || c == 'a') { s = S_77; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_77:
                if      (c == 'R' || c == 'r') { s = S_78; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_78:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveChar(); in.putback(c); s = S_START; } break;
            
            case S_CO:
                if      (c == 'N' || c == 'n') { s = S_CON; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_CON:
                if      (c == 'C' || c == 'c') { s = S_98; }
                else if (c == 'S' || c == 's') { s = S_11; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_98:
                if      (c == 'A' || c == 'a') { s = S_99; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_99:
                if      (c == 'T' || c == 't') { s = S_100; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_100:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveConcat(); in.putback(c); s = S_START; } break;
            case S_11:
                if      (c == 'T' || c == 't') { s = S_12; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_12:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveConst(); in.putback(c); s = S_START; } break;
            
            case S_73:
                if      (c == 'O' || c == 'o') { s = S_74; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_74:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveDo(); in.putback(c); s = S_START; } break;
            
            case S_E:
                if      (c == 'L' || c == 'l') { s = S_46; }
                else if (c == 'N' || c == 'n') { s = S_85; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_46:
                if      (c == 'S' || c == 's') { s = S_47; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_47:
                if      (c == 'E' || c == 'e') { s = S_48; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_48:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveElse(); in.putback(c); s = S_START; } break;
            
            case S_85:
                if      (c == 'D' || c == 'd') { s = S_86; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_86:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveEnd(); in.putback(c); s = S_START; } break;
            
            case S_F:
                if      (c == 'A' || c == 'a') { s = S_62; }
                else if (c == 'U' || c == 'u') { s = S_127; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_62:
                if      (c == 'L' || c == 'l') { s = S_63; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_63:
                if      (c == 'S' || c == 's') { s = S_64; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_64:
                if      (c == 'E' || c == 'e') { s = S_65; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_65:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveFalse(); in.putback(c); s = S_START; } break;
            
            case S_127:
                if      (c == 'N' || c == 'n') { s = S_128; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_128:
                if      (c == 'C' || c == 'c') { s = S_129; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_129:
                if      (c == 'T' || c == 't') { s = S_130; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_130:
                if      (c == 'I' || c == 'i') { s = S_131; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_131:
                if      (c == 'O' || c == 'o') { s = S_132; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_132:
                if      (c == 'N' || c == 'n') { s = S_133; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_133:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveFunction(); in.putback(c); s = S_START; } break;
            
            case S_30:
                if      (c == 'O' || c == 'o') { s = S_31; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_31:
                if      (c == 'T' || c == 't') { s = S_32; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_32:
                if      (c == 'O' || c == 'o') { s = S_33; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_33:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveGoto(); in.putback(c); s = S_START; } break;
            
            case S_I:
                if      (c == 'F' || c == 'f') { s = S_40; }
                else if (c == 'N' || c == 'n') { s = S_14; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_40:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveIf(); in.putback(c); s = S_START; } break;
            
            case S_14:
                if      (c == 'T' || c == 't') { s = S_15; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_15:
                if      (c == 'E' || c == 'e') { s = S_16; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_16:
                if      (c == 'G' || c == 'g') { s = S_17; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_17:
                if      (c == 'E' || c == 'e') { s = S_18; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_18:
                if      (c == 'R' || c == 'r') { s = S_19; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_19:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveInteger(); in.putback(c); s = S_START; } break;
            
            case S_L:
                if      (c == 'A' || c == 'a') { s = S_91; }
                else if (c == 'E' || c == 'e') { s = S_102; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_91:
                if      (c == 'B' || c == 'b') { s = S_92; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_92:
                if      (c == 'E' || c == 'e') { s = S_93; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_93:
                if      (c == 'L' || c == 'l') { s = S_94; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_94:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveLabel(); in.putback(c); s = S_START; } break;
            
            case S_102:
                if      (c == 'N' || c == 'n') { s = S_103; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_103:
                if      (c == 'G' || c == 'g') { s = S_104; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_104:
                if      (c == 'T' || c == 't') { s = S_105; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_105:
                if      (c == 'H' || c == 'h') { s = S_106; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_106:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveLength(); in.putback(c); s = S_START; } break;
            
            case S_N:
                if      (c == 'E' || c == 'e') { s = S_143; }
                else if (c == 'O' || c == 'o') { s = S_146; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_143:
                if      (c == 'W' || c == 'w') { s = S_144; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_144:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveNew(); in.putback(c); s = S_START; } break;
            
            case S_146:
                if      (c == 'T' || c == 't') { s = S_147; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_147:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveNot(); in.putback(c); s = S_START; } break;
            
            case S_O:
                if      (c == 'P' || c == 'p') { s = S_135; }
                else if (c == 'R' || c == 'r') { s = S_149; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_135:
                if      (c == 'E' || c == 'e') { s = S_136; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_136:
                if      (c == 'R' || c == 'r') { s = S_137; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_137:
                if      (c == 'A' || c == 'a') { s = S_138; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_138:
                if      (c == 'T' || c == 't') { s = S_139; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_139:
                if      (c == 'O' || c == 'o') { s = S_140; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_140:
                if      (c == 'R' || c == 'r') { s = S_141; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_141:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveOperator(); in.putback(c); s = S_START; } break;
            
            case S_149:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveOr(); in.putback(c); s = S_START; } break;
            
            case S_1:
                if      (c == 'R' || c == 'r') { s = S_2; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_2:
                if      (c == 'O' || c == 'o') { s = S_3; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_3:
                if      (c == 'G' || c == 'g') { s = S_4; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_4:
                if      (c == 'R' || c == 'r') { s = S_5; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_5:
                if      (c == 'A' || c == 'a') { s = S_6; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_6:
                if      (c == 'M' || c == 'm') { s = S_7; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_7:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveProgram(); in.putback(c); s = S_START; } break;
            
            case S_R:
                if      (c == 'E' || c == 'e') { s = S_RE; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_RE:
                if      (c == 'A' || c == 'a') { s = S_REA; }
                else if (c == 'P' || c == 'p') { s = S_109; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_REA:
                if      (c == 'D' || c == 'd') { s = S_52; }
                else if (c == 'L' || c == 'l') { s = S_23; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_52:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveRead(); in.putback(c); s = S_START; } break;
            
            case S_23:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveReal(); in.putback(c); s = S_START; } break;
            
            case S_109:
                if      (c == 'L' || c == 'l') { s = S_110; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_110:
                if      (c == 'A' || c == 'a') { s = S_111; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_111:
                if      (c == 'C' || c == 'c') { s = S_112; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_112:
                if      (c == 'E' || c == 'e') { s = S_113; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_113:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveReplace(); in.putback(c); s = S_START; } break;
            
            case S_S:
                if      (c == 'T' || c == 't') { s = S_25; }
                else if (c == 'U' || c == 'u') { s = S_115; }
                else if (c == 'E' || c == 'e') { s = S_121; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_25:
                if      (c == 'R' || c == 'r') { s = S_26; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_26:
                if      (c == 'I' || c == 'i') { s = S_27; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_27:
                if      (c == 'N' || c == 'n') { s = S_28; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_28:
                if      (c == 'G' || c == 'g') { s = S_29; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_29:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveString(); in.putback(c); s = S_START; } break;
            
            case S_115:
                if      (c == 'B' || c == 'b') { s = S_116; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_116:
                if      (c == 'S' || c == 's') { s = S_117; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_117:
                if      (c == 'T' || c == 't') { s = S_118; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_118:
                if      (c == 'R' || c == 'r') { s = S_119; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_119:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveSubstr(); in.putback(c); s = S_START; } break;
            
            case S_121:
                if      (c == 'A' || c == 'a') { s = S_122; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_122:
                if      (c == 'R' || c == 'r') { s = S_123; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_123:
                if      (c == 'C' || c == 'c') { s = S_124; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_124:
                if      (c == 'H' || c == 'h') { s = S_125; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_125:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveSearch(); in.putback(c); s = S_START; } break;
            
            case S_T:
                if      (c == 'R' || c == 'r') { s = S_58; }
                else if (c == 'H' || c == 'h') { s = S_42; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_58:
                if      (c == 'U' || c == 'u') { s = S_59; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_59:
                if      (c == 'E' || c == 'e') { s = S_60; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_60:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveTrue(); in.putback(c); s = S_START; } break;
            
            case S_42:
                if      (c == 'E' || c == 'e') { s = S_43; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_43:
                if      (c == 'N' || c == 'n') { s = S_44; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_44:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveThen(); in.putback(c); s = S_START; } break;
            
            case S_W:
                if      (c == 'R' || c == 'r') { s = S_54; }
                else if (c == 'H' || c == 'h') { s = S_35; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_54:
                if      (c == 'I' || c == 'i') { s = S_55; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_55:
                if      (c == 'T' || c == 't') { s = S_56; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_56:
                if      (c == 'E' || c == 'e') { s = S_57; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_57:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveWrite(); in.putback(c); s = S_START; } break;
            
            case S_35:
                if      (c == 'I' || c == 'i') { s = S_36; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_36:
                if      (c == 'L' || c == 'l') { s = S_37; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_37:
                if      (c == 'E' || c == 'e') { s = S_38; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_38:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveWhile(); in.putback(c); s = S_START; } break;
            
            case S_153:
                if      (c == '=') { s = S_154; }
                else { saveColumn(); in.putback(c); s = S_START; } break;
            case S_154:
                saveEq(); in.putback(c); s = S_START; break;
            
            case S_155:
                if      (c == '>') { s = S_156; }
                else if (c == '=') { s = S_201; }
                else { saveLess(); in.putback(c); s = S_START; } break;
            case S_156:
                saveNotEqual(); in.putback(c); s = S_START; break;
            case S_201:
                saveLessEqual(); in.putback(c); s = S_START; break;
            
            case S_157:
                saveEqual(); in.putback(c); s = S_START; break;
            
            case S_158:
                if      (c == '=') { s = S_200; }
                else { saveGreater(); in.putback(c); s = S_START; } break;
            
            case S_200:
                saveGreaterEqual(); in.putback(c); s = S_START; break;
            
            case S_168:
                if      (isNum(c)) { s = S_168; }
                else if (c == '.') { s = S_169; }
                else { saveNum(); in.putback(c); s = S_START; } break;
            case S_169:
                if      (isNum(c)) { s = S_169; }
                else if (c == 'E' || c == 'e') { s = S_170; }
                else { saveRc(); in.putback(c); s = S_START; } break;
            case S_170:
                if      (isNum(c)) { s = S_172; }
                else if (c == '+' || c == '-') { s = S_171; }
                else { unrecErr(c); in.putback(c); s = S_ERROR; } break;
            case S_171:
                if      (isNum(c)) { s = S_172; }
                else { unrecErr(c); in.putback(c); s = S_ERROR; } break;
            case S_172:
                if      (isNum(c)) { s = S_172; }
                else { saveRc(); in.putback(c); s = S_START; } break;
            
            case S_163:
                if (c == '\'') { s = S_166; }
                else { s = S_164; } break;
            case S_164:
                if (c == '\'') { s = S_166; }
                else { s = S_165; } break;
            case S_165:
                if (c == '\'') { s = S_167; }
                else { s = S_165; } break;
            case S_167:
                saveStr(); in.putback(c); s = S_START; break;
            
            case S_160:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            
            case S_87:
                if      (c == 'A' || c == 'a') { s = S_88; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_88:
                if      (c == 'R' || c == 'r') { s = S_89; }
                else if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveCurrentId(); in.putback(c); s = S_START; } break;
            case S_89:
                if (isNum(c) || isLetter(c)) { s = S_160; }
                else { saveVar(); in.putback(c); s = S_START; } break;
                
            default:
                unrecErr(c);
                break;
        }
    }
   
    std::cout << "\n\nLexical analize complete\n";

    std::cout << "\n\nSyntactical analize ...\n";
    
	// Epsilon Symbol
    Symbol epsSymbol (_EPS, "$", 1);
    tokens.push_back(epsSymbol);
    //Hash Symbol
	Symbol hashSymbol (_HASH, "#", 0);
    // Start gram
    CurGram cg (0, 0);
	// 
	bool success = true;
	// Current token
    token_t ct;
	// 
	int ing;
	
	
	pTokens();
    
    
    // Start from G0
    gramsStack.push(cg);
    // Gramm& g = grams[cg.id];
	// Put hash in stack (CS)
    commonStack.push(hashSymbol);
    
	
	
    // int ing = findTokenInGramWide(cg.id, ct);
    // int ing = findTokenInGram(cg.id, ct);
    // cg = gramsStack.top();
    
    // doTransRule(cg, tokens[0]);
    
    int i = 25;
    while (gramsStack.size() > 0 /* && i > 0 */) {
		i --;
	
		// Print info
        pGramStack();
        pCommonStack();
        pTokens();
        //pOutFoldRules();
		
        ct = tokens[0].id;
        cg = gramsStack.top();
        ing = findTokenInGram(cg.id, ct);
		
		if (ing == -1) { // Надо делать свертку
            if (doTransRule(cg, epsSymbol) == 2) {
                success = false; break;
            }
        }
		else if (cg.id == ing) { // Токен в текущей грамматике
			if (doTransRule(cg, tokens[0]) == 2) {
                success = false; break;
            }
		}
		else {
			commonStack.push(hashSymbol);
            cg.id = ing;
			cg.firstElemInCS = commonStack.size() - 1;
            gramsStack.push(cg);
		}
        
    }
    
    if (success) {
        std::cout << "Sentence analysis is complete successfuly.\n";
        pGramStack();
        pCommonStack();
        pTokens();

        pOutFoldRules();
    }
    else {
        std::cout << "Sentence analysis is not complete successfuly.\n";
    }
    
    return 0;
}
