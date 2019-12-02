#include "IntegerVariable.h"

IntegerVariable::IntegerVariable(){
    subtype = "ANONIntegerVariable";
    val = 0;
}

IntegerVariable::IntegerVariable(std::string &n) : Variable(n){
    subtype = "IntegerVariable";
    val = 0;
}

int IntegerVariable::getVal() {
    return val;
}

std::string IntegerVariable::getOut() {
    return(std::to_string(val));
}

void IntegerVariable::setVal(int v) {
    val = v;
}
