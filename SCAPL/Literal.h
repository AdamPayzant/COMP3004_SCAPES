#ifndef LITERAL_H
#define LITERAL_H

#include "Identifier.h"
#include "Value.h"

class Literal: public Identifier, public Value {
    public:
        Literal(int);
        Literal(std::string);
        ~Literal();
        int getVal();
        std::string getOut();
        void setVal(int);
    private:
        int val;
        std::string str;
};

#endif