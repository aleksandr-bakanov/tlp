
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

//======================================================================
//
// G L O B A L   V A R I A B L E S
//
//======================================================================
// Необходимая фигня, чтобы в функциях и перегрузках не влезать во второй блок begin .. end
bool forFuncAndOper;

// Common stack
std::stack<Symbol> commonStack;
// Stack of gramms
std::stack<CurGram> gramsStack;
// Output stack

// Vector for table of resource
std::vector<TableOfResource*> resourceTables;

std::stack<TableOfResource*> resourceTableStack;
TableOfResource* currentResourceTable = NULL;
Node* newTableNode = NULL;
//======================================================================

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
#ifdef DEBUG
    std::cout << "findTokenInGram(gi=" << gi << ", t="; pT(t); std::cout  << ")" << std::endl;
#endif
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
            case 6:
                if (t == _CBRACK && commonStack.top().id != _OBRACK) {
                    return -1;
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
            case 13:
                if (t == _OBRACK && commonStack.top().id == _OBRACK) {
                    return 7;
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

                else if (t == _CONST) return 23;
                else if (t == _VAR) return 23;
                else if (t == _LABEL) return 23;
                else if (t == _FUNC) return 23;
                else if (t == _OPER) return 23;

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
                //else if (t == _NEWW) return 24;
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

// Функция вытаскивает из синтаксического дерева все указатели на RVAR.
void getAllRvars(Node* n, std::vector<Node*>& res) {
    if (n->data.id == RVAR) {
        res.push_back(n);
    }
    // Если есть дети, смотрим их слева-направо
    if (n->children.size() > 0) {
        for (int i = 0; i < n->children.size(); i++) {
            getAllRvars(n->children[i], res);
        }
    }
}

// Функция вытаскивает из синтаксического дерева все указатели на ID.
void getAllIds(Node* n, std::vector<Node*>& res) {
    if (n->data.id == ID) {
        res.push_back(n);
    }
    // Если есть дети, смотрим их слева-направо
    if (n->children.size() > 0) {
        for (int i = 0; i < n->children.size(); i++) {
            getAllIds(n->children[i], res);
        }
    }
}

// Функция вытаскивает из синтаксического дерева все указатели на ID.
void getAllUnderscoredIds(Node* n, std::vector<Node*>& res) {
    if (n->data.id == _ID) {
        res.push_back(n);
    }
    // Если есть дети, смотрим их слева-направо
    if (n->children.size() > 0) {
        for (int i = 0; i < n->children.size(); i++) {
            getAllUnderscoredIds(n->children[i], res);
        }
    }
}

// Функции передают указатель на RVAR узел, она ищет среди его
// потомков узлы с типом _ID и TYPE. Заполняя по ходу таблицу ресурсов.
void collectVars(Node* n, std::vector<Resource>& resources, bool isRoot) {
    if (n->data.id == _ID) {
        Resource r (n->data.value(), R_VAR, V_NULL, "");
        resources.push_back(r);
    }
    else if (n->data.id == TYPE) {
        value_t type = V_NULL;
        switch (n->children[0]->data.id) {
            case _INT: type = V_INTEGER; break;
            case _REAL: type = V_REAL; break;
            case _BOOL: type = V_BOOLEAN; break;
            case _STRING: type = V_STRING; break;
            default: type = V_NULL; break;
        }
        for (int i = 0; i < resources.size(); i++) {
            resources[i].type = type;
        }
        return;
    }
    else if (n->data.id == RVAR && !isRoot) {
        // Get the fuck out here!
        return;
    }
    // Если есть дети, смотрим их справа-налево
    if (n->children.size() > 0) {
        for (int i = 0; i < n->children.size(); i++) {
            collectVars(n->children[i], resources, false);
        }
    }
}

void collectConst(Node* n, std::vector<Resource>& resources) {
    Node* nameChild = n->children[0];
    Node* valueChild = n->parent->children[2]->children[0];
    value_t type = V_NULL;
    switch (valueChild->data.id) {
        case _NUM: type = V_INTEGER; break;
        case _RC: type = V_REAL; break;
        case _TRUE:
        case _FALSE: type = V_BOOLEAN; break;
        case _STR: type = V_STRING; break;
        default: type = V_NULL; break;
    }
    Resource r (nameChild->data.value(), R_CONST, type, valueChild->data.value());
    resources.push_back(r);
}

void collectLabel(Node* n, std::vector<Resource>& resources) {
    Resource r (n->data.value(), R_LABEL, V_NULL, "");
    resources.push_back(r);
}

void giveMeVars(Node* n) {
    // Собираем все rvars из детей данного узла.
    std::vector<Node*> rvars;
    getAllRvars(n, rvars);
    // Собираем vars в ресурсы
    std::vector<Resource> vars;
    for (int i = 0; i < rvars.size(); i++) {
        collectVars(rvars[i], vars, true);
    }
    // Сохраняем ресурсы в текущую таблицу.
    for (int i = 0; i < vars.size(); i++) {
        std::pair<std::map<std::string, Resource>::iterator, bool>
            ret = currentResourceTable->table.insert(
                std::pair<std::string, Resource>(
                    vars[i].name, vars[i]));
        // Если ресурс с таким именем уже есть в таблице,
        // то сообщаем об ошибке и уходим.
        if (ret.second == false) {
            printf("Duplicate identifier: %s\n", vars[i].name.c_str());
            exit(1);
        }
    }
}

void giveMeConsts(Node* n) {
    // Собираем все rvars из детей данного узла.
    std::vector<Node*> ids;
    getAllIds(n, ids);
    // Собираем consts в ресурсы
    std::vector<Resource> consts;
    for (int i = 0; i < ids.size(); i++) {
        collectConst(ids[i], consts);
    }
    // Сохраняем ресурсы в текущую таблицу.
    for (int i = 0; i < consts.size(); i++) {
        std::pair<std::map<std::string, Resource>::iterator, bool>
            ret = currentResourceTable->table.insert(
                std::pair<std::string, Resource>(
                    consts[i].name, consts[i]));
        // Если ресурс с таким именем уже есть в таблице,
        // то сообщаем об ошибке и уходим.
        if (ret.second == false) {
            printf("Duplicate identifier: %s\n", consts[i].name.c_str());
            exit(1);
        }
    }
}

void giveMeLabels(Node* n) {
    // Собираем все rvars из детей данного узла.
    std::vector<Node*> labelIds;
    getAllUnderscoredIds(n, labelIds);
    // Собираем vars в ресурсы
    std::vector<Resource> labels;
    for (int i = 0; i < labelIds.size(); i++) {
        collectLabel(labelIds[i], labels);
    }
    // Сохраняем ресурсы в текущую таблицу.
    for (int i = 0; i < labels.size(); i++) {
        std::pair<std::map<std::string, Resource>::iterator, bool>
            ret = currentResourceTable->table.insert(
                std::pair<std::string, Resource>(
                    labels[i].name, labels[i]));
        // Если ресурс с таким именем уже есть в таблице,
        // то сообщаем об ошибке и уходим.
        if (ret.second == false) {
            printf("Duplicate identifier: %s\n", labels[i].name.c_str());
            exit(1);
        }
    }
}

value_t getVariableType(Node* n) {
    switch (n->data.id) {
        case _INT: return V_INTEGER;
        case _REAL: return V_REAL;
        case _BOOL: return V_BOOLEAN;
        case _STRING: return V_STRING;
        default: return V_NULL;
    }
}

// Сбор ресурсов с подконтрольных территорий (всего дерева).
void collectResources(Node* n) {
    // Если есть дети, надо проверить нулевого, он может быть
    // _VAR, _CONST, _LABEL или HFUN.
    if (n->children.size() > 0) {
        token_t id = n->children[0]->data.id;
        if (id == _VAR) {
            giveMeVars(n);
            return;
        }
        else if (id == _CONST) {
            giveMeConsts(n);
            return;
        }
        else if (id == _LABEL) {
            giveMeLabels(n);
            return;
        }
        else if (id == HFUN) {
            Node* nameChild = n->children[0]->children[1]->children[0];
            Node* typeChild = n->children[0]->children[3]->children[0];
            value_t type = getVariableType(typeChild);
            Resource r (nameChild->data.value(), R_FUNC, type, "");
            std::pair<std::map<std::string, Resource>::iterator, bool>
                ret = currentResourceTable->table.insert(
                    std::pair<std::string, Resource>(r.name, r));
            if (ret.second == false) {
                printf("Duplicate identifier: %s\n", r.name.c_str());
                exit(1);
            }
            // Создаем локальную таблицу ресурсов
            newTableNode = n;
            TableOfResource* newTable = new TableOfResource(r.name);
            resourceTables.push_back(newTable);
            resourceTableStack.push(newTable);
            currentResourceTable = newTable;
            // Запишем сразу в локальную таблицу переменную с названием
            // функции и типом возвращаемого значения функции.
            Resource r2d2 (nameChild->data.value(), R_VAR, type, "");
            currentResourceTable->table.insert(
                    std::pair<std::string, Resource>(r2d2.name, r2d2));
        }
        else if (id == _OPER) {
            Resource operand_1, operand_2, return_value;
            std::string oper_name = pTT(n->children[1]->children[0]->data.id);
            Node* ovar = n->children[3];
            operand_1.name = ovar->children[0]->children[0]->data.value();
            if (ovar->children[1]->data.id == _COLUM) {
                value_t oper_1_type = getVariableType(ovar->children[2]->children[0]);
                operand_1.type = oper_1_type;
                operand_2.name = ovar->children[4]->children[0]->data.value();
                value_t oper_2_type = getVariableType(ovar->children[6]->children[0]);
                operand_2.type = oper_2_type;
            }
            else {
                operand_2.name = ovar->children[2]->children[0]->data.value();
                value_t operands_type = getVariableType(ovar->children[4]->children[0]);
                operand_1.type = operands_type;
                operand_2.type = operands_type;
            }
            return_value.name = n->children[5]->children[0]->data.value();
            value_t return_value_type = getVariableType(n->children[7]->children[0]);
            return_value.type = return_value_type;
            operand_1.res = operand_2.res = return_value.res = R_VAR;
            
            oper_name += Resource::valueTypeToStr(operand_1.type) + Resource::valueTypeToStr(operand_2.type);
            
            // Создаем локальную таблицу ресурсов
            TableOfResource* newTable = new TableOfResource(oper_name);
            resourceTables.push_back(newTable);
            newTable->table.insert(std::pair<std::string, Resource>(operand_1.name, operand_1));
            newTable->table.insert(std::pair<std::string, Resource>(operand_2.name, operand_2));
            newTable->table.insert(std::pair<std::string, Resource>(return_value.name, return_value));
        }
    }

    for (int i = 0; i < n->children.size(); i++) {
        collectResources(n->children[i]);
    }

    if (newTableNode == n) {
        newTableNode = NULL;
        resourceTableStack.pop();
        currentResourceTable = resourceTableStack.top();
    }
}

int doTransRule(CurGram cg, Symbol s) {
#ifdef DEBUG
    std::cout << "doTransRule(cg.id=" << cg.id << ", Symbol s = " << pTT(s.id) << ")\n";
#endif
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
#ifdef DEBUG
                        std::cout << ">> _S\n";
#endif
                        tokens.erase(tokens.begin());
                        commonStack.push(s);
                    }
                    else if (tr.rule == _A) {
#ifdef DEBUG
                        std::cout << ">> _A\n";
#endif
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
#ifdef DEBUG
                        std::cout << ">> _R\n";
#endif
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
#ifdef DEBUG
                                    std::cout << ">> Compare common stack and fr.inStack:\n";
                                    for (int j = 0; j < fr.inStack.size(); j++) {
                                        std::cout << "  " << j << ") " << pTT(dummyVector[j].id) <<
                                            "\t" << pTT(fr.inStack[j]) << std::endl;
                                    }
                                    std::cout << ">> Add OutFoldRule: g.id = " << g.id << ", rNum = " <<
                                        fr.ruleNum << std::endl;
#endif
                                    break;
                                }
                            }
                        }
                        // Если не найдены правила свертки
                        if (!foldRuleFound) {
#ifdef DEBUG
                            std::cout << "    foldRuleFound IS FALSE !!!\n";
#endif
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
    printf("├");
}

