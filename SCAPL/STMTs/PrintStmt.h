#ifndef PRINTSTMT_H
#define PRINTSTMT_H

#include <string>

#include "../Statement.h"

class PrintStmt: public Statement {
    public:
        PrintStmt(Program *);
        ~PrintStmt();
        void compile(std::string);
        void run();
};

#endif