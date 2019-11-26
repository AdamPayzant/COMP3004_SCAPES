
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

Identifier* Operand::getIDPtr() {
    return id;
}

void Operand::setID(Identifier *i) {
    id = i;
}

int Operand::getVal() {
    IntegerVariable *temp = (IntegerVariable *) id;
    if(id == nullptr) {
        return val;
    }
    else {
        return(temp->getVal());
    }
}