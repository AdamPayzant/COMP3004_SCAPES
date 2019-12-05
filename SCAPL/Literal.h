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
         * Getter function for the value of the literal converted to an int
         **/
        int getVal();
        /**
         * Getter function for the value of the string of the literal
         **/
        std::string getOut();
        /**
         * Setter function for value. Doesn't actually do anything
         **/
        void setVal(int);
    private:
        /**
         * The value the literal stores
         **/
        std::string str;
};

#endif
