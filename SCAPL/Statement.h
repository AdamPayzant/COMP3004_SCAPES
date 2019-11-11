#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>

#include "Program.h"
#include "Operand.h"
#include "Label.h"

class Statement {
    public:
        virtual void compile(std::string &) = 0;
        virtual void run() = 0;
    protected:
        // Master program
        Program *master;
        // Two operands (Either can be NULL)
        Operand *o1;
        Operand *o2;
        // Label (Can be NULL)
        Label *label;
};

#endif