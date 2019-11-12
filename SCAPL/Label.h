#ifndef LABEL_H
#define LABEL_H

#include <string>

#include "Identifier.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: Label.h
 * Author: Edward Adam Payzant
 * Date: 12/11/2019
 *
 * File Purpose:
 *     Used to create a Label object, which is an internal representation of
 * the label associated with a SCAPL instruction.
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class Label: public Identifier {
    public:
        /**
         *
         **/
        Label(std::string &);

        /**
         *
         **/
        ~Label();

    private:
};

#endif
