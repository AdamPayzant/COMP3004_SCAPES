#ifndef ARRACCESS_H
#define ARRACCESS_H

#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#include "Value.h"
#include "ArrayVariable.h"
#include "Identifier.h"
#include "IntegerVariable.h"
#include "Literal.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 05/12/2019
 *
 * Version 1.0:
 * File: ArrAccess.h
 * Author: Edward Adam Payzant
 * Date: 05/12/2019
 *
 * File Purpose:
 *     Used to store and track array access points
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/

class Program;
class ArrAccess: public Identifier, public Value {
    public:
        /**
         * Constructor
         * Parameters:
         * - The arrayvariable it's accessing
         * - The access parameter
         * - The master program
         **/
        ArrAccess(ArrayVariable *, std::string, Program *);
        /**
         * Destructor
         **/
        ~ArrAccess();
        /**
         * Gets the value from the array
         **/
        int getVal();
        /**
         * Gets the output
         **/
        std::string getOut();
        /**
         * Sets the array index it accesses to passed value
         **/
        void setVal(int);
        /**
         * Gets the ArrayVariable it's too access
         **/
        ArrayVariable* getParent();
        /**
         * Gets the access parameters
         **/
        std::string getAccess();
        
        /**
         * Print function implemented to allow for the easy implementation of an additional 
         * type to the composite design pattern if deemed necessary.
         * Allows for the value of the element in the array to be printed to the GUI for the user.
         **/
        void print(std::string&);
    
    private:
        /**
         * Private getter to retrieve the variable associated to this association instance.
         **/
        IntegerVariable* getVar();
        /**
         * ArrayVariable it's accessing
         **/
        ArrayVariable* arr;
        /**
         * Access parameter
         **/
        std::string access;
        /**
         * The program running everything
         **/
        Program *master;
};

#endif
