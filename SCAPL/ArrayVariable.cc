#include "ArrayVariable.h"

ArrayVariable::ArrayVariable(int s, std::string &n) : Variable(n){
    size = s;
}

ArrayVariable::~ArrayVariable() {
    for(int i = 0; i < size; i++) {
        delete(arr[i]);
    }
    delete(arr);
}

void ArrayVariable::create() {
    arr = new Variable*[size];
    for(int i = 0; i < size; i++) {
        arr[i] = new IntegerVariable();
    }
}

void ArrayVariable::setAt(int v) {

}

Variable* ArrayVariable::getAt(int pos) {

}