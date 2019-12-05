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

#include "STMTs/AddStmt.h"
#include "STMTs/CompStmt.h"
#include "STMTs/DeclArrStmt.h"
#include "STMTs/DeclIntStmt.h"
#include "STMTs/EndStmt.h"
#include "STMTs/JEqStmt.h"
#include "STMTs/JLessStmt.h"
#include "STMTs/JMoreStmt.h"
#include "STMTs/JumpStmt.h"
#include "STMTs/MovStmt.h"
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
class MainController;
class Program {
    public:
        /**
         * Constructor
         * Parameters:
         * - Filename of the source file to be compiled or restored.
         **/
        Program(std::string &);

        Program(std::string &, MainController*);
  
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

        /**
         * Setter functions that will change the current comparison flag
         **/
        void setCFlag(int);

        /**
         * Getter that finds and returns the identifier named
         **/
        Identifier* getID(std::string);

        /**
         * Takes a label, searches for the statement linked with it, then sets stmtPos to the found statement
         **/
        void changeStmt(Label *);

        /*
        void addPrint(std::string);
        */
    
        /**
         * Takes a string and adds it to the output
         **/
        void pushToWindow(std::string&);

        /**
         * Sets stmtPos to higher than stmts->size() so execution will end
         **/
        void end();

        /**
         * Gets user input from the main controller
         **/
        std::string& getUserInput();

        /**
         * Returns the last compile error
         **/
        std::string& getCompileError();

        /**
         * Sets the compile error
         **/
        void setCompileError(std::string&);

        /**
         * Checks if there has been been a compile error
         * Returns compileValidityStatus
         **/
        bool getCompileValidityStatus();

        /**
         * Setter for compileValidityStatus
         **/
        void setCompileValidityStatus(bool);

        /**
         * removes the whitespace at the start of a string
         **/
        int removeLeadingWhitespace(std::string&);

        /**
         * Gets the next argument in a statement call
         **/
        int parseNextArg(std::string&, std::string&);

        /**
         * Removes the next argument from a string
         **/
        int removeNextArg(std::string&);

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

        /**
         * Tracks the current statement position for execution, 
         * outside of the execution function so that jump statements and end can modify it
         **/
        int stmtPos;

        /**
         * string for tracking output
         **/
        std::string output;

        /**
         * The maincontroller handling program
         **/
        MainController* controller;

        /**
         * Tracks compile status
         **/
        bool compileValidityStatus;

        /**
         * Stores the last compile error output
         **/
        std::string compileError;
};

#endif
