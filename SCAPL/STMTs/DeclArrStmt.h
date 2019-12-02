#ifndef DECLARRSTMT_H
#define DECLARRSTMT_H

#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#include "../Statement.h"
#include "../Variable.h"
#include "../Operand.h"
#include "../ArrAccess.h"
#include "../Literal.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: DeclArrStmt.h
 * Author: Edward Adam Payzant
 * Date: 12/11/2019
 *
 * File Purpose:
 *     Used to create Add Statement objects representing Array Variable Declaration instructions
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class Program;
class DeclArrStmt: public Statement {
    public:
        /**
         * Constructor
         * Parameters:
         * - Pointer to the program from which the statement was derived
         **/
        DeclArrStmt(Program *);

        /**
         * Destructor
         **/
        ~DeclArrStmt();

        /**
         * Function used to compile the instruction provided into an internal format
         **/
        void compile(std::string &);

        /**
         * Function used to execute the compiled state of the instruction
         **/
        void run();

};

#endif
