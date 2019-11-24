
#include "Operand.h"

Operand::Operand(Identifier *i) {
    id = i;
}

Operand::Operand(int v) {
    val = v;
}

Operand::~Operand() {
    // id is not deleted here because it shares a pointer with Program
}

void Operand::getID(Identifier *i) {
    i = id;
}

void Operand::setID(Identifier *i) {
    id = i;
}

int Operand::getVal() {
    if(id == nullptr) {
        return val;
    }
    else {
        return(id->getValue());
    }
}