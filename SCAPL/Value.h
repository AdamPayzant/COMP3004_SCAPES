#ifndef VALUE_H
#define VALUE_H

#include <string>

class Value {
    public:
        virtual int getVal() = 0;
        virtual std::string getOut() = 0;
        virtual void setVal(int) = 0;
};

#endif