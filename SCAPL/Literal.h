#ifndef LITERAL_H
#define LITERAL_H

#include "Identifier.h"
#include "Value.h"

class Literal: public Identifier, public Value {
    public:
        Literal(int);
        ~Literal();
        int getVal();
        void setVal(int);
    private:
        int val;
};

#endif