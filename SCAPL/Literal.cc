#include "Literal.h"

Literal::Literal(int v) {
    val = v;
    subtype = "Literal";
}

Literal::~Literal() {

}

int Literal::getVal() {
    return(val);
}

void Literal::setVal(int i) {
    return;
}