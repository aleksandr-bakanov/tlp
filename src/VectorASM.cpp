/*
* Фигачим ассемблерный код
*/

class VectorASM {
public:
    VectorASM(std::vector<TableOfResource*> resourceTable, VectorTriad* vectorTriad);
    
    // Вектор со строками заголовка
    std::vector<std::string> head;
    // Вектор со строками объявления данных
    std::vector<std::string> data;
    // Вектор со строками команд
    std::vector<std::string> code;
    
    void print(std::ostream& out);

private:

    // Обрабатываем ресурсы
    void resourceToCode(std::vector<TableOfResource*> resourceTable);
    // Обрабатываем триады
    void triadsToCode(std::vector<TableOfResource*> resourceTable, VectorTriad* vectorTriad);
    
    // По названию _ID надо найти соответствующий ресурс
    Resource* idToResource(std::string str, std::vector<TableOfResource*> resourceTable, int numScope);
    
    // Добавляем код для конкатенации строк
    void addCodeConc();
    
};

// Обрабатываем ресурсы
void VectorASM::resourceToCode(std::vector<TableOfResource*> resourceTable) {
    for (int i = 0; i < resourceTable.size(); i++) {
        // Обходим map
        std::map<std::string, Resource>::iterator it;
        for (it = resourceTable[i]->table.begin(); it != resourceTable[i]->table.end(); it++) {
            // Записывать надо только переменные и константы
            if (it->second.res == R_VAR || it->second.res == R_CONST) {
                std::string str = "    ";
                
                str += resourceTable[i]->name;
                str += "_";
                str += it->second.name;
                str += "    ";
                if (it->second.type == V_INTEGER) {
                    str += "dd";
                }
                else if (it->second.type == V_REAL) {
                    str += "dd";
                }
                else if (it->second.type == V_BOOLEAN) {
                    str += "dd";
                }
                else if (it->second.type == V_STRING) {
                    str += "db";
                }
                str += "    ";
                if (it->second.type == V_INTEGER) {
                    if (it->second.value == "") {
                        str += "0";
                    }
                    else {
                        str += it->second.value;
                    }
                }
                else if (it->second.type == V_REAL) {
                    if (it->second.value == "") {
                        str += "0.0";
                    }
                    else {
                        str += it->second.value;
                    }
                }
                else if (it->second.type == V_BOOLEAN) {
                    if (it->second.value == "") {
                        str += "0";
                    }
                    else if (it->second.value == "_TRUE"){
                        str += "1";
                    }
                    else if (it->second.value == "_FALSE"){
                        str += "0";
                    }
                }
                else if (it->second.type == V_STRING) {
                    if (it->second.value.length() == 0) {
                        str += "0";
                    }
                    else {
                        str += it->second.value;
                        str += ", 0";
                    }
                }
                code.push_back(str);
            }
        }
    }
}

// По названию _ID надо найти соответствующий ресурс
Resource* VectorASM::idToResource(std::string str, std::vector<TableOfResource*> resourceTable, int numScope) {
    // TODO: Не понятно учитываются ли вложенные области видимости
    for (int i = numScope; i >= 0; i--) {
        std::map<std::string, Resource>::iterator it = resourceTable[i]->table.find(str);
        if (it != resourceTable[i]->table.end()) {
            return &(it->second);
        }
    }
}

