#ifndef READSTMT_H
#define READSTMT_H

#include <string>

#include "../Statement.h"

class ReadStmt: public Statement {
    public:
        ReadStmt();
        ~ReadStmt();
        void compile(std::string);
        void run();
};

#endif