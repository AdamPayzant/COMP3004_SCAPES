#include "IntegerVariable.h"

IntegerVariable::IntegerVariable() {
    
}

IntegerVariable::IntegerVariable(std::string &n) : Variable(n){
    val = 0;
    subtype = "IntegerVariable";
}

int IntegerVariable::getVal() {
    return val;
}

void IntegerVariable::setVal(int v) {
    val = v;
}