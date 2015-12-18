// Tokens
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
    _C, _HASH,
    // Для триад
    _OLD
} token_t;

std::string pTT(token_t t) {if(t==_ID)return std::string("_ID");else if(t==_NUM)return std::string("_NUM");else if(t==_STR)return std::string("_STR");else if(t==_PROG)return std::string("_PROG");else if(t==_CONST)return std::string("_CONST");else if(t==_INT)return std::string("_INT");else if(t==_REAL)return std::string("_REAL");else if(t==_STRING)return std::string("_STRING");else if(t==_GOTO)return std::string("_GOTO");else if(t==_WHILE)return std::string("_WHILE");else if(t==_IF)return std::string("_IF");else if(t==_THEN)return std::string("_THEN");else if(t==_ELSE)return std::string("_ELSE");else if(t==_READ)return std::string("_READ");else if(t==_WRITE)return std::string("_WRITE");else if(t==_TRUE)return std::string("_TRUE");else if(t==_FALSE)return std::string("_FALSE");else if(t==_BOOL)return std::string("_BOOL");else if(t==_DO)return std::string("_DO");else if(t==_CHAR)return std::string("_CHAR");else if(t==_BEGIN)return std::string("_BEGIN");else if(t==_END)return std::string("_END");else if(t==_VAR)return std::string("_VAR");else if(t==_LABEL)return std::string("_LABEL");else if(t==_CONC)return std::string("_CONC");else if(t==_LEN)return std::string("_LEN");else if(t==_REPL)return std::string("_REPL");else if(t==_SUBS)return std::string("_SUBS");else if(t==_SRCH)return std::string("_SRCH");else if(t==_FUNC)return std::string("_FUNC");else if(t==_OPER)return std::string("_OPER");else if(t==_NEWW)return std::string("_NEWW");else if(t==_L)return std::string("_L");else if(t==_N)return std::string("_N");else if(t==_PLUS)return std::string("_PLUS");else if(t==_MINUS)return std::string("_MINUS");else if(t==_MULT)return std::string("_MULT");else if(t==_DIV)return std::string("_DIV");else if(t==_NOT)return std::string("_NOT");else if(t==_AND)return std::string("_AND");else if(t==_OR)return std::string("_OR");else if(t==_REL)return std::string("_REL");else if(t==_EQ)return std::string("_EQ");else if(t==_DOT)return std::string("_DOT");else if(t==_OBRACK)return std::string("_OBRACK");else if(t==_CBRACK)return std::string("_CBRACK");else if(t==_SEMCOL)return std::string("_SEMCOL");else if(t==_COLUM)return std::string("_COLUM");else if(t==_COMMA)return std::string("_COMMA");else if(t==_RC)return std::string("_RC");else if(t==_CC)return std::string("_CC");else if(t==_EPS)return std::string("_EPS");else if(t==PROG)return std::string("PROG");else if(t==VARS)return std::string("VARS");else if(t==VAR)return std::string("VAR");else if(t==CONSTS)return std::string("CONSTS");else if(t==CONST)return std::string("CONST");else if(t==LABELS)return std::string("LABELS");else if(t==TYPE)return std::string("TYPE");else if(t==ID)return std::string("ID");else if(t==L)return std::string("L");else if(t==N)return std::string("N");else if(t==AEXP)return std::string("AEXP");else if(t==TERM)return std::string("TERM");else if(t==MULT)return std::string("MULT");else if(t==SIGN)return std::string("SIGN");else if(t==LEXP)return std::string("LEXP");else if(t==LTERM)return std::string("LTERM");else if(t==LMULT)return std::string("LMULT");else if(t==REL)return std::string("REL");else if(t==C)return std::string("C");else if(t==DEC)return std::string("DEC");else if(t==NN)return std::string("NN");else if(t==RC)return std::string("RC");else if(t==DC)return std::string("DC");else if(t==EXP)return std::string("EXP");else if(t==CC)return std::string("CC");else if(t==BC)return std::string("BC");else if(t==SC)return std::string("SC");else if(t==NLN)return std::string("NLN");else if(t==OP)return std::string("OP");else if(t==UMOP)return std::string("UMOP");else if(t==AOP)return std::string("AOP");else if(t==GOP)return std::string("GOP");else if(t==WOP)return std::string("WOP");else if(t==MSG)return std::string("MSG");else if(t==ROP)return std::string("ROP");else if(t==COP)return std::string("COP");else if(t==IFOP)return std::string("IFOP");else if(t==FOROP)return std::string("FOROP");else if(t==LENOP)return std::string("LENOP");else if(t==CONOP)return std::string("CONOP");else if(t==REPOP)return std::string("REPOP");else if(t==SEOP)return std::string("SEOP");else if(t==SUBOP)return std::string("SUBOP");else if(t==FUNOP)return std::string("FUNOP");else if(t==HFUN)return std::string("HFUN");else if(t==NEWOP)return std::string("NEWOP");else if(t==IFAOP)return std::string("IFAOP");else if(t==OPOP)return std::string("OPOP");else if(t==OVAR1)return std::string("OVAR1");else if(t==OVAR2)return std::string("OVAR2");else if(t==OVAR)return std::string("OVAR");else if(t==OOP)return std::string("OOP");else if(t==FUNCS)return std::string("FUNCS");else if(t==CLV)return std::string("CLV");else if(t==OPROG)return std::string("OPROG");else if(t==OCOP)return std::string("OCOP");else if(t==RVAR)return std::string("RVAR");else if(t==RID)return std::string("RID");else if(t==RCONST)return std::string("RCONST");else if(t==RLTERM)return std::string("RLTERM");else if(t==RECUROP)return std::string("RECUROP");else if(t==ALEXP)return std::string("ALEXP");else if(t==RMSG)return std::string("RMSG");else if(t==ZOMOP)return std::string("ZOMOP");else if(t==IDSC)return std::string("IDSC");else if(t==IDNN)return std::string("IDNN");else if(t==OEAOP)return std::string("OEAOP");else if(t==_C)return std::string("_C");else if(t==_HASH)return std::string("_HASH");}


