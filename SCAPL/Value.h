#ifndef VALUE_H
#define VALUE_H


class Value {
    public:
        virtual int getVal() = 0;
        virtual void setVal(int) = 0;
};

#endif