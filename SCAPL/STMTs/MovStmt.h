#ifndef MOVSTMT_H
#define MOVSTMT_H

#include <string>

#include "../Statement.h"

class MovStmt: public Statement {
    public:
        MovStmt(Program *);
        ~MovStmt();
        void compile(std::string &);
        void run();
};

#endif