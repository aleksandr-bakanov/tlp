/*
* На основе нового дерева вывода нужно построить триады
*/
class VectorTriad {
public:
    VectorTriad(Tree* tree);
    
    // Stack of fold rules and grams
    std::vector<Triad> triads;
    
    void print();
    
private:
    // Рекурсивная функция создания триад
    void makeTriads(Node* vertex, int& numTr);
    
};

VectorTriad::VectorTriad(Tree* tree) {
    int numTr = 0;
    makeTriads(tree->vertex, numTr);
}

// Рекурсивная функция создания триад
void VectorTriad::makeTriads(Node* vertex, int& numTr) {
    // Сначала проверяем корень
    if (vertex->data.id == _PROG) {
        for (int i = 0; i < vertex->children.size(); i++) {
            Triad triad;
            triad.operation = &vertex->data;
            triad.operand1 = &vertex->children[i]->data;
            triad.operand2 = NULL;
            triad.triadNum = numTr;
            numTr++;
            triads.push_back(triad);
            // Рекурсия
            makeTriads(vertex->children[i], numTr);
            Triad triad1;
            triad1.operation = &vertex->data;
            Symbol* s = new Symbol(_END, pTT(_END).c_str(), isTokenTerm(_END));
            triad1.operand1 = s;
            triad1.operand2 = NULL;
            triad1.triadNum = numTr;
            numTr++;
            triads.push_back(triad1);
        }
    }
    else if (vertex->data.id == _BEGIN) {
        for (int i = 0; i < vertex->children.size(); i++) {
            // Рекурсия
            makeTriads(vertex->children[i], numTr);
        }
    }
    else if (vertex->data.id == _WRITE) {
        for (int i = 0; i < vertex->children.size(); i++) {
            Triad triad;
            triad.operation = &vertex->data;
            int oldNumTr = numTr;
            // Рекурсия
            makeTriads(vertex->children[i], numTr);
            if (oldNumTr == numTr) {
                triad.operand1 = &vertex->children[i]->data;
            }
            else {
                std::string str = "[";
                std::ostringstream temp;
                temp << (numTr-1);
                str += temp.str();
                str += "]";
                Symbol* s = new Symbol(_OLD, str, isTokenTerm(_OLD));
                
                triad.operand1 = s;
            }
            triad.operand2 = NULL;
            triad.triadNum = numTr;
            numTr++;
            triads.push_back(triad);
        }
    }
    else if (vertex->data.id == _PLUS || vertex->data.id == _MINUS || 
                            vertex->data.id == _MULT || vertex->data.id == _DIV || 
                            vertex->data.id == _AND || vertex->data.id == _OR || 
                            vertex->data.id == _REL) {
        // У _PLUS, _MINUS, _MULT, _DIV может быть только два ребенка или один
        Triad triad;
        triad.operation = &vertex->data;
        int oldNumTr = numTr;
        // Рекурсия для левого ребенка
        if (vertex->children[0] != NULL) {
            makeTriads(vertex->children[0], numTr);
            if (oldNumTr == numTr) {
                triad.operand1 = &vertex->children[0]->data;
            }
            else {
                std::string str = "[";
                std::ostringstream temp;
                temp << (numTr-1);
                str += temp.str();
                str += "]";
                Symbol* s = new Symbol(_OLD, str, isTokenTerm(_OLD));
                
                triad.operand1 = s;
            }
        }
        else {
            triad.operand1 = NULL;
        }
        oldNumTr = numTr;
        // Рекурсия для правого ребенка
        if (vertex->children[1] != NULL) {
            makeTriads(vertex->children[1], numTr);
            if (oldNumTr == numTr) {
                triad.operand2 = &vertex->children[1]->data;
            }
            else {
                std::string str = "[";
                std::ostringstream temp;
                temp << (numTr-1);
                str += temp.str();
                str += "]";
                Symbol* s = new Symbol(_OLD, str, isTokenTerm(_OLD));
                
                triad.operand2 = s;
            }
        }
        else {
            triad.operand2 = NULL;
        }
        triad.triadNum = numTr;
        numTr++;
        triads.push_back(triad);
    }
    else if (vertex->data.id == _EQ) {
        // У _EQ два ребенка: слева идентификатор, справа какое-то выражение
        Triad triad;
        triad.operation = &vertex->data;
        triad.operand1 = &vertex->children[0]->data;
        int oldNumTr = numTr;
        // Рекурсия для правого ребенка
        if (vertex->children[1] != NULL) {
            makeTriads(vertex->children[1], numTr);
            if (oldNumTr == numTr) {
                triad.operand2 = &vertex->children[1]->data;
            }
            else {
                std::string str = "[";
                std::ostringstream temp;
                temp << (numTr-1);
                str += temp.str();
                str += "]";
                Symbol* s = new Symbol(_OLD, str, isTokenTerm(_OLD));
                
                triad.operand2 = s;
            }
        }
        else {
            triad.operand2 = NULL;
        }
        triad.triadNum = numTr;
        numTr++;
        triads.push_back(triad);
    }
    else if (vertex->data.id == _READ) {
        for (int i = 0; i < vertex->children.size(); i++) {
            Triad triad;
            triad.operation = &vertex->data;
            triad.operand1 = &vertex->children[i]->data;
            triad.operand2 = NULL;
            triad.triadNum = numTr;
            numTr++;
            triads.push_back(triad);
        }
    }
    else if (vertex->data.id == _LEN) {
        Triad triad;
        triad.operation = &vertex->data;
        triad.operand1 = &vertex->children[0]->data;
        triad.operand2 = NULL;
        triad.triadNum = numTr;
        numTr++;
        triads.push_back(triad);
    }
    else if (vertex->data.id == _LABEL) {
        Triad triad;
        triad.operation = &vertex->data;
        triad.operand1 = &vertex->children[0]->data;
        triad.operand2 = NULL;
        triad.triadNum = numTr;
        numTr++;
        triads.push_back(triad);
        // Рекурсия
        makeTriads(vertex->children[1], numTr);
    }
    else if (vertex->data.id == _GOTO) {
        Triad triad;
        triad.operation = &vertex->data;
        triad.operand1 = &vertex->children[0]->data;
        triad.operand2 = NULL;
        triad.triadNum = numTr;
        numTr++;
        triads.push_back(triad);
    }
    else if (vertex->data.id == _CONC) {
        Triad triad;
        triad.operation = &vertex->data;
        triad.operand1 = &vertex->children[0]->data;
        triad.operand2 = &vertex->children[1]->data;
        triad.triadNum = numTr;
        numTr++;
        triads.push_back(triad);
    }
    else if (vertex->data.id == _SRCH) {
        Triad triad;
        triad.operation = &vertex->data;
        triad.operand1 = &vertex->children[0]->data;
        triad.operand2 = &vertex->children[1]->data;
        triad.triadNum = numTr;
        numTr++;
        triads.push_back(triad);
    }
    else if (vertex->data.id == _NOT) {
        Triad triad;
        triad.operation = &vertex->data;
        int oldNumTr = numTr;
        // Рекурсия
        makeTriads(vertex->children[0], numTr);
        if (oldNumTr == numTr) {
            triad.operand1 = &vertex->children[0]->data;
        }
        else {
            std::string str = "[";
            std::ostringstream temp;
            temp << (numTr-1);
            str += temp.str();
            str += "]";
            Symbol* s = new Symbol(_OLD, str, isTokenTerm(_OLD));
            
            triad.operand1 = s;
        }
        triad.operand2 = NULL;
        triad.triadNum = numTr;
        numTr++;
        triads.push_back(triad);
    }
    else if (vertex->data.id == _IF) {
        // Первый ребенок - условие перехода
        // После него должен быть условный переход
        Triad triad;
        triad.operation = &vertex->data;
        int oldNumTr = numTr;
        // Рекурсия
        makeTriads(vertex->children[0], numTr);
        if (oldNumTr == numTr) {
            triad.operand1 = &vertex->children[0]->data;
        }
        else {
            std::string str = "[";
            std::ostringstream temp;
            temp << (numTr-1);
            str += temp.str();
            str += "]";
            Symbol* s = new Symbol(_OLD, str, isTokenTerm(_OLD));
            
            triad.operand1 = s;
        }
        Symbol* s = new Symbol(_OLD, "_OLD", isTokenTerm(_OLD));
        triad.operand2 = s;
        triad.triadNum = numTr;
        numTr++;
        triads.push_back(triad);
        // Второй ребенок - блок с командами
        // Рекурсия
        makeTriads(vertex->children[1], numTr);
        std::string str = "[";
        std::ostringstream temp;
        temp << (numTr+1);
        str += temp.str();
        str += "]";
        s->str = str;
        // Третий ребенок - блок с командами
        Triad triad1;
        s = new Symbol(_GOTO, pTT(_GOTO).c_str(), isTokenTerm(_GOTO));
        triad1.operation = s;
        s = new Symbol(_OLD, "_OLD", isTokenTerm(_OLD));
        triad1.operand1 = s;
        triad1.operand2 = NULL;
        triad1.triadNum = numTr;
        numTr++;
        triads.push_back(triad1);
        // Рекурсия
        if (vertex->children.size() == 3) makeTriads(vertex->children[2], numTr);
        str = "[";
        std::ostringstream temp1;
        temp1 << (numTr);
        str += temp1.str();
        str += "]";
        s->str = str;
    }
    else if (vertex->data.id == _WHILE) {
        // Первый ребенок - условие перехода
        // После него должен быть условный переход
        Triad triad;
        Symbol* s = new Symbol(_IF, pTT(_IF).c_str(), isTokenTerm(_IF));
        triad.operation = s;
        int oldNumTr = numTr;
        // Рекурсия
        makeTriads(vertex->children[0], numTr);
        if (oldNumTr == numTr) {
            triad.operand1 = &vertex->children[0]->data;
        }
        else {
            std::string str = "[";
            std::ostringstream temp;
            temp << (numTr-1);
            str += temp.str();
            str += "]";
            Symbol* s = new Symbol(_OLD, str, isTokenTerm(_OLD));
            
            triad.operand1 = s;
        }
        s = new Symbol(_OLD, "_OLD", isTokenTerm(_OLD));
        triad.operand2 = s;
        triad.triadNum = numTr;
        numTr++;
        triads.push_back(triad);
        // Второй ребенок - блок с командами
        // Рекурсия
        makeTriads(vertex->children[1], numTr);
        std::string str = "[";
        std::ostringstream temp;
        temp << (numTr+1);
        str += temp.str();
        str += "]";
        s->str = str;
        // В конец блока надо добавить безусловный переход к условию
        Triad triad1;
        s = new Symbol(_GOTO, pTT(_GOTO).c_str(), isTokenTerm(_GOTO));
        triad1.operation = s;
        str = "[";
        std::ostringstream temp1;
        temp1 << (oldNumTr);
        str += temp1.str();
        str += "]";
        s = new Symbol(_OLD, str, isTokenTerm(_OLD));
        triad1.operand1 = s;
        triad1.operand2 = NULL;
        triad1.triadNum = numTr;
        numTr++;
        triads.push_back(triad1);
    }
}

void VectorTriad::print() {
    for (int i = 0; i < triads.size(); i++) {
        std::cout << triads[i].toString() << std::endl;
    }
}
