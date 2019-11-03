#ifndef PRINTSTMT_H
#define PRINTSTMT_H

#include <string>

#include "../Statement.h"

class PrintStmt: public Statement {
    public:
        PrintStmt();
        ~PrintStmt();
        void compile(std::string);
        void run();
};

#endif