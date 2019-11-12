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

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: Program.h
 * Author: Edward Adam Payzant
 * Date: 12/11/2019
 *
 * File Purpose:
 *     Used to create a Project object, which is used to organize the operations
 * required to compile the SCAPL source code of a program into internal representations
 * of the concepts and operations (identifiers and statements) that would be involved in the
 * execution of the compiled source code.
 * The object is also able to organize the execution of the compiled source code using
 * the previously-created objects.
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class Program {
    public:
        /**
         *
         **/
        Program(std::string &);
        /**
         *
         **/
        ~Program();

        /**
         *
         **/
        void compile();

        /**
         *
         **/
        void execute();

        /**
         *
         **/
        void print();

        /**
         *
         **/
        std::vector<Identifier*>* getIds();

        /**
         *
         **/
        std::vector<Statement*>* getStmts();

        /**
         *
         **/
        int getCFlag();

    private:
        /**
         *
         **/
        std::string filename;

        /**
         *
         **/
        int comparisonFlag;

        /**
         *
         **/
        std::vector<Identifier*> *ids;

        /**
         *
         **/
        std::vector<Statement*> *stmts;
};

#endif
