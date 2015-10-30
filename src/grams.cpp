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
    token_t nonTerms[] = {AEXP, ID, LENOP, MULT, SEOP, TERM};
    token_t Terms[] = {_OBRACK, _CBRACK, _MULT, _PLUS, _MINUS, _DIV, _NUM, _RC};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 6);
    g.terms.insert(Terms, Terms + 8);
    g.startNonTerm = AEXP;
    g.rulesCount = 14;
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
	token_t r12t[] = {MULT, LENOP};
	token_t r13t[] = {MULT, SEOP};
    
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
    token_t nonTerms[] = {AOP, COP, FOROP, GOP, ID, IFAOP, IFOP, NEWOP, OP, ROP, UMOP, WOP};
    token_t Terms[] = {_COLUM};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 12);
    g.terms.insert(Terms, Terms + 1);
    g.startNonTerm = OP;
    g.rulesCount = 11;
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
    token_t r9t[] = {UMOP, NEWOP};
    token_t r10t[] = {UMOP, IFAOP};
    
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
    token_t nonTerms[] = {AEXP, ALEXP, AOP, C, CONOP, ID, LEXP, REPOP, SUBOP};
    token_t Terms[] = {_EQ};
    g.nonTerms.insert(g.nonTerms.begin(), nonTerms, nonTerms + 9);
    g.terms.insert(Terms, Terms + 1);
    g.startNonTerm = AOP;
    g.rulesCount = 7;
    g.rules = new std::vector<token_t> [g.rulesCount];
    token_t r0t[] = {AOP, ID, _EQ, ALEXP};
    token_t r1t[] = {ALEXP, C};
    token_t r2t[] = {ALEXP, AEXP};
    token_t r3t[] = {ALEXP, LEXP};
    token_t r4t[] = {ALEXP, CONOP};
    token_t r5t[] = {ALEXP, REPOP};
    token_t r6t[] = {ALEXP, SUBOP};
    
    std::vector<token_t> r0 (r0t, r0t + sizeof(r0t) / sizeof(token_t));
    std::vector<token_t> r1 (r1t, r1t + sizeof(r1t) / sizeof(token_t));
    std::vector<token_t> r2 (r2t, r2t + sizeof(r2t) / sizeof(token_t));
    std::vector<token_t> r3 (r3t, r3t + sizeof(r3t) / sizeof(token_t));
    std::vector<token_t> r4 (r4t, r4t + sizeof(r4t) / sizeof(token_t));
    std::vector<token_t> r5 (r5t, r5t + sizeof(r5t) / sizeof(token_t));
    std::vector<token_t> r6 (r6t, r6t + sizeof(r6t) / sizeof(token_t));
    
    g.rules[0] = r0;
    g.rules[1] = r1;
    g.rules[2] = r2;
    g.rules[3] = r3;
    g.rules[4] = r4;
    g.rules[5] = r5;
    g.rules[6] = r6;
    
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
