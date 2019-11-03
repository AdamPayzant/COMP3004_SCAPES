#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>

#include "Operand.h"
#include "Label.h"

class Statement {
    public:
        Statement();
        ~Statement();
        virtual void compile(std::string) = 0;
        virtual void run() = 0;
    private:
        // Two operands (Can be NULL)
        Operand o1;
        Operand o2;
        // Label (Can be NULL)
        Label label;
};

#endif