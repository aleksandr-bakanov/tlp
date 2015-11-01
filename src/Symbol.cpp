// Description of any symbol
class Symbol {
public:
    Symbol(token_t id, std::string& str, bool isToken);
    Symbol(token_t id, const char* str, bool isToken);
    // ID from token enum
    token_t id;
    // String representation
    std::string str;
    // True if token, false if non terminal
    bool isToken;
    
    std::string value();
};

Symbol::Symbol(token_t id, std::string& str, bool isToken) {
    this->id = id;
    this->str = str;
    this->isToken = isToken;
}

Symbol::Symbol(token_t id, const char* str, bool isToken) {
    this->id = id;
    this->str = std::string(str);
    this->isToken = isToken;
}

std::string Symbol::value() {
    size_t start = str.find("[");
    if (start == std::string::npos)
        return str;
    size_t end = str.find("]");
    return str.substr(start + 1, end - start - 1);
}
