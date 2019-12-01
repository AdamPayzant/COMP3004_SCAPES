#ifndef INTEGERVARIABLE_H
#define INTEGERVARIABLE_H

#include <string>

#include "Variable.h"
#include "Value.h"

class IntegerVariable: public Variable, public Value {
    public:
        IntegerVariable(std::string &);
        IntegerVariable();
        ~IntegerVariable();
        int getVal();
        std::string getOut();
        void setVal(int);
    private:
        int val;
};

#endif