// Обрабатываем триады
void VectorASM::triadsToCode(std::vector<TableOfResource*> resourceTable, VectorTriad* vectorTriad) {
    // TODO: Нет поддержки функций
    
    // Номер области видимости
    int numScope = -1;
    // Номер временной константы
    int numTempConst = 0;
    std::vector<Triad>::iterator it;
    for (it = vectorTriad->triads.begin(); it != vectorTriad->triads.end(); it++) {
        // std::string str = "    ";
        if (it->operation->id == _PROG) {
            if (it->operand1->id == _BEGIN) {
                numScope++;
                std::string str = resourceTable[numScope]->name;
                str += " PROC";
                code.push_back(str);
            }
            else if (it->operand1->id == _END) {
                if (numScope == 0) {
                    code.push_back("    invoke ExitProcess, 0");
                    code.push_back("    ret");
                }
                else {
                    code.push_back("    ret");
                }
                std::string str = resourceTable[numScope]->name;
                str += " endp";
                code.push_back(str);
                code.push_back("\n");
            }
        }
        else if (it->operation->id == _WRITE) {
            std::string str = "    print ";
            if (it->operand1->id == _ID) {
                // По названию _ID надо найти соответствующий ресурс
                Resource* res = idToResource(it->operand1->value(), resourceTable, numScope);
                // В зависимости от типа ресурса разная обработка
                if (res->type == V_STRING) {
                    str += "addr ";
                    str += resourceTable[numScope]->name;
                    str += "_";
                    str += it->operand1->value();
                }
                else if (res->type == V_INTEGER) {
                    str += "str$(";
                    str += resourceTable[numScope]->name;
                    str += "_";
                    str += it->operand1->value();
                    str += ")";
                }
                else if (res->type == V_BOOLEAN) {
                    str += "\"";
                    if (it->operand1->value() == "_TRUE") {
                        str += "1";
                    }
                    else {
                        str += "0";
                    }
                    str += "\"";
                }
                else if (res->type == V_REAL) {
                    // TODO: Это неправильно
                    str += "str$(";
                    str += resourceTable[numScope]->name;
                    str += "_";
                    str += it->operand1->value();
                    str += ")";
                }
                str += ",13,10";
                code.push_back(str);
            }
            else if (it->operand1->id == _STR) {
                std::string temp = it->operand1->value();
                temp.replace(0, 1, "\"");
                temp.replace(temp.length()-1, 1, "\"");
                str += temp;
                str += ",13,10";
                code.push_back(str);
            }
            else if (it->operand1->id == _NUM || it->operand1->id == _RC) {
                str += "\"";
                str += it->operand1->value();
                str += "\"";
                str += ",13,10";
                code.push_back(str);
            }
            else if (it->operand1->id == _OLD) {
                str += "str$(triad_result)";
                str += ",13,10";
                code.push_back(str);
            }
        }
        else if (it->operation->id == _EQ) {
            // Второй операнд
            if (it->operand2->id == _ID) {
                // По названию _ID надо найти соответствующий ресурс
                Resource* res = idToResource(it->operand2->value(), resourceTable, numScope);
                // В зависимости от типа ресурса разная обработка
                if (res->type == V_STRING) {
                    // TODO
                    code.push_back("    cld");
                    std::string str = "    invoke StrLen, addr ";
                    str += resourceTable[numScope]->name;
                    str += "_";
                    str += it->operand2->value();
                    code.push_back(str);
                    code.push_back("    add eax, 1");
                    str = "    mov esi, offset ";
                    str += resourceTable[numScope]->name;
                    str += "_";
                    str += it->operand2->value();
                    code.push_back(str);
                    str = "    mov edi, offset ";
                    str += resourceTable[numScope]->name;
                    str += "_";
                    str += it->operand1->value();
                    code.push_back(str);
                    code.push_back("    mov ecx, eax");
                    code.push_back("    rep movsb");
                }
                else if (res->type == V_INTEGER || res->type == V_BOOLEAN || res->type == V_REAL) {
                    // To registr
                    std::string str = "    mov eax, ";
                    str += resourceTable[numScope]->name;
                    str += "_";
                    str += it->operand2->value();
                    code.push_back(str);
                    // To var
                    str = "    mov ";
                    str += resourceTable[numScope]->name;
                    str += "_";
                    str += it->operand1->value();
                    str += ", eax";
                    code.push_back(str);
                }
            }
            else if (it->operand2->id == _STR) {
                // Создаем временную переменную
                std::string tempName = "temp_";
                char t[32];
                itoa(numTempConst, t, 10);
                tempName += std::string(t);
                numTempConst++;
                std::string str = "    ";
                str += tempName;
                str += "    db    ";
                str += it->operand2->value();
                str += ", 0";
                data.push_back(str);
                // Пишем код на присвоение
                code.push_back("    cld");
                str = "    invoke StrLen, addr ";
                str += tempName;
                code.push_back(str);
                code.push_back("    add eax, 1");
                str = "    mov esi, offset ";
                str += tempName;
                code.push_back(str);
                str = "    mov edi, offset ";
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand1->value();
                code.push_back(str);
                code.push_back("    mov ecx, eax");
                code.push_back("    rep movsb");
            }
            else if (it->operand2->id == _NUM) {
                std::string str = "    mov ";
                // Первый операнд
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand1->value();
                str += ", ";
                str += it->operand2->value();
                code.push_back(str);
            }
            else if (it->operand2->id == _TRUE) {
                std::string str = "    mov ";
                // Первый операнд
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand1->value();
                str += ", 1";
                code.push_back(str);
            }
            else if (it->operand2->id == _FALSE) {
                std::string str = "    mov ";
                // Первый операнд
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand1->value();
                str += ", 0";
                code.push_back(str);
            }
            else if (it->operand2->id == _RC) {
                // Создаем временную переменную
                std::string tempName = "temp_";
                char t[32];
                itoa(numTempConst, t, 10);
                tempName += std::string(t);
                numTempConst++;
                std::string str = "    ";
                str += tempName;
                str += "    dd    ";
                str += it->operand2->value();
                data.push_back(str);
                // Пишем код на присвоение
                // To registr
                str = "    mov eax, ";
                str += tempName;
                code.push_back(str);
                // To var
                str = "    mov ";
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand1->value();
                str += ", eax";
                code.push_back(str);
            }
            else if (it->operand2->id == _OLD) {
                // To registr
                std::string str = "    mov eax, triad_result";
                code.push_back(str);
                // To var
                str = "    mov ";
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand1->value();
                str += ", eax";
                code.push_back(str);
            }
        }
        else if (it->operation->id == _LEN) {
            if (it->operand1->id == _ID) {
                std::string str = "    invoke StrLen, addr ";
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand1->value();
                code.push_back(str);
                code.push_back("    mov triad_result, eax");
            }
            else if (it->operand1->id == _STR) {
                // Создаем временную переменную
                std::string tempName = "temp_";
                char t[32];
                itoa(numTempConst, t, 10);
                tempName += std::string(t);
                numTempConst++;
                std::string str = "    ";
                str += tempName;
                str += "    db    ";
                str += it->operand1->value();
                str += ", 0";
                data.push_back(str);
                // Код
                str = "    invoke StrLen, addr ";
                str += tempName;
                code.push_back(str);
                code.push_back("    mov triad_result, eax");
            }
        }
        else if (it->operation->id == _PLUS || it->operation->id == _MINUS || it->operation->id == _MULT || it->operation->id == _DIV) {
            // Первый операнд
            if (it->operand1->id == _ID) {
                std::string str = "    mov eax, ";
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand1->value();
                code.push_back(str);
            }
            else if (it->operand1->id == _OLD) {
                std::string str = "    mov eax, triad_result";
                code.push_back(str);
            }
            // _NUM, _RC
            else {
                // Создаем временную переменную
                std::string tempName = "temp_";
                char t[32];
                itoa(numTempConst, t, 10);
                tempName += std::string(t);
                numTempConst++;
                std::string str = "    ";
                str += tempName;
                str += "    dd    ";
                str += it->operand1->value();
                data.push_back(str);
                // Код
                str = "    mov eax,  ";
                str += tempName;
                code.push_back(str);
            }
            // Второй операнд
            if (it->operand2->id == _ID) {
                std::string str = "    mov ebx, ";
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand2->value();
                code.push_back(str);
            }
            else if (it->operand2->id == _OLD) {
                std::string str = "    mov ebx, triad_result";
                code.push_back(str);
            }
            // _NUM, _RC
            else {
                // Создаем временную переменную
                std::string tempName = "temp_";
                char t[32];
                itoa(numTempConst, t, 10);
                tempName += std::string(t);
                numTempConst++;
                std::string str = "    ";
                str += tempName;
                str += "    dd    ";
                str += it->operand2->value();
                data.push_back(str);
                // Код
                str = "    mov ebx, ";
                str += tempName;
                code.push_back(str);
            }
            // Арифметическая операция
            if (it->operation->id == _PLUS) {
                code.push_back("    add eax, ebx");
            }
            else if (it->operation->id == _MINUS) {
                code.push_back("    sub eax, ebx");
            }
            else if (it->operation->id == _MULT) {
                code.push_back("    mul ebx");
            }
            else if (it->operation->id == _DIV) {
                code.push_back("    div ebx");
            }
            code.push_back("    mov triad_result, eax");
        }
        else if (it->operation->id == _IF) {
            if (it->operand1->id == _ID) {
                std::string str = "    .if ";
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand1->value();
                code.push_back(str);
            }
            else if (it->operand1->id == _OLD) {
                code.push_back("    .if triad_result");
            }
        }
        else if (it->operation->id == _ELSE) {
            code.push_back("    .else");
        }
        else if (it->operation->id == _ENDIF) {
            code.push_back("    .endif");
        }
        else if (it->operation->id == _WHILE) {
            if (it->operand1->id == _ID) {
                std::string str = "    .while ";
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand1->value();
                code.push_back(str);
            }
            else if (it->operand1->id == _OLD) {
                code.push_back("    .while triad_result");
            }
        }
        else if (it->operation->id == _ENDW) {
            code.push_back("    .endw");
        }
        else if (it->operation->id == _REL) {
            // Первый операнд
            if (it->operand1->id == _ID) {
                std::string str = "    mov eax, ";
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand1->value();
                code.push_back(str);
            }
            else if (it->operand1->id == _OLD) {
                std::string str = "    mov eax, triad_result";
                code.push_back(str);
            }
            // _NUM, _RC
            else {
                // Создаем временную переменную
                std::string tempName = "temp_";
                char t[32];
                itoa(numTempConst, t, 10);
                tempName += std::string(t);
                numTempConst++;
                std::string str = "    ";
                str += tempName;
                str += "    dd    ";
                str += it->operand1->value();
                data.push_back(str);
                // Код
                str = "    mov eax,  ";
                str += tempName;
                code.push_back(str);
            }
            // Второй операнд
            if (it->operand2->id == _ID) {
                std::string str = "    mov ebx, ";
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand2->value();
                code.push_back(str);
            }
            else if (it->operand2->id == _OLD) {
                std::string str = "    mov ebx, triad_result";
                code.push_back(str);
            }
            // _NUM, _RC
            else {
                // Создаем временную переменную
                std::string tempName = "temp_";
                char t[32];
                itoa(numTempConst, t, 10);
                tempName += std::string(t);
                numTempConst++;
                std::string str = "    ";
                str += tempName;
                str += "    dd    ";
                str += it->operand2->value();
                data.push_back(str);
                // Код
                str = "    mov ebx, ";
                str += tempName;
                code.push_back(str);
            }
            code.push_back("    cmp eax, ebx");
            code.push_back("    mov eax, 0");
            // Логическая операция
            if (it->operation->value() == "=") {
                code.push_back("    setz al");
            }
            else if (it->operation->value() == "<") {
                code.push_back("    setb al");
            }
            else if (it->operation->value() == "<=") {
                code.push_back("    setbe al");
            }
            else if (it->operation->value() == ">") {
                code.push_back("    seta al");
            }
            else if (it->operation->value() == ">=") {
                code.push_back("    setae al");
            }
            else if (it->operation->value() == "<>") {
                code.push_back("    setnz al");
            }
            code.push_back("    mov triad_result, eax");
        }
        else if (it->operation->id == _AND  || it->operation->id == _OR) {
            // TODO: А вот фигушки, тут могут прийти две триады
            // Первый операнд
            if (it->operand1->id == _ID) {
                std::string str = "    mov eax, ";
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand1->value();
                code.push_back(str);
            }
            else if (it->operand1->id == _OLD) {
                std::string str = "    mov eax, triad_result";
                code.push_back(str);
            }
            // Второй операнд
            if (it->operand2->id == _ID) {
                std::string str = "    mov ebx, ";
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand2->value();
                code.push_back(str);
            }
            else if (it->operand2->id == _OLD) {
                std::string str = "    mov ebx, triad_result";
                code.push_back(str);
            }
            // Логическая операция
            if (it->operation->id == _AND) {
                code.push_back("    and eax, ebx");
            }
            else if (it->operation->id == _OR) {
                code.push_back("    or eax, ebx");
            }
            code.push_back("    mov eax, 0");
            code.push_back("    setnz al");
            code.push_back("    mov triad_result, eax");
        }
        else if (it->operation->id == _LABEL) {
            // Первый операнд
            std::string str = "";
            str += resourceTable[numScope]->name;
            str += "_";
            str += it->operand1->value();
            str += ":";
            code.push_back(str);
        }
        else if (it->operation->id == _GOTO) {
            // Первый операнд
            std::string str = "    jmp ";
            str += resourceTable[numScope]->name;
            str += "_";
            str += it->operand1->value();
            code.push_back(str);
        }
        else if (it->operation->id == _READ) {
            // TODO: Работает только для строк
            
            // По названию _ID надо найти соответствующий ресурс
            Resource* res = idToResource(it->operand1->value(), resourceTable, numScope);
            // В зависимости от типа ресурса разная обработка
            if (res->type == V_STRING) {
                code.push_back("    push 100");
                std::string str = "    push offset ";
                str += resourceTable[numScope]->name;
                str += "_";
                str += it->operand1->value();
                code.push_back(str);
                code.push_back("    call StdIn");
            }
            else if (res->type == V_INTEGER || res->type == V_BOOLEAN || res->type == V_REAL) {
                // TODO
            }
        }
        else if (it->operation->id == _CONC) {
            // Первый операнд
            std::string name1;
            if (it->operand1->id == _ID) {
                name1 = resourceTable[numScope]->name;
                name1 += "_";
                name1 += it->operand1->value();
            }
            else if (it->operand1->id == _STR) {
                // Создаем временную переменную
                name1 = "temp_";
                char t[32];
                itoa(numTempConst, t, 10);
                name1 += std::string(t);
                numTempConst++;
                std::string str = "    ";
                str += name1;
                str += "    db    ";
                str += it->operand1->value();
                str += ", 0";
                data.push_back(str);
            }
            // Второй операнд
            std::string name2;
            if (it->operand2->id == _ID) {
                name2 = resourceTable[numScope]->name;
                name2 += "_";
                name2 += it->operand2->value();
            }
            else if (it->operand2->id == _STR) {
                // Создаем временную переменную
                name2 = "temp_";
                char t[32];
                itoa(numTempConst, t, 10);
                name2 += std::string(t);
                numTempConst++;
                std::string str = "    ";
                str += name2;
                str += "    db    ";
                str += it->operand2->value();
                str += ", 0";
                data.push_back(str);
            }
            std::string str = "    Invoke Str_concat, ADDR ";
            str += name1;
            str += ", ADDR ";
            str += name2;
            str += ", LENGTHOF ";
            str += name1;
            str += ", LENGTHOF ";
            str += name2;
            code.push_back(str);
        }
    }
}

