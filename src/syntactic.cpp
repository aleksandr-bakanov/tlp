
class OutFoldRule {
public:
    OutFoldRule(int g, int r) : gNum(g), rNum(r) {};
    int gNum;
    int rNum;
    std::vector<Symbol> symbols;
};

// Stack of fold rules and grams
std::vector<OutFoldRule> outFoldRules;

// Class current gramm
class CurGram {
public:
    CurGram (int i, int f) : id(i), firstElemInCS(f) {};
    // ID of Gramm
    int id;
    // Pointer of first element by gramm in common stack
    int firstElemInCS;
};

// Необходимая фигня, чтобы в функциях и перегрузках не влезать во второй блок begin .. end
bool forFuncAndOper;

// Common stack
std::stack<Symbol> commonStack;
// Stack of gramms
std::stack<CurGram> gramsStack;
// Output stack

// Vector for table of resource
std::vector<TableOfResource> tables;

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
//    std::cout << "findTokenInGram(gi=" << gi << ", t="; pT(t); std::cout  << ")" << std::endl;
    Gramm& g = grams[gi];
    // Если текущий символ есть в текущей грамматике, но возможно он принадлежит другой грамматике
    if (isTokenInGram(gi, t)) {
        // Возможно символ все-таки принадлежит не этой грамматике
        token_t nextT = tokens[1].id;
        switch(gi) {
            case 1:
                // Может надо проверять, что t == _SEMCOL ?
                if (t == _SEMCOL && (nextT == _BEGIN || nextT == _VAR || nextT == _CONST || nextT == _LABEL || nextT == _FUNC || nextT == _OPER)) return -1;
                break;
            case 2:
                if (t == _SEMCOL && (nextT == _BEGIN || nextT == _VAR || nextT == _CONST || nextT == _LABEL || nextT == _FUNC || nextT == _OPER)) return -1;
                break;
            case 3:
                if (t == _SEMCOL && (nextT == _BEGIN || nextT == _VAR || nextT == _CONST || nextT == _LABEL || nextT == _FUNC || nextT == _OPER)) return -1;
                break;
            case 4:
				if (t == _SEMCOL && (nextT == _BEGIN || nextT == _VAR || nextT == _CONST || nextT == _LABEL || nextT == _FUNC || nextT == _OPER) && forFuncAndOper) return -1;
				// if (t == _SEMCOL && commonStack.top().id == FUNCS) {
                    // Symbol s1 = commonStack.top();
                    // commonStack.pop();
                    // Symbol s2 = commonStack.top();
                    // commonStack.push(s1);
                    // if (s2.id == _SEMCOL || s2.id == _HASH) return -1;
                // }
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
            case 18:
                if (t == _CBRACK && commonStack.top().id == _CBRACK) return -1;
                else if (t == _CBRACK && commonStack.top().id == LENOP) {
                    Symbol s1 = commonStack.top();
                    commonStack.pop();
                    Symbol s2 = commonStack.top();
                    commonStack.push(s1);
                    if (s2.id == _HASH) return -1;
                }
                break;
            case 19:
                if ((t == _CBRACK || t == _COMMA) && commonStack.top().id == _CBRACK) return -1;
                else if ((t == _CBRACK || t == _COMMA) && commonStack.top().id == CONOP) {
                    Symbol s1 = commonStack.top();
                    commonStack.pop();
                    Symbol s2 = commonStack.top();
                    commonStack.push(s1);
                    if (s2.id == _HASH) return -1;
                }
                break;
            case 20:
                if ((t == _CBRACK || t == _COMMA) && commonStack.top().id == _CBRACK) return -1;
                else if ((t == _CBRACK || t == _COMMA) && commonStack.top().id == REPOP) {
                    Symbol s1 = commonStack.top();
                    commonStack.pop();
                    Symbol s2 = commonStack.top();
                    commonStack.push(s1);
                    if (s2.id == _HASH) return -1;
                }
                break;
            case 21:
                if ((t == _CBRACK || t == _COMMA) && commonStack.top().id == _CBRACK) return -1;
                else if ((t == _CBRACK || t == _COMMA) && commonStack.top().id == SEOP) {
                    Symbol s1 = commonStack.top();
                    commonStack.pop();
                    Symbol s2 = commonStack.top();
                    commonStack.push(s1);
                    if (s2.id == _HASH) return -1;
                }
                break;
            case 22:
                if ((t == _CBRACK || t == _COMMA) && commonStack.top().id == _CBRACK) return -1;
                else if ((t == _CBRACK || t == _COMMA) && commonStack.top().id == SUBOP) {
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
                else if (t == _BEGIN) {forFuncAndOper = true; return 15;}
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
				else if (t == _LEN) return 18;
                else if (t == _SRCH) return 21;
                break;
            case 8:
                // if (t != _STR && tokens[1].id == _REL) return 7;
                if ((t == _PLUS || t == _MINUS || t == _OBRACK || t == _ID || t == _NUM || t == _RC || t == _LEN || t == _SRCH) && isAtB(_REL, _SEMCOL) &&
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
                //else if (t == _LEN) return 18;
                //else if (t == _CONC) return 19;
                //else if (t == _REPL) return 20;
                //else if (t == _SRCH) return 21;
                //else if (t == _SUBS) return 22;
                else if (t == _NEWW) return 24;
                break;
            case 11:
                // TODO ////////////////////////////////////////////////
                if (t == _ID && tokens[1].id == _EQ) return 6;
                else if (isAtB(_NOT, _SEMCOL) || isAtB(_OR, _SEMCOL) || isAtB(_AND, _SEMCOL) ||
                         isAtB(_REL, _SEMCOL)) return 8;
                else if (t == _CC || t == _TRUE || t == _FALSE || t == _STR) return 9;
                else if (t == _PLUS || t == _MINUS || t == _OBRACK || t == _ID || t == _NUM || t == _RC || t == _LEN || t == _SRCH) return 7;
                else if (t == _CONC) return 19;
                else if (t == _REPL) return 20;
                else if (t == _SUBS) return 22;
                break;
            case 12:
                if (t == _ID) return 6;
                break;
            case 13:
                // TODO ////////////////////////////////////////////////
                if (isAtB(_NOT, _SEMCOL) || isAtB(_OR, _SEMCOL) || isAtB(_AND, _SEMCOL) ||
                         isAtB(_REL, _SEMCOL)) return 8;
                else if (t == _PLUS || t == _MINUS || t == _OBRACK || t == _ID || t == _NUM || t == _RC || t == _LEN || t == _SRCH) return 7;
                else if (t == _CONC) return 19;
                else if (t == _REPL) return 20;
                else if (t == _SUBS) return 22;
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
                else if (t == _FUNC) {forFuncAndOper = false; return 4;}
                else if (t == _OPER) {forFuncAndOper = false; return 4;}
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
                else if (t == _BEGIN) {forFuncAndOper = true; return 15;}
                break;
            default:
                break;
        }
        
        return -1;
    }
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

int doTransRule(CurGram cg, Symbol s) {
//    std::cout << "doTransRule(cg.id=" << cg.id << ", Symbol s = " << pTT(s.id) << ")\n";
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
//                        std::cout << ">> _S\n";
                        tokens.erase(tokens.begin());
                        commonStack.push(s);
                    }
                    else if (tr.rule == _A) {
//                        std::cout << ">> _A\n";
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
//                        std::cout << ">> _R\n";
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
//                                    std::cout << ">> Compare common stack and fr.inStack:\n";
//                                    for (int j = 0; j < fr.inStack.size(); j++) {
//                                        std::cout << "  " << j << ") " << pTT(dummyVector[j].id) <<
//                                            "\t" << pTT(fr.inStack[j]) << std::endl;
//                                    }
//                                    std::cout << ">> Add OutFoldRule: g.id = " << g.id << ", rNum = " <<
//                                        fr.ruleNum << std::endl;
                                    
                                    break;
                                }
                            }
                        }
                        // Если не найдены правила свертки
                        if (!foldRuleFound) {
//                            std::cout << "    foldRuleFound IS FALSE !!!\n";
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
    //printf("?");
    printf("└");
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
        // Если это последний ребенок родителя, печатаем L
        if (isLastChild) {
            printCurv();
        }
        // Иначе печатаем +
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

void pTree() {
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

void pOutFoldRules() {
    std::cout << "Fold Rules: [";
    for (int i = 0; i < outFoldRules.size(); i++) {
        std::cout << "(g=" << outFoldRules[i].gNum << ", r=" << outFoldRules[i].rNum << ") ";
    }
    std::cout << "]\n";
    
    
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

void syntacticAnalysis() {	
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
    
    // Start tables
    TableOfResource main(std::string(""), 0);
    tables.push_back(main);
    
    
    //main.table.insert ( std::pair<std::string, Resource>("asd", Resource("asd", R_VAR, V_INTEGER, "12")));
    //main.print();
    
    
    // int ing = findTokenInGramWide(cg.id, ct);
    // int ing = findTokenInGram(cg.id, ct);
    // cg = gramsStack.top();
    
    // doTransRule(cg, tokens[0]);
    
    int i = 25;
    while (gramsStack.size() > 0 /* && i > 0 */) {
        i --;
    
        // Print info
//        pGramStack();
//        pCommonStack();
//        pTokens();
//        pOutFoldRules();
        
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
        //pGramStack();
        //pCommonStack();
        //pTokens();

        pOutFoldRules();
        
        pTree();
    }
    else {
        std::cout << "Sentence analysis is NOT complete successfuly.\n";
    }
}
