#include "Variable.h"

Variable::Variable(std::string &n) {
    name = n;
    subtype = "Variable";
}

void Variable::getVal(int &v) {
    v = value;
}

void Variable::setVal(int &v) {
    value = v;
}