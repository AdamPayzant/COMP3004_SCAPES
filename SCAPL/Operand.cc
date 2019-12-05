#include "Operand.h"
#include "ArrAccess.h"
#include <iostream>

Operand::Operand(Identifier *i) {
    id = i;
}

Operand::~Operand() {
    // id is not deleted here because it shares a pointer with Program
    std::string name = id->getSubtype();
    if(name.compare("ArrAccess") == 0 || name.compare("Literal") == 0) {
        delete(id);
    }
}

void Operand::getID(Identifier** i) {
    *i = id;
}

Identifier* Operand::getIDPtr() {
    return id;
}

void Operand::setID(Identifier* i) {
    i = id;
}

int Operand::getVal() {
    std::cout<<"val: this operand is a "<<id->getSubtype()<<std::endl;
    if(id != nullptr){
        if(id->getSubtype().compare("IntegerVariable") == 0){
            return ((IntegerVariable*) id)->getVal();
        }
        else if(id->getSubtype().compare("ArrAccess") == 0){
            return ((ArrAccess*) id)->getVal();
        }
        else if(id->getSubtype().compare("Literal") == 0){
            return ((Literal *) id)->getVal();
        }
    }
    return -1;
}

std::string Operand::getOut() {
    if(id != nullptr){
        if(id->getSubtype().compare("IntegerVariable") == 0){
            return std::to_string(((IntegerVariable*) id)->getVal());
        }
        else if(id->getSubtype().compare("ArrAccess") == 0){
            return std::to_string(((ArrAccess*) id)->getVal());
        }
        else if(id->getSubtype().compare("Literal") == 0){
            return std::to_string(((Literal *) id)->getVal());
        }
    }
    return "";
}

void Operand::setVal(int v) {
    if(id != nullptr){
        if(id->getSubtype().compare("IntegerVariable") == 0){
            ((IntegerVariable*) id)->setVal(v);
        }
        else if(id->getSubtype().compare("ArrAccess") == 0){
            ((ArrAccess*) id)->setVal(v);
        }
        else if(id->getSubtype().compare("Literal") == 0){
            ((Literal *) id)->setVal(v);
        }
    }
    return;
}
