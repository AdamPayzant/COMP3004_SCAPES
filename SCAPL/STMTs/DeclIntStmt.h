#ifndef DECLINTSTMT_H
#define DECLINTSTMT_H

#include <string>

#include "../Statement.h"

class DeclIntStmt: public Statement {
    public:
        DeclIntStmt();
        ~DeclIntStmt();
        void compile(std::string);
        void run();
};

#endif