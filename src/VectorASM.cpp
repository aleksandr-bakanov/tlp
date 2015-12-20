// TODO: Нет проверок на совпадение переменных с зарезервированными словами ассемблера

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
                    str += "db";
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
                if (res->type == V_STRING) {
                    str += "addr ";
                    str += resourceTable[numScope]->name;
                    str += "_";
                    str += it->operand1->value();
                }
                else {
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
                // TODO
            }
        }
        
        
        
        
    }
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
    resourceToCode(resourceTable);
    // Обрабатываем триады
    code.push_back(".code");
    code.push_back("start:");
    code.push_back("\n");
    
    triadsToCode(resourceTable, vectorTriad);
    
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