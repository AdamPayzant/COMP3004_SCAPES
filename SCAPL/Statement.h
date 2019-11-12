#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include <vector>

#include "Operand.h"
#include "Label.h"

class Program;
class Statement {
    public:
        ~Statement() {
            if(o1 != nullptr) {
                delete(o1);
            }
            if(o2 != nullptr) {
                delete(o2);
            }
        };
        virtual void compile(std::string &) = 0;
        virtual void run() = 0;
        virtual std::string getName() = 0;
        virtual void setLabel(Label *l) = 0;
    protected:
        // Master program
        Program *master;
        // Two operands (Either can be NULL)
        Operand *o1;
        Operand *o2;
        // Label (Can be NULL)
        Label *label;
        std::string subtype;
};

#endif
