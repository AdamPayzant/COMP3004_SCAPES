#ifndef READSTMT_H
#define READSTMT_H

#include <string>

#include "../Statement.h"
#include "../Program.h"


/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: ReadStmt.h
 * Author: Edward Adam Payzant
 * Date: 12/11/2019
 *
 * File Purpose:
 *     Used to create Add Statement objects representing Read instructions
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class ReadStmt: public Statement {
    public:
        /**
         * Constructor
         * Parameters:
         * - Pointer to the program from which the statement was derived
         **/
        ReadStmt(Program *);

        /**
         * Destructor
         **/
        ~ReadStmt();

        /**
         * Function used to compile the instruction provided into an internal format
         **/
        void compile(std::string &);

        /**
         * Function used to execute the compiled state of the instruction
         **/
        void run();

        /**
         * Getter function used to return the current subclass name
         **/
        virtual std::string getName();
};

#endif
