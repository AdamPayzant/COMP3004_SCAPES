#include "Literal.h"

Literal::Literal(int v) {
    val = v;
    subtype = "LiteralInt";
}

Literal::Literal(std::string s) {
    str = s;
    subtype = "LiteralString";
}

Literal::~Literal() {

}

int Literal::getVal() {
    return(val);
}

std::string Literal::getOut() {
    if(str.empty()) {
        return(std::to_string(val));
    }
    else {
        return(str);
    }
}

void Literal::setVal(int i) {
    return;
}
