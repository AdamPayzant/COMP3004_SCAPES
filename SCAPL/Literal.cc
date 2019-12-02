#include "Literal.h"


Literal::Literal(std::string s) {
    str = s;
    subtype = "Literal";
}

Literal::~Literal() {

}

int Literal::getVal() {
    return(std::stoi(str));
}

std::string Literal::getOut() {
    return(str);
}

void Literal::setVal(int i) {
    return;
}
