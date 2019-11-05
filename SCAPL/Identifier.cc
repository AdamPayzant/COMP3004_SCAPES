#include "Identifier.h"

Identifier::Identifier(std::string &n) {
    name = n;
}

void Identifier::getName(std::string &n) {
    n = name;
}