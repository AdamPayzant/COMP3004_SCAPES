#ifndef ADDSTMT_H
#define ADDSTMT_H

#include <string>
#include <vector>
#include <iterator>
#include <sstream>

#include "../Statement.h"

class AddStmt: public Statement {
    public:
        AddStmt(Program *);
        ~AddStmt();

        void compile(std::string);
        void run();
};

#endif