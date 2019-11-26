#include "IntegerVariable.h"

IntegerVariable::IntegerVariable() {
    subtype = "IntegerVariable";
    val = 0;
}

IntegerVariable::IntegerVariable(std::string &n) : Variable(n){
    subtype = "IntegerVariable";
    val = 0;
}

int IntegerVariable::getVal() {
    return val;
}

void IntegerVariable::setVal(int v) {
    val = v;
}