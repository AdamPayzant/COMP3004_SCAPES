#ifndef PRINTSTMT_H
#define PRINTSTMT_H

#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#include "../Program.h"
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
 * File: PrintStmt.h
 * Author: Edward Adam Payzant
 * Date: 12/11/2019
 *
 * File Purpose:
 *     Used to create Add Statement objects representing Print instructions
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class PrintStmt: public Statement {
    public:
        /**
         * Constructor
         * Parameters:
         * - Pointer to the program from which the statement was derived
         **/
        PrintStmt(Program *);

        /**
         * Destructor
         **/
        ~PrintStmt();

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

        /**
         * Getter function used to return a pointer to the first operand object associated with the subclass object
         **/
        virtual Operand* getOperand1();

        /**
         * Getter function used to return a pointer to the second operand object associated with the subclass object
         **/
        virtual Operand* getOperand2();

        /**
         * Getter function used to return a pointer to the label object associated with the subclass object
         **/
        virtual Label* getLabel();

        /**
         * Setter function used to set a pointer to the label object associated with the subclass object
         **/
        virtual void setLabel(Label *l);
};

#endif
