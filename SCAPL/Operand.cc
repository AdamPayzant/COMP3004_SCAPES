#include "Operand.h"

Operand::Operand(Identifier *i) {
    id = i;
}


Operand::~Operand() {
    // id is not deleted here because it shares a pointer with Program
}

void Operand::getID(Identifier *i) {
    i = id;
}