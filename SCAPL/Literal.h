#ifndef LITERAL_H
#define LITERAL_H

#include "Identifier.h"
#include "Value.h"

class Literal: public Identifier, public Value {
    public:
        Literal(int);
        ~Literal();
        int getVal();
    private:
        int val;
};

#endif