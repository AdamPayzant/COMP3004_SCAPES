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
         * Constructor
         * Parameters:
         * - Filename of the source file to be compiled or restored.
         **/
        Program(std::string &);

        /**
         * Destructor
         **/
        ~Program();

        /**
         * Function used to manage the operations required to compile the source code of the program
         **/
        void compile();

        /**
         * Function used to manage the operations required to execute the compiled version of the source code
         * of the program.
         **/
        void execute();

        /**
         * Function used to print for testing purposes in D2
         **/
        void print();

        /**
         * Getter function that returns a pointer to the vector of Identifiers of the program
         **/
        std::vector<Identifier*>* getIds();

        /**
         * Getter function that returns a pointer to the vector of Statements of the program
         **/
        std::vector<Statement*>* getStmts();

        /**
         * Getter function that returns the current value of the comparison flag of the program
         **/
        int getCFlag();

        void changeStmt(Label *);

    private:
        /**
         * String variable used to hold the program's filename
         **/
        std::string filename;

        /**
         * Integer variable used to hold the current state of the program's comparison flag
         **/
        int comparisonFlag;

        /**
         * Pointer used to hold the memory address of the vector of Identifiers for the program
         **/
        std::vector<Identifier*> *ids;

        /**
         * Pointer used to hold the memory address of the vector of Statements for the program
         **/
        std::vector<Statement*> *stmts;

        Statement *curStmt;
        int stmtPos;
};

#endif
