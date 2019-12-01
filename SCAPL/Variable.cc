#include "Variable.h"

Variable::Variable(){
    name = "ANON";
}

Variable::Variable(std::string &n) {
    name = n;
}
