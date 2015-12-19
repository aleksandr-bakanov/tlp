// TODO: ��� �������� �� ���������� ���������� � ������������������ ������� ����������

/*
* ������� ������������ ���
*/

class VectorASM {
public:
    VectorASM(std::vector<TableOfResource*> resourceTable, VectorTriad* vectorTriad);
    
    // ������ �� �������� ���������
    std::vector<std::string> head;
    
    // ������ �� �������� ���������� ������
    std::vector<std::string> data;
    
    // ������ �� �������� ������
    std::vector<std::string> code;
    
    // ������������ �������
    void resourceToCode(std::vector<TableOfResource*> resourceTable);
    // ������������ ������
    void triadsToCode(std::vector<TableOfResource*> resourceTable, VectorTriad* vectorTriad);
    
    void printToConsole();
};

// ������������ �������
void VectorASM::resourceToCode(std::vector<TableOfResource*> resourceTable) {
    // TODO: ��� ��������� �������
    for (int i = 0; i < resourceTable.size(); i++) {
        std::cout << "qwert" << std::endl;
        // ������� map
        std::map<std::string, Resource>::iterator it;
        for (it = resourceTable[i]->table.begin(); it != resourceTable[i]->table.end(); it++) {
            // ���������� ���� ������ ���������� � ���������
            if (it->second.res == R_VAR || it->second.res == R_CONST) {
                std::string str = "    ";
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
                    str += it->second.value;
                    str += ", 0";
                }
                code.push_back(str);
            }
        }
    }
}

// ������������ ������
void triadsToCode(std::vector<TableOfResource*> resourceTable, VectorTriad* vectorTriad) {
    // ����� ������� ���������
    int amountScope = -1;
    std::vector<Triad>::iterator it;
    for (it = vectorTriad->triads.begin(); it != vectorTriad->triads.end(); it++) {
        std::string str = "    ";
        if (it->operation->id == _WRITE) {
            str += "invoke StdOut, ";
            if (it->operand1->id == _ID) {
                str += "addr ";
                str += it->operand1->value();
            }
            else if (it->operand1->id == _STR) {
                str += "addr ";
                str += it->operand1->value();
            }
        }
        
        
        
        
    }
}

VectorASM::VectorASM(std::vector<TableOfResource*> resourceTable, VectorTriad* vectorTriad) {
    // �����
    head.push_back(".386");
    head.push_back(".model flat, stdcall");
    head.push_back("option casemap :none");
    head.push_back("include \\masm32\\include\\windows.inc");
    head.push_back("include \\masm32\\include\\kernel32.inc");
    head.push_back("include \\masm32\\include\\masm32.inc");
    head.push_back("includelib \\masm32\\lib\\kernel32.lib");
    head.push_back("includelib \\masm32\\lib\\masm32.lib");
    // ������������ �������
    data.push_back(".data");
    resourceToCode(resourceTable);
    // ������������ ������
    code.push_back(".code");
    code.push_back("start:");
    
    // triadsToCode(vectorTriad);
    
    code.push_back("end start");
}

void VectorASM::printToConsole() {
    for (int i = 0; i < head.size(); i++) {
        std::cout << head[i] << std::endl;
    }
    for (int i = 0; i < data.size(); i++) {
        std::cout << data[i] << std::endl;
    }
    for (int i = 0; i < code.size(); i++) {
        std::cout << code[i] << std::endl;
    }
}