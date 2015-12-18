#include <iostream>
#include <fstream>
#include <deque>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <wchar.h>
#include <map>
#include <sstream>

#include "state_t.cpp"
#include "token_t.cpp"
#include "Symbol.cpp"
#include "lexical.cpp"
#include "grams.cpp"
#include "TableOfResource.cpp"
#include "syntactic.cpp"
#include "Tree.cpp"
#include "Triad.cpp"
#include "VectorTriad.cpp"


void printHelp() {
    std::cout << "Usage: main <file_name>\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printHelp();
    }
    
    std::ifstream in (argv[1]);
    if (!in.is_open()) {
        std::cout << "Cannot open " << argv[1] << ".\n";
        return 0;
    }
    
    std::cout << "\n\nLexical analize ...\n";
    
    // Lexical analysis
    lexicalAnalysis(in);
    
    std::cout << "\n\nLexical analize complete\n";

    std::cout << "\n\nSyntactical analize ...\n";
    
    // Initialization grammars
    initGrams();
    
    // Syntactic analysis
    if (!syntacticAnalysis()) {
        return 0;
    }
    
    // Вывод всех использованных правил сверток
#ifdef DEBUG
    Tree::printFoldRules(outFoldRules);
    std::cout << std::endl;
#endif
    // Создание дерева вывода по использованным правилам сверток и количеству областей видимости в программе 
    Tree* tree = new Tree(outFoldRules, resourceTables.size());
    std::cout << std::endl;
    std::cout << "Output tree:" << std::endl;
    tree->print();
    
    // Создаем список триад
    VectorTriad* vectorTriad = new VectorTriad(tree);
    std::cout << std::endl;
    std::cout << "Triads:" << std::endl;
    vectorTriad->print();
    
    return 0;
}
