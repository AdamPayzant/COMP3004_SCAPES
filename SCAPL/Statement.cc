#include "Statement.h"
#include "Program.h"

Statement::~Statement() {
    if(o1 != nullptr) {
        delete(o1);
    }
    if(o2 != nullptr) {
        delete(o2);
    }
}

std::string Statement::getName(){
    return subtype;
}

Operand* Statement::getOperand1() {
    return(o1);
}

void Statement::setOperand1(Operand* operandPtr) {
    o1 = operandPtr;
}

Operand* Statement::getOperand2() {
    return(o2);
}

void Statement::setOperand2(Operand* operandPtr) {
    o2 = operandPtr;
}

Label* Statement::getLabel() {
    return(label);
}

void Statement::setLabel(Label *l) {
    label = l;
}
