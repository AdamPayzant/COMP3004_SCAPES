#include "Literal.h"
#include <cstdlib>
#include <iostream>


Literal::Literal(std::string s) {
    str = s;
    std::cout<<"literal constructor: "<<str<<std::endl;
    subtype = "Literal";
}

Literal::~Literal() {

}

int Literal::getVal() {
    std::cout<<str<<std::endl;
    return(std::stoi(str));
}

std::string Literal::getOut() {
    return(str);
}

void Literal::setVal(int i) {
    return;
}
