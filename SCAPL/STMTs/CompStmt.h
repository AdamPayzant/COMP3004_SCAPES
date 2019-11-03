#ifndef COMPSTMT_H
#define COMPSTMT_H

#include <string>

#include "../Statement.h"

class CompStmt: public Statement {
    public:
        CompStmt();
        ~CompStmt();
        void compile(std::string);
        void run();
};

#endif