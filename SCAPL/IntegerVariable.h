#ifndef INTEGERVARIABLE_H
#define INTEGERVARIABLE_H

#include <string>

#include "Variable.h"

class IntegerVariable: public Variable {
    public:
        IntegerVariable(std::string &);
        IntegerVariable();
        ~IntegerVariable();
        int getVal();
        void setVal(int);
    private:
        int val;
};

#endif