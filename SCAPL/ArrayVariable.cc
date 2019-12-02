#include "ArrayVariable.h"

ArrayVariable::ArrayVariable(std::string &n) : Variable(n) {
    subtype = "ArrayVariable";
}

ArrayVariable::~ArrayVariable() {
    for(int i = 0; i < size; i++) {
        delete(arr[i]);
    }
    delete(arr);
}

void ArrayVariable::create(int s) {
    size = s;
    arr = new Variable*[size];
    for(int i = 0; i < size; i++) {
        arr[i] = new IntegerVariable();
    }
}

void ArrayVariable::setAt(int loc, int val) {
    IntegerVariable *cur = (IntegerVariable *) arr[loc];
    cur->setVal(val);
}

Variable* ArrayVariable::getAt(int pos) {
    return(arr[pos]);
}