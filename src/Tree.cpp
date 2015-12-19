/*
* На основе использованных правил сверток и исходных правил из грамматик
* составим синтаксическое дерево, в котором
* узлы - операции,
* листья - операнды.
*/

// Дерево
class Tree {
public:
    Tree(std::vector<OutFoldRule> foldRules, int amountFunc);
    
    // Вершина дерева
    Node* vertex;
    
    // Печать дерева
    void print();
    // Хочу распечатать все использованные правила сверток
    static void printFoldRules(std::vector<OutFoldRule> foldRules);
};

Tree::Tree(std::vector<OutFoldRule> foldRules, int amountFunc) {
    // TODO: Обработка функций и перегрузок
    
    // Запихиваем терминал _PROG в вершину
    vertex = new Node(Symbol(_PROG, pTT(_PROG).c_str(), isTokenTerm(_PROG)), NULL);
    // Запихиваем PROG для главной области видимости
    Node* ch = new Node(Symbol(PROG, pTT(PROG).c_str(), isTokenTerm(PROG)), vertex);
    vertex->children.push_back(ch);
    amountFunc--;
    
    // Разбираем все правила, которые не относятся к объявлению ресурсов
    for (int i = outFoldRules.size() - 1; i >= 0; i--) {
        // Берем правило свертки
        OutFoldRule ofr = outFoldRules[i];
        // Берем грамматику
        Gramm& g = grams[ofr.gNum];
        // Берем правило из грамматики
        std::vector<token_t>& r = g.rules[ofr.rNum];
        // Находим самый правый нетерминал в существующем дереве
        Node* n = findRightestNonTerm(vertex);
        // Если нетерминал найден, то заменяем его
        // В зависимости от номера грамматики и номера правила обработка будет разной
        // Причем не имеет значения какие нетерминалы лежат в дереве, они все равно все заменятся терминалами
        if (n) {
            if (ofr.gNum == 0) {
                // No make
            }
            else if (ofr.gNum == 1) {
                // No make
            }
            else if (ofr.gNum == 2) {
                // No make
            }
            else if (ofr.gNum == 3) {
                // No make
            }
            else if (ofr.gNum == 4) {
                // No make
            }
            else if (ofr.gNum == 5) {
                // No make
            }
            else if (ofr.gNum == 6) {
                if (ofr.rNum == 0) {
                    n->data = ofr.symbols[1];
                }
                if (ofr.rNum == 1) {
                    n->data = ofr.symbols[1];
                }
            }
            else if (ofr.gNum == 7) {
                if (ofr.rNum == 0) {
                    // No make
                }
                else if (ofr.rNum == 1) {
                    n->data = Symbol(_PLUS, pTT(_PLUS).c_str(), isTokenTerm(_PLUS));
                    Node* ch = new Node(Symbol(_NUM, "_NUM[0]", isTokenTerm(_NUM)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(AEXP, pTT(AEXP).c_str(), isTokenTerm(AEXP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 2) {
                    n->data = Symbol(_MINUS, pTT(_MINUS).c_str(), isTokenTerm(_MINUS));
                    Node* ch = new Node(Symbol(_NUM, "_NUM[0]", isTokenTerm(_NUM)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(AEXP, pTT(AEXP).c_str(), isTokenTerm(AEXP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 3) {
                    n->data = Symbol(_PLUS, pTT(_PLUS).c_str(), isTokenTerm(_PLUS));
                    Node* ch = new Node(Symbol(AEXP, pTT(AEXP).c_str(), isTokenTerm(AEXP)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(AEXP, pTT(AEXP).c_str(), isTokenTerm(AEXP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 4) {
                    n->data = Symbol(_MINUS, pTT(_MINUS).c_str(), isTokenTerm(_MINUS));
                    Node* ch = new Node(Symbol(AEXP, pTT(AEXP).c_str(), isTokenTerm(AEXP)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(AEXP, pTT(AEXP).c_str(), isTokenTerm(AEXP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 5) {
                    // No make
                }
                else if (ofr.rNum == 6) {
                    n->data = Symbol(_MULT, pTT(_MULT).c_str(), isTokenTerm(_MULT));
                    Node* ch = new Node(Symbol(AEXP, pTT(AEXP).c_str(), isTokenTerm(AEXP)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(AEXP, pTT(AEXP).c_str(), isTokenTerm(AEXP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 7) {
                    n->data = Symbol(_DIV, pTT(_DIV).c_str(), isTokenTerm(_DIV));
                    Node* ch = new Node(Symbol(AEXP, pTT(AEXP).c_str(), isTokenTerm(AEXP)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(AEXP, pTT(AEXP).c_str(), isTokenTerm(AEXP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 8) {
                    // No make
                }
                else if (ofr.rNum == 9) {
                    // No make
                }
                else if (ofr.rNum == 10) {
                    n->data = ofr.symbols[1];
                }
                else if (ofr.rNum == 11) {
                    n->data = ofr.symbols[1];
                }
                else if (ofr.rNum == 12) {
                    // No make
                }
                else if (ofr.rNum == 13) {
                    // No make
                }
            }
            else if (ofr.gNum == 8) {
                if (ofr.rNum == 0) {
                    // No make
                }
                else if (ofr.rNum == 1) {
                    n->data = Symbol(_OR, pTT(_OR).c_str(), isTokenTerm(_OR));
                    Node* ch = new Node(Symbol(LEXP, pTT(LEXP).c_str(), isTokenTerm(LEXP)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(LEXP, pTT(LEXP).c_str(), isTokenTerm(LEXP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 2) {
                    n->data = Symbol(_OR, pTT(_OR).c_str(), isTokenTerm(_OR));
                    Node* ch = new Node(Symbol(LEXP, pTT(LEXP).c_str(), isTokenTerm(LEXP)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(LEXP, pTT(LEXP).c_str(), isTokenTerm(LEXP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 3) {
                    // No make
                }
                else if (ofr.rNum == 4) {
                    n->data = Symbol(_AND, pTT(_AND).c_str(), isTokenTerm(_AND));
                    Node* ch = new Node(Symbol(LEXP, pTT(LEXP).c_str(), isTokenTerm(LEXP)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(LEXP, pTT(LEXP).c_str(), isTokenTerm(LEXP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 5) {
                    // No make
                }
                else if (ofr.rNum == 6) {
                    // No make
                }
                else if (ofr.rNum == 7) {
                    // n->data = Symbol(_REL, pTT(_REL).c_str(), isTokenTerm(_REL));
                    n->data = ofr.symbols[2];
                    Node* ch = new Node(Symbol(AEXP, pTT(AEXP).c_str(), isTokenTerm(AEXP)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(AEXP, pTT(AEXP).c_str(), isTokenTerm(AEXP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 8) {
                    // n->data = Symbol(_REL, pTT(_REL).c_str(), isTokenTerm(_REL));
                    n->data = ofr.symbols[2];
                    Node* ch = new Node(ofr.symbols[1], n);
                    n->children.push_back(ch);
                    Node* cch = new Node(ofr.symbols[3], n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 9) {
                    n->data = Symbol(_NOT, pTT(_NOT).c_str(), isTokenTerm(_NOT));
                    Node* ch = new Node(Symbol(LEXP, pTT(LEXP).c_str(), isTokenTerm(LEXP)), n);
                    n->children.push_back(ch);
                }
                else if (ofr.rNum == 10) {
                    // No make
                }
            }
            else if (ofr.gNum == 9) {
                if (ofr.rNum == 0) {
                    // No make
                }
                else if (ofr.rNum == 1) {
                    n->data = ofr.symbols[1];
                }
                else if (ofr.rNum == 2) {
                    // No make
                }
                else if (ofr.rNum == 3) {
                    n->data = ofr.symbols[1];
                }
                else if (ofr.rNum == 4) {
                    n->data = Symbol(_PLUS, pTT(_PLUS).c_str(), isTokenTerm(_PLUS));
                    Node* ch = new Node(Symbol(_NUM, pTT(_NUM).c_str(), isTokenTerm(_NUM)), n);
                    n->children.push_back(ch);
                }
                else if (ofr.rNum == 5) {
                    n->data = Symbol(_MINUS, pTT(_MINUS).c_str(), isTokenTerm(_MINUS));
                    Node* ch = new Node(Symbol(_NUM, pTT(_NUM).c_str(), isTokenTerm(_NUM)), n);
                    n->children.push_back(ch);
                }
                else if (ofr.rNum == 6) {
                    n->data = ofr.symbols[1];
                }
                else if (ofr.rNum == 7) {
                    n->data = ofr.symbols[1];
                }
                else if (ofr.rNum == 8) {
                    n->data = ofr.symbols[1];
                }
                else if (ofr.rNum == 9) {
                    n->data = ofr.symbols[1];
                }
            }
            else if (ofr.gNum == 10) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_LABEL, pTT(_LABEL).c_str(), isTokenTerm(_LABEL));
                    Node* ch = new Node(Symbol(ID, pTT(ID).c_str(), isTokenTerm(ID)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(OP, pTT(OP).c_str(), isTokenTerm(OP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 1) {
                    // No make
                }
                else if (ofr.rNum == 2) {
                    // No make
                }
                else if (ofr.rNum == 3) {
                    // No make
                }
                else if (ofr.rNum == 4) {
                    // No make
                }
                else if (ofr.rNum == 5) {
                    // No make
                }
                else if (ofr.rNum == 6) {
                    // No make
                }
                else if (ofr.rNum == 7) {
                    // No make
                }
                else if (ofr.rNum == 8) {
                    // No make
                }
                else if (ofr.rNum == 9) {
                    // No make
                }
                else if (ofr.rNum == 10) {
                    // No make
                }
            }
            else if (ofr.gNum == 11) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_EQ, pTT(_EQ).c_str(), isTokenTerm(_EQ));
                    Node* ch = new Node(Symbol(ID, pTT(ID).c_str(), isTokenTerm(ID)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(AEXP, pTT(AEXP).c_str(), isTokenTerm(AEXP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 1) {
                    // No make
                }
                else if (ofr.rNum == 2) {
                    // No make
                }
                else if (ofr.rNum == 3) {
                    // No make
                }
                else if (ofr.rNum == 4) {
                    // No make
                }
                else if (ofr.rNum == 5) {
                    // No make
                }
                else if (ofr.rNum == 6) {
                    // No make
                }
            }
            else if (ofr.gNum == 12) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_GOTO, pTT(_GOTO).c_str(), isTokenTerm(_GOTO));
                    Node* ch = new Node(Symbol(ID, pTT(ID).c_str(), isTokenTerm(ID)), n);
                    n->children.push_back(ch);
                }
            }
            else if (ofr.gNum == 13) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_WRITE, pTT(_WRITE).c_str(), isTokenTerm(_WRITE));
                    Node* ch = new Node(Symbol(MSG, pTT(MSG).c_str(), isTokenTerm(MSG)), n);
                    n->children.push_back(ch);
                }
                else if (ofr.rNum == 1) {
                    Node* ch = new Node(Symbol(MSG, pTT(MSG).c_str(), isTokenTerm(MSG)), n->parent);
                    n->parent->children.push_back(ch);
                }
                else if (ofr.rNum == 2) {
                    // No make
                }
                else if (ofr.rNum == 3) {
                    // No make
                }
                else if (ofr.rNum == 4) {
                    // No make
                }
                else if (ofr.rNum == 5) {
                    n->data = ofr.symbols[1];
                }
            }
            else if (ofr.gNum == 14) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_READ, pTT(_READ).c_str(), isTokenTerm(_READ));
                    Node* ch = new Node(Symbol(ID, pTT(ID).c_str(), isTokenTerm(ID)), n);
                    n->children.push_back(ch);
                }
                else if (ofr.rNum == 1) {
                    Node* ch = new Node(Symbol(ID, pTT(ID).c_str(), isTokenTerm(ID)), n->parent);
                    n->parent->children.push_back(ch);
                }
                else if (ofr.rNum == 2) {
                    // No make
                }
            }
            else if (ofr.gNum == 15) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_BEGIN, pTT(_BEGIN).c_str(), isTokenTerm(_BEGIN));
                    Node* ch = new Node(Symbol(OP, pTT(OP).c_str(), isTokenTerm(OP)), n);
                    n->children.push_back(ch);
                }
                else if (ofr.rNum == 1) {
                    n->data = Symbol(_BEGIN, pTT(_BEGIN).c_str(), isTokenTerm(_BEGIN));
                }
                else if (ofr.rNum == 2) {
                    Node* ch = new Node(Symbol(OP, pTT(OP).c_str(), isTokenTerm(OP)), n->parent);
                    n->parent->children.push_back(ch);
                }
                else if (ofr.rNum == 3) {
                    // No make
                }
            }
            else if (ofr.gNum == 16) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_IF, pTT(_IF).c_str(), isTokenTerm(_IF));
                    Node* ch = new Node(Symbol(LEXP, pTT(LEXP).c_str(), isTokenTerm(LEXP)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(OCOP, pTT(OCOP).c_str(), isTokenTerm(OCOP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 1) {
                    n->data = Symbol(_IF, pTT(_IF).c_str(), isTokenTerm(_IF));
                    Node* ch = new Node(Symbol(LEXP, pTT(LEXP).c_str(), isTokenTerm(LEXP)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(OCOP, pTT(OCOP).c_str(), isTokenTerm(OCOP)), n);
                    n->children.push_back(cch);
                    Node* ccch = new Node(Symbol(OCOP, pTT(OCOP).c_str(), isTokenTerm(OCOP)), n);
                    n->children.push_back(ccch);
                }
                else if (ofr.rNum == 2) {
                    // No make
                }
                else if (ofr.rNum == 3) {
                    // No make
                }
            }
            else if (ofr.gNum == 17) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_WHILE, pTT(_WHILE).c_str(), isTokenTerm(_WHILE));
                    Node* ch = new Node(Symbol(LEXP, pTT(LEXP).c_str(), isTokenTerm(LEXP)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(OCOP, pTT(OCOP).c_str(), isTokenTerm(OCOP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 1) {
                    // No make
                }
                else if (ofr.rNum == 2) {
                    // No make
                }
            }
            else if (ofr.gNum == 18) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_LEN, pTT(_LEN).c_str(), isTokenTerm(_LEN));
                    Node* ch = new Node(Symbol(IDSC, pTT(IDSC).c_str(), isTokenTerm(IDSC)), n);
                    n->children.push_back(ch);
                }
                else if (ofr.rNum == 1) {
                    n->data = Symbol(ID, pTT(ID).c_str(), isTokenTerm(ID));
                }
                else if (ofr.rNum == 2) {
                    n->data = ofr.symbols[1];
                }
            }
            else if (ofr.gNum == 19) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_CONC, pTT(_CONC).c_str(), isTokenTerm(_CONC));
                    Node* ch = new Node(Symbol(IDSC, pTT(IDSC).c_str(), isTokenTerm(IDSC)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(IDSC, pTT(IDSC).c_str(), isTokenTerm(IDSC)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 1) {
                    n->data = Symbol(ID, pTT(ID).c_str(), isTokenTerm(ID));
                }
                else if (ofr.rNum == 2) {
                    n->data = ofr.symbols[1];
                }
            }
            else if (ofr.gNum == 20) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_REPL, pTT(_REPL).c_str(), isTokenTerm(_REPL));
                    Node* ch = new Node(Symbol(IDSC, pTT(IDSC).c_str(), isTokenTerm(IDSC)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(IDSC, pTT(IDSC).c_str(), isTokenTerm(IDSC)), n);
                    n->children.push_back(cch);
                    Node* ccch = new Node(Symbol(IDSC, pTT(IDSC).c_str(), isTokenTerm(IDSC)), n);
                    n->children.push_back(ccch);
                }
                else if (ofr.rNum == 1) {
                    n->data = Symbol(ID, pTT(ID).c_str(), isTokenTerm(ID));
                }
                else if (ofr.rNum == 2) {
                    n->data = ofr.symbols[1];
                }
            }
            else if (ofr.gNum == 21) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_SRCH, pTT(_SRCH).c_str(), isTokenTerm(_SRCH));
                    Node* ch = new Node(Symbol(IDSC, pTT(IDSC).c_str(), isTokenTerm(IDSC)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(IDSC, pTT(IDSC).c_str(), isTokenTerm(IDSC)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 1) {
                    n->data = Symbol(ID, pTT(ID).c_str(), isTokenTerm(ID));
                }
                else if (ofr.rNum == 2) {
                    n->data = ofr.symbols[1];
                }
            }
            else if (ofr.gNum == 22) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_SUBS, pTT(_SUBS).c_str(), isTokenTerm(_SUBS));
                    Node* ch = new Node(Symbol(IDSC, pTT(IDSC).c_str(), isTokenTerm(IDSC)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(IDSC, pTT(IDSC).c_str(), isTokenTerm(IDSC)), n);
                    n->children.push_back(cch);
                    Node* ccch = new Node(Symbol(IDSC, pTT(IDSC).c_str(), isTokenTerm(IDSC)), n);
                    n->children.push_back(ccch);
                }
                else if (ofr.rNum == 1) {
                    n->data = Symbol(ID, pTT(ID).c_str(), isTokenTerm(ID));
                }
                else if (ofr.rNum == 2) {
                    n->data = ofr.symbols[1];
                }
                else if (ofr.rNum == 3) {
                    n->data = Symbol(ID, pTT(ID).c_str(), isTokenTerm(ID));
                }
                else if (ofr.rNum == 4) {
                    n->data = ofr.symbols[1];
                }
            }
            else if (ofr.gNum == 23) {
                // No make
            }
            else if (ofr.gNum == 24) {
                // Don't make this gramma
            }
            else if (ofr.gNum == 25) {
                if (ofr.rNum == 0) {
                    n->data = Symbol(_IF, pTT(_IF).c_str(), isTokenTerm(_IF));
                    Node* ch = new Node(Symbol(LEXP, pTT(LEXP).c_str(), isTokenTerm(LEXP)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(AOP, pTT(AOP).c_str(), isTokenTerm(AOP)), n);
                    n->children.push_back(cch);
                }
                else if (ofr.rNum == 1) {
                    n->data = Symbol(_IF, pTT(_IF).c_str(), isTokenTerm(_IF));
                    Node* ch = new Node(Symbol(LEXP, pTT(LEXP).c_str(), isTokenTerm(LEXP)), n);
                    n->children.push_back(ch);
                    Node* cch = new Node(Symbol(AOP, pTT(AOP).c_str(), isTokenTerm(AOP)), n);
                    n->children.push_back(cch);
                    Node* ccch = new Node(Symbol(AOP, pTT(AOP).c_str(), isTokenTerm(AOP)), n);
                    n->children.push_back(ccch);
                }
            }
            else if (ofr.gNum == 26) {
                // No make
            }
        }
        // Если не нашли, то построение дерева для главной области видимости закончено
        // Нужно глянуть есть ли еще области видмости и достроить дерево для них
        else {
            if (amountFunc != 0) {
                if (ofr.gNum == 15) {
                    // Запихиваем PROG для новой области видимости
                    Node* ch = new Node(Symbol(PROG, pTT(PROG).c_str(), isTokenTerm(PROG)), vertex);
                    if (vertex->children.size() == 1) {
                        vertex->children.push_back(ch);
                    }
                    else {
                        vertex->children.insert(vertex->children.begin()+1, ch);
                    }
                    amountFunc--;
                    // Нужно еще раз глянуть текущее правило свертки
                    i++;
                }
            }
            else {
                break;
            }
        }
    }
    
}

// Печать дерева
// Используются функции из syntactic.cpp, чтобы не определять их еще один раз
void Tree::print() {
    tabs = 0;
    pipes = 1;
    return showNode(vertex, false);
}

// Хочу распечатать все использованные правила сверток
void Tree::printFoldRules(std::vector<OutFoldRule> foldRules) {
    for (int i = 0; i < foldRules.size(); i++) {
        // Берем правило свертки
        OutFoldRule ofr = foldRules[i];
        // Берем грамматику
        Gramm& g = grams[ofr.gNum];
        // Берем правило из грамматики
        std::vector<token_t>& r = g.rules[ofr.rNum];
        // Печатаем правило
        std::cout << "G=" << ofr.gNum << " R=" << ofr.rNum << std::endl;
        for (int j = 1; j < r.size(); j++) {
            Symbol s (r[j], pTT(r[j]).c_str(), isTokenTerm(r[j]));
            if (r[j] == _ID || r[j] == _NUM || r[j] == _RC || r[j] == _REL || r[j] == _STR) {
                s.str = ofr.symbols[j].str;
            }
            std::cout << s.value() << " ";
        }
        std::cout << std::endl;
    }
}