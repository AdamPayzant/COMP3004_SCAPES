#ifndef LITERAL_H
#define LITERAL_H

#include "Identifier.h"
#include "Value.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 05/12/2019
 *
 * Version 1.0:
 * File: Literal.h
 * Author: Edward Adam Payzant
 * Date: 05/12/2019
 *
 * File Purpose:
 *     Used to store literal values
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class Literal: public Identifier, public Value {
    public:
        /**
         * Constructor
         * Parameters:
         * - A string containing the value of the literal
         **/
        Literal(std::string);
        /**
         * Destructor
         **/
        ~Literal();
        /**
         * Returns the value of the literal converted to a string
         **/
        int getVal();
        /**
         * Returns the string of the literal
         **/
        std::string getOut();
        /**
         * Setter for value. Doesn't actually do anything
         **/
        void setVal(int);
    private:
        /**
         * The value it stores
         **/
        std::string str;
};

#endif