// Добавляем код для конкатенации строк
void VectorASM::addCodeConc() {
    // Определение функции
    head.push_back("Str_concat PROTO,");
	head.push_back("    target:PTR BYTE,");
	head.push_back("    source:PTR BYTE,");
    head.push_back("    len1:dWORD,");
    head.push_back("    len2:dWORD");
    // Сама функция
    code.push_back("Str_concat PROC USES eax ebx ecx esi edi,");
	code.push_back("target:PTR BYTE,");
	code.push_back("source:PTR BYTE,");
    code.push_back("len1:dWORD,");
    code.push_back("len2:dWORD");
    code.push_back("cld");
    code.push_back("sub len1, 1");
    code.push_back("mov esi, target");
    code.push_back("mov edi, offset buffer1");
    code.push_back("mov ecx, len1");
    code.push_back("rep movsb");
    
    code.push_back("mov eax, len1");
	code.push_back("mov ecx, len2");
	code.push_back("mov esi, source");
	code.push_back("mov edi, offset buffer1");

    code.push_back("KGBL1:");
	code.push_back("add edi, eax");
	code.push_back("mov ebx, [esi]");
	code.push_back("mov [edi], ebx");

	code.push_back("add eax, 1");
	code.push_back("add esi, 1");
	code.push_back("loop KGBL1");

	code.push_back("ret");
    
code.push_back("Str_concat ENDP");
}