void printPipe() {
    printf("│");
}

void printCurv() {
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

void pTree(Node* &root) {
    // Print in tree view
    // Create tree
    // При построении дерева по правилам свертки, каждое очередное правило разворачивает
    // самый правый нетерминал в дереве.
    Symbol tmp_s (PROG, pTT(PROG).c_str(), isTokenTerm(PROG));
    root = new Node(tmp_s, NULL);
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
                if (r[j] == _ID || r[j] == _NUM || r[j] == _RC || r[j] == _REL || r[j] == _STR) {
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

// Сериализация узла дерева
void serializationNode(std::ofstream& fout, Node* n, int& numNode) {
    
    if (n->parent == NULL) {
        fout << "\tn" << numNode << ";" << std::endl;
    }
    
    fout << "\tn" << numNode << "[shape=\"";
    if (n->data.isToken) {
        fout << "ellipse";
    } else {
        fout << "box";
    }
    fout << "\", label = ";
    if (n->data.isToken) {
        fout << "\"" << n->data.str << "\"";
    } else {
        fout << "<<I>" << n->data.str << "</I>>";
    }
    fout << "];" << std::endl;
    
    // Рекурсивно сериализуем детей
    int curNumNode = numNode;
    for (int i = 0; i < n->children.size(); i++) {
        numNode++;
        fout << "\tn" << curNumNode << " -> n" << numNode << ";" << std::endl;
        serializationNode(fout, n->children[i], numNode);
    }
}

// Сериализация дерева для его последующего красивого представления.
void serializationTree(Node* root) {
    std::ofstream fout("tree.gv");
    
    fout << "digraph HelloWorld {" << std::endl;
    fout << "\tnode [margin=\"0.01\"];" << std::endl;
    fout << "\trankdir=\"LR\";" << std::endl << std::endl;
    int numNode = 1;
    serializationNode(fout, root, numNode);
    fout << "}" << std::endl;
    fout.close();
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

void pSyntaxErrorAt(std::vector<Symbol> tokens, int index) {
    std::cout << "Tokens: [";
    for (int i = 0; i < tokens.size(); i++) {
        if (i == index) {
            std::cout << "      >>>>>>>>>> ";
            std::cout << tokens[i].str;
            std::cout << " <<<<<<<<<<        ";
        }
        else {
            std::cout << tokens[i].str << "  ";
        }
    }
    std::cout << "]\n";
}

bool syntacticAnalysis() {
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
    
    // Local copy of tokens from lexical analisator
    std::vector<Symbol> tokensCopy = tokens;

    pTokens();

    // Start from G0
    gramsStack.push(cg);
    // Gramm& g = grams[cg.id];
    // Put hash in stack (CS)
    commonStack.push(hashSymbol);

    int i = 25;
    while (gramsStack.size() > 0 /* && i > 0 */) {
        i--;

        // Print info
#ifdef DEBUG
        pGramStack();
        pCommonStack();
        pTokens();
        pOutFoldRules();
#endif
        
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

        pOutFoldRules();

        Node* root = NULL;
        pTree(root);
        
        serializationTree(root);
        
        TableOfResource* firstResourceTable = new TableOfResource();
        resourceTables.push_back(firstResourceTable);
        resourceTableStack.push(firstResourceTable);
        currentResourceTable = firstResourceTable;
        
        collectResources(root);
        
        printf("Resources tables: \n");
        for (int i = 0; i < resourceTables.size(); i++) {
            std::cout << "Table <" << resourceTables[i]->name << ">:" << std::endl;
            resourceTables[i]->print();
        }
        
        return true;
    }
    else {
        std::cout << "\n\nSentence analysis is STOPPED at symbol marked by arrows:\n";
        pSyntaxErrorAt(tokensCopy, tokensCopy.size() - tokens.size());
        return false;
    }
}
