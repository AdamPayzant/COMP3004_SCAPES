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

/*
int Operand::getVal() {
    std::cout<<"val: this operand is a "<<id->getSubtype()<<std::endl;
    if (id->getSubtype() == "Literal") {
        //cast to Literal
        Literal *temp = (Literal *) id;
        return(temp->getVal());
    } else if (id->getSubtype() == "Variable") {
        //cast to IntegerVariable
        if (((Variable *) id)->getSubtype() == "IntegerVariable") {
            IntegerVariable *temp = (IntegerVariable *) id;
            return(temp->getVal());
        } else {
            //error case
        }
    } else if (id->getSubtype() == "ArrAccess") {
        //cast to ArrAccess
        ArrAccess *temp = (ArrAccess *) id;
        return(temp->getVal());
    } else {
        //error case
    }
}

std::string Operand::getOut() {
  std::cout<<"out: this operand is a "<<id->getSubtype()<<std::endl;
  if (id->getSubtype() == "Literal") {
      //cast to Literal
      Literal *temp = (Literal *) id;
      return(temp->getOut());
  } else if (id->getSubtype() == "Variable") {
      //cast to IntegerVariable
      if (((Variable *) id)->getSubtype() == "IntegerVariable") {
          IntegerVariable *temp = (IntegerVariable *) id;
          return(temp->getOut());
      } else {
          //error case
      }
  } else if (id->getSubtype() == "ArrAccess") {
      //cast to ArrAccess
      ArrAccess *temp = (ArrAccess *) id;
      return(temp->getOut());
  } else {
      //error case
  }
}

void Operand::setVal(int v) {
    std::cout<<"set: this operand is a "<<id->getSubtype()<<std::endl;
    if (id->getSubtype() == "Variable") {
        //cast to IntegerVariable
        if (((Variable *) id)->getSubtype() == "IntegerVariable") {
            IntegerVariable *temp = (IntegerVariable *) id;
            temp->setVal(v);
        } else {
            //error case
        }
    } else if (id->getSubtype() == "ArrAccess") {
        //cast to ArrAccess
        ArrAccess *temp = (ArrAccess *) id;
        temp->setVal(v);
    } else {
        //error case
    }
}
*/
