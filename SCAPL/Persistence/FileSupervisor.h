#ifndef FILESUPERVISOR_H
#define FILESUPERVISOR_H

#include <ofstream>
#include <ifstream>
#include <string>

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 * 
 * Version 1.0:
 * File: FileSupervisor.h
 * Author: Mathieu Leblanc
 * Date: 12/11/2019
 * 
 * File Purpose:
 *     Used to create an SQLiteConnector object, which will be used to
 * open, manage, and finally close a connection with a local SQLite Database.
 * 
 * Formatting style based on course notes and course work from COMP2401 and 
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering 
 * of COMP2404.
 * 
 **/
class FileSupervisor
{
  public:
    /**
     * 
     **/
    FileSupervisor();

    /**
     * Destructor
     **/
    ~FileSupervisor();

    /**
     *
     **/
    bool saveToFile(string&, string);

    /**
     * 
     **/
    bool loadFromFile(string&, string);
};

#endif
