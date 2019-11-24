#include "Statement.h"

Statement::~Statement() {
    if(o1 != nullptr) {
        delete(o1);
    }
    if(o2 != nullptr) {
        delete(o2);
    }
}

Operand* Statement::getOperand1() {
    return(o1);
}

Operand* Statement::getOperand2() {
    return(o2);
}

Label* Statement::getLabel() {
    return(label);
}