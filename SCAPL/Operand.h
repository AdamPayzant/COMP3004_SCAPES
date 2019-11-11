#ifndef OPERAND_H
#define OPERAND_H

#include "Identifier.h"

class Operand {
    public:
        Operand(Identifier *);
        ~Operand();

        void getID(Identifier *);
    private:
        Identifier *id;
};

#endif