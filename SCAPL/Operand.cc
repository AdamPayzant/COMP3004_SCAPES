#include "Operand.h"
#include "ArrAccess.h"

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

void Operand::getID(Identifier** i) {
    *i = id;
}

Identifier* Operand::getIDPtr() {
    return id;
}

void Operand::setID(Identifier* i) {
    i = id;
}

int Operand::getVal() {
    if (id->getSubtype() == "Literal") {
        //cast to Literal
        Literal *temp = (Literal *) id;
        return(temp->getVal());
    } else if (id->getSubtype() == "Variable") {
        //cast to IntegerVariable
        if (((Variable *) id)->getSubtype() == "IntegerVariable") {
            IntegerVariable *temp = (IntegerVariable *) id;
            return(temp->getVal());
        } else {
            //error case
        }
    } else if (id->getSubtype() == "ArrAccess") {
        //cast to ArrAccess
        ArrAccess *temp = (ArrAccess *) id;
        return(temp->getVal());
    } else {
        //error case
    }
}

std::string Operand::getOut() {
    Value *temp = (Value *) id;
    return(temp->getOut());
}

void Operand::setVal(int v) {
    Value *temp = (Value *) id;
    temp->setVal(v);
}
