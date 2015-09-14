sub  trim { my $s = shift; $s =~ s/^\s+|\s+$//g; return $s };

my $in =
"_ID, _NUM, _STR, _PROG, _CONST, _INT, _REAL, _STRING, _GOTO, _WHILE, _IF, _THEN, _ELSE, _READ, _WRITE, _TRUE, _FALSE, _BOOL, _DO, _CHAR, _BEGIN, _END, _VAR, _LABEL, _CONC, _LEN, _REPL, _SUBS, _SRCH, _FUNC, _OPER, _NEWW, _L, _N, _PLUS, _MINUS, _MULT, _DIV, _NOT, _AND, _OR, _REL, _EQ, _DOT, _OBRACK, _CBRACK, _SEMCOL, _COLUM, _COMMA, _RC, _CC, _EPS, PROG, VARS, VAR, CONSTS, CONST, LABELS, TYPE, ID, L, N, AEXP, TERM, MULT, SIGN, LEXP, LTERM, LMULT, REL, C, DEC, NN, RC, DC, EXP, CC, BC, SC, NLN, OP, UMOP, AOP, GOP, WOP, MSG, ROP, COP, IFOP, FOROP, LENOP, CONOP, REPOP, SEOP, SUBOP, FUNOP, HFUN, NEWOP, IFAOP, OPOP, OVAR1, OVAR2, OVAR, OOP, FUNCS, CLV, OPROG, OCOP, RVAR, RID, RCONST, RLTERM, RECUROP, ALEXP, RMSG, ZOMOP, IDSC, IDNN, OEAOP, _C, _HASH";

my $s = "std::string pTT(token_t t) {";

my @tokens = split /, /, $in;
foreach my $t (@tokens) {
    $s .= "else if(t==$t)return std::string(\"$t\");";
}

$s .= "}\n";
print $s;
