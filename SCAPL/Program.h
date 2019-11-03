#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>

#include "Statement.h"
#include "Identifier.h"

class Program {
    public:
        Program();
        ~Program(); 
        void compile();
        void execute();
        void print();
    private:
        std::string filename;
        int comparisonFlag;
        std::vector<Identifier> ids;
        std::vector<Statement> stmts;
};

#endif