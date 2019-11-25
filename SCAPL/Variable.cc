
#include "Variable.h"

Variable::Variable(std::string &n) {
    name = n;
    subtype = "Variable";
    value = 0;
}

int Variable::getVal() {
    return(value);
}

void Variable::setVal(int &v) {
    value = v;
}
