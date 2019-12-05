#ifndef ARRAYVARIABLE_H
#define ARRAYVARIABLE_H

#include <string>

#include "Variable.h"
#include "Value.h"
#include "Literal.h"
#include "IntegerVariable.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 05/12/2019
 *
 * Version 1.0:
 * File: ArrayVariable.h
 * Author: Edward Adam Payzant
 * Date: 05/12/2019
 *
 * File Purpose:
 *     Used to store and track array variables
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/

class ArrAccess;
class ArrayVariable: public Variable {
    public:
        /**
         * Constructor
         * Parameters:
         * - A string containing it's name
         **/
        ArrayVariable(std::string &);
        /**
         * Destructor
         **/
        ~ArrayVariable();
        /**
         * Creates the array to the passed size
         **/
        void create(int);
        /**
         * Sets the value at a given index
         **/
        void setAt(int, int);
        /**
         * Gets the value a given index
         **/
        Variable* getAt(int);
        /**
         * Returns the size of the array
         **/
        int getSize();
        /**
         * Resizes the array
         **/
        int setSize(int newSize);
    
        /**
         * Implementation of the function used for the composite design pattern.
         * Allows for ArrayVariable to call its subelements' print function without
         * worrying about their type; polymorphism decides what implementation will
         * take place within the subelement's call.
         **/
        virtual void print(std::string&);
    private:
        /**
         * The array
         **/
        Variable** arr;
        /**
         * The size of array
         **/
        int size;
};

#endif
