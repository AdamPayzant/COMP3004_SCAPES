#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <functional>
#include <iostream>

#include "Statement.h"
#include "Identifier.h"

#include "STMTs/CompStmt.h"
#include "STMTs/DeclIntStmt.h"
#include "STMTs/EndStmt.h"
#include "STMTs/JMoreStmt.h"
#include "STMTs/JumpStmt.h"
#include "STMTs/PrintStmt.h"
#include "STMTs/ReadStmt.h"

class Program {
    public:
        Program(std::string &);
        ~Program(); 
        bool compile();
        void execute();
        void print();

        // Getters
        std::vector<Identifier*>* getIds();

        std::vector<Statement*>* getStmts();
  
        int getCFlag();
    private:
        std::string filename;
        int comparisonFlag;
        std::vector<Identifier*> *ids;
        std::vector<Statement*> *stmts;
};

#endif
