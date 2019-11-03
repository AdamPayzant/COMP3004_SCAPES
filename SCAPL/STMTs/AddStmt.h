#ifndef ADDSTMT_H
#define ADDSTMT_H

#include <string>

#include "../Statement.h"

class AddStmt: public Statement {
    public:
        AddStmt();
        ~AddStmt();
        void compile(std::string);
        void run();
};

#endif