VectorASM::VectorASM(std::vector<TableOfResource*> resourceTable, VectorTriad* vectorTriad) {
    // Шапка
    head.push_back(".386");
    head.push_back(".model flat, stdcall");
    head.push_back("option casemap :none");
    // head.push_back("include \\masm32\\include\\windows.inc");
    // head.push_back("include \\masm32\\include\\kernel32.inc");
    // head.push_back("include \\masm32\\include\\masm32.inc");
    head.push_back("include \\masm32\\include\\masm32rt.inc");
    head.push_back("includelib \\masm32\\lib\\kernel32.lib");
    head.push_back("includelib \\masm32\\lib\\masm32.lib");
    // Обрабатываем ресурсы
    data.push_back(".data");
    data.push_back("    triad_result    dd    0");
    resourceToCode(resourceTable);
    // Обрабатываем триады
    code.push_back(".code");
    code.push_back("start:");
    code.push_back("\n");
    
    triadsToCode(resourceTable, vectorTriad);
    
    //addCodeConc();
    code.push_back("end start");
}

void VectorASM::print(std::ostream& out) {
    for (int i = 0; i < head.size(); i++) {
        out << head[i] << std::endl;
    }
    for (int i = 0; i < data.size(); i++) {
        out << data[i] << std::endl;
    }
    for (int i = 0; i < code.size(); i++) {
        out << code[i] << std::endl;
    }
}