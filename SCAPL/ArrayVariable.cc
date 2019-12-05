#include "ArrayVariable.h"
#include "ArrAccess.h"
#include <cstdlib>
#include <iostream>

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
    std::cout<<"create"<<std::endl;
    size = s;
    std::cout<<"create"<<std::endl;
    arr = new Variable*[size];
    std::cout<<"create"<<std::endl;
    for(int i = 0; i < size; i++) {
      std::cout<<"create"<<std::endl;
        arr[i] = new IntegerVariable();
    }
    std::cout<<"create"<<std::endl;
}

void ArrayVariable::setAt(int loc, int val) {
    IntegerVariable *cur = (IntegerVariable *) arr[loc];
    cur->setVal(val);
}

Variable* ArrayVariable::getAt(int pos) {
    return(arr[pos]);
}
