#ifndef JLESSSTMT_H
#define JLESSSTMT_H

#include <string>

#include "../Statement.h"

class JLessStmt: public Statement {
    public:
        JLessStmt();
        ~JLessStmt();
        void compile(std::string);
        void run();
};

#endif