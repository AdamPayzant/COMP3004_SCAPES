#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <ios>
#include <fstream>
#include <string.h>
#include <string>

using namespace std;

#include "./Interface/MainWindow.h"
#include "./Persistence/PersistenceManager.h"
//#include "./SCAPL/Program.h"

class MainWindow;
/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: MainController.h
 * Author: Mathieu Leblanc
 * Date: 12/11/2019
 *
 * File Purpose:
 *     Used to create a controller object that will be used manage the operations required
 * to complete requests received by the application window through user input.
 * Id est, the controller object will coordinate operations completed by both the application window
 * and the persistence objects to ensure program functionality.
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 **/
class MainController
{
    public:
        /**
         *
         **/
        MainController(PersistenceManager*, MainWindow*);

        /**
         *
         **/
        ~MainController();

        /**
         *
         **/
        void clientRequestHandler(string);

        /**
         *
         **/
        void saveSourceCode();

        /**
         *
         **/
        void loadSourceCode();

        /**
         *
         **/
        void compileSourceCode();

        /**
         *
         **/
        void runCompiledProgram();


    private:
        /**
         *
         **/
        PersistenceManager* persistenceManager;

        /**
         *
         **/
        MainWindow* mainWindow;

        /**
         *
         **/
        //Program* program;
};

#endif
