// Input token sequence (from lexical analizer).
std::vector<Symbol> tokens;

void pTokens() {
    std::cout << "Tokens: [";
    for (int i = 0; i < tokens.size(); i++) {
        std::cout << tokens[i].str << "  ";
    }
    std::cout << "]\n";
}

// Accumulator
std::deque<char> acc;

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

void lexicalAnalysis (std::ifstream &in) {
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
}
