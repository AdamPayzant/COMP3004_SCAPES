
#include "Identifier.h"

void Identifier::getName(std::string& n) {
    n = this->name;
}

std::string Identifier::getNameValue(){
    return this->name;
}

std::string Identifier::getSubtype() {
    return this->subtype;
}
