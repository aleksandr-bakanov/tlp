/*
* Класс описывающий триаду
*/
class Triad {
public:
    Triad();
    
    int triadNum;
    Symbol* operation;
    Symbol* operand1;
    Symbol* operand2;    
    
    std::string toString();
};

Triad::Triad() {
    this->triadNum = -1;
    this->operation = NULL;
    this->operand1 = NULL;
    this->operand2 = NULL;
}

std::string Triad::toString() {
    std::string str;    
    std::ostringstream temp;
    temp << this->triadNum;
    str = temp.str();    
    str += " ";
    if (this->operation) {
        str += this->operation->str;
    }
    else {
        str += "___";
    }
    str += " ";
    if (this->operand1) {
        str += this->operand1->str;
    }
    else {
        str += "___";
    }
    str += " ";
    if (this->operand2) {
        str += this->operand2->str;
    }
    else {
        str += "___";
    }
    return str;
}