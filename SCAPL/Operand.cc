
#include "Operand.h"

Operand::Operand(Identifier *i) {
    id = i;
}

Operand::~Operand() {
    // id is not deleted here because it shares a pointer with Program
    std::string name = id->getSubtype();
    if(name.compare("ArrAccess") == 0 || name.compare("Literal") == 0) {
        delete(id);
    }
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
    Value *temp = (Value *) id;
    return(temp->getVal());
}

std::string Operand::getOut() {
    Value *temp = (Value *) id;
    return(temp->getOut());
}

void Operand::setVal(int v) {
    Value *temp = (Value *) id;
    temp->setVal(v);
}