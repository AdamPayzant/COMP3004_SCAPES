#include "Variable.h"

Variable::Variable(std::string &n) {
    name = n;
    subType = "Variable";
}

void Variable::getVal(int &v) {
    v = value;
}

void Variable::setVal(int &v) {
    value = v;
}