void pT(token_t t) {if(t==_ID)std::cout << "_ID";else if(t==_NUM)std::cout << "_NUM";else if(t==_STR)std::cout << "_STR";else if(t==_PROG)std::cout << "_PROG";else if(t==_CONST)std::cout << "_CONST";else if(t==_INT)std::cout << "_INT";else if(t==_REAL)std::cout << "_REAL";else if(t==_STRING)std::cout << "_STRING";else if(t==_GOTO)std::cout << "_GOTO";else if(t==_WHILE)std::cout << "_WHILE";else if(t==_IF)std::cout << "_IF";else if(t==_THEN)std::cout << "_THEN";else if(t==_ELSE)std::cout << "_ELSE";else if(t==_READ)std::cout << "_READ";else if(t==_WRITE)std::cout << "_WRITE";else if(t==_TRUE)std::cout << "_TRUE";else if(t==_FALSE)std::cout << "_FALSE";else if(t==_BOOL)std::cout << "_BOOL";else if(t==_DO)std::cout << "_DO";else if(t==_CHAR)std::cout << "_CHAR";else if(t==_BEGIN)std::cout << "_BEGIN";else if(t==_END)std::cout << "_END";else if(t==_VAR)std::cout << "_VAR";else if(t==_LABEL)std::cout << "_LABEL";else if(t==_CONC)std::cout << "_CONC";else if(t==_LEN)std::cout << "_LEN";else if(t==_REPL)std::cout << "_REPL";else if(t==_SUBS)std::cout << "_SUBS";else if(t==_SRCH)std::cout << "_SRCH";else if(t==_FUNC)std::cout << "_FUNC";else if(t==_OPER)std::cout << "_OPER";else if(t==_NEWW)std::cout << "_NEWW";else if(t==_L)std::cout << "_L";else if(t==_N)std::cout << "_N";else if(t==_PLUS)std::cout << "_PLUS";else if(t==_MINUS)std::cout << "_MINUS";else if(t==_MULT)std::cout << "_MULT";else if(t==_DIV)std::cout << "_DIV";else if(t==_NOT)std::cout << "_NOT";else if(t==_AND)std::cout << "_AND";else if(t==_OR)std::cout << "_OR";else if(t==_REL)std::cout << "_REL";else if(t==_EQ)std::cout << "_EQ";else if(t==_DOT)std::cout << "_DOT";else if(t==_OBRACK)std::cout << "_OBRACK";else if(t==_CBRACK)std::cout << "_CBRACK";else if(t==_SEMCOL)std::cout << "_SEMCOL";else if(t==_COLUM)std::cout << "_COLUM";else if(t==_COMMA)std::cout << "_COMMA";else if(t==_RC)std::cout << "_RC";else if(t==_CC)std::cout << "_CC";else if(t==_EPS)std::cout << "_EPS";else if(t==PROG)std::cout << "PROG";else if(t==VARS)std::cout << "VARS";else if(t==VAR)std::cout << "VAR";else if(t==CONSTS)std::cout << "CONSTS";else if(t==CONST)std::cout << "CONST";else if(t==LABELS)std::cout << "LABELS";else if(t==TYPE)std::cout << "TYPE";else if(t==ID)std::cout << "ID";else if(t==L)std::cout << "L";else if(t==N)std::cout << "N";else if(t==AEXP)std::cout << "AEXP";else if(t==TERM)std::cout << "TERM";else if(t==MULT)std::cout << "MULT";else if(t==SIGN)std::cout << "SIGN";else if(t==LEXP)std::cout << "LEXP";else if(t==LTERM)std::cout << "LTERM";else if(t==LMULT)std::cout << "LMULT";else if(t==REL)std::cout << "REL";else if(t==C)std::cout << "C";else if(t==DEC)std::cout << "DEC";else if(t==NN)std::cout << "NN";else if(t==RC)std::cout << "RC";else if(t==DC)std::cout << "DC";else if(t==EXP)std::cout << "EXP";else if(t==CC)std::cout << "CC";else if(t==BC)std::cout << "BC";else if(t==SC)std::cout << "SC";else if(t==NLN)std::cout << "NLN";else if(t==OP)std::cout << "OP";else if(t==UMOP)std::cout << "UMOP";else if(t==AOP)std::cout << "AOP";else if(t==GOP)std::cout << "GOP";else if(t==WOP)std::cout << "WOP";else if(t==MSG)std::cout << "MSG";else if(t==ROP)std::cout << "ROP";else if(t==COP)std::cout << "COP";else if(t==IFOP)std::cout << "IFOP";else if(t==FOROP)std::cout << "FOROP";else if(t==LENOP)std::cout << "LENOP";else if(t==CONOP)std::cout << "CONOP";else if(t==REPOP)std::cout << "REPOP";else if(t==SEOP)std::cout << "SEOP";else if(t==SUBOP)std::cout << "SUBOP";else if(t==FUNOP)std::cout << "FUNOP";else if(t==HFUN)std::cout << "HFUN";else if(t==NEWOP)std::cout << "NEWOP";else if(t==IFAOP)std::cout << "IFAOP";else if(t==OPOP)std::cout << "OPOP";else if(t==OVAR1)std::cout << "OVAR1";else if(t==OVAR2)std::cout << "OVAR2";else if(t==OVAR)std::cout << "OVAR";else if(t==OOP)std::cout << "OOP";else if(t==FUNCS)std::cout << "FUNCS";else if(t==CLV)std::cout << "CLV";else if(t==OPROG)std::cout << "OPROG";else if(t==OCOP)std::cout << "OCOP";else if(t==RVAR)std::cout << "RVAR";else if(t==RID)std::cout << "RID";else if(t==RCONST)std::cout << "RCONST";else if(t==RLTERM)std::cout << "RLTERM";else if(t==RECUROP)std::cout << "RECUROP";else if(t==ALEXP)std::cout << "ALEXP";else if(t==RMSG)std::cout << "RMSG";else if(t==ZOMOP)std::cout << "ZOMOP";else if(t==IDSC)std::cout << "IDSC";else if(t==IDNN)std::cout << "IDNN";else if(t==OEAOP)std::cout << "OEAOP";else if(t==_C)std::cout << "_C";else if(t==_HASH)std::cout << "_HASH";}
