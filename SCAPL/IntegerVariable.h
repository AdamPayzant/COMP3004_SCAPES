#ifndef INTEGERVARIABLE_H
#define INTEGERVARIABLE_H

#include <string>

#include "Variable.h"
#include "Value.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 05/12/2019
 *
 * Version 1.0:
 * File: IntegerVariable.h
 * Author: Edward Adam Payzant
 * Date: 05/12/2019
 *
 * File Purpose:
 *     Used to store and track integer variables
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class IntegerVariable: public Variable, public Value {
    public:
        /**
         * Constructor
         * Parameters:
         * - A string containing it's name
         **/
        IntegerVariable(std::string &);
        /**
         * Constructor for anon variables
         **/
        IntegerVariable();
        /**
         * Destructor
         **/
        ~IntegerVariable();
        /**
         * Returns the value restored
         **/
        int getVal();
        /**
         * Gets the output
         **/
        std::string getOut();
        /**
         * Sets the value
         **/
        void setVal(int);
    
        /**
         * Implementation of the function used as behavior for the composite design pattern.
         * Allows for IntegerVariable to provide its value to a string that could be passed 
         * through a composite object or only to itself.
         **/
        virtual void print(std::string&);
    private:
        /**
         * Value of the Integer
         **/
        int val;
};

#endif
