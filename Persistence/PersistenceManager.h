#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H

#include <string>
#include <vector>
using namespace std;

#include "DatabaseConductor.h"
#include "FileSupervisor.h"
#include "./../SCAPL/Identifier.h"
#include "./../SCAPL/Statement.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 * 
 * Version 1.0:
 * File: PersistenceManager.h
 * Author: Mathieu Leblanc
 * Date: 12/11/2019
 * 
 * File Purpose:
 *     Used to create a PersistenceManager object, which will be used to
 * coordinate operations involving object or source code persistence by providing
 * a unifying interface of the storage layer services.
 * 
 * Formatting style based on course notes and course work from COMP2401 and 
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering 
 * of COMP2404.
 * 
 **/
class PersistenceManager
{
  public:
    /**
     * 
     **/
    PersistenceManager();

    /**
     * Destructor
     **/
    ~PersistenceManager();

    /**
     * 
     **/
    bool persistProgramObjects(std::vector<Identifier*>*, std::vector<Statement*>*, string);

    /**
     * 
     **/ 
    bool restoreProgramObjects(std::vector<Identifier*>*, std::vector<Statement*>*, string);

    /**
     *
     **/
    bool saveToFile(string, string&);

    /**
     * 
     **/
    bool loadFromFile(string&, string&);

  private:
    /**
     * 
     **/
    DatabaseConductor databaseConductor;

    /**
     * 
     **/
    FileSupervisor fileSupervisor;

    /**
     *
     **/
    string sourceCodeSnapshot;
};

#endif
