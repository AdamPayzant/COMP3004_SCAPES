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

#include "MainController.h"

MainController::MainController(PersistenceManager* persistenceManagerPtr, MainWindow* mainWindowPtr)
{
    this->persistenceManager = persistenceManagerPtr;
    this->mainWindow = mainWindowPtr;
    this->program = nullptr;
}

MainController::~MainController()
{
}

void MainController::clientRequestHandler(string command)
{
    if(command.compare("save") == 0){
        saveSourceCode();
        return;
    }
    if(command.compare("load") == 0){
        loadSourceCode();
        return;
    }
    if(command.compare("compile") == 0){
        compileSourceCode();
    }
    if(command.compare("run") == 0){
        runCompiledProgram();
    }
    return;
}

void MainController::saveSourceCode()
{
    if(persistenceManager->saveToFile(this->mainWindow->getEditorText(), mainWindow->getProgramFilename())){
        string tempString = "";
        tempString.append("Save operation successful.\nFile ");
        tempString.append(this->mainWindow->getProgramFilename().data());
        tempString.append(".scapl saved to default directory.");
        this->mainWindow->setFeedbackText(tempString);
        this->mainWindow->prepareLoadedWindowState();
    }else{
        this->mainWindow->setFeedbackText("An Error occurred during the save operation.");
    }
}

void MainController::loadSourceCode()
{
    if(persistenceManager->loadFromFile(this->mainWindow->getEditorText(), mainWindow->getProgramFilename())){
        this->mainWindow->refreshEditorText();
        string tempString = "";
        tempString.append("Open operation successful.\nFile ");
        tempString.append(this->mainWindow->getProgramFilename().data());
        tempString.append(".scapl opened from default directory.");
        this->mainWindow->setFeedbackText(tempString);
        this->mainWindow->prepareLoadedWindowState();
    }else{
        this->mainWindow->setFeedbackText("An Error occurred during the open operation.");
    }
}

void MainController::compileSourceCode()
{
    /*
    if(this->program != nullptr){
        delete this->program;
    }
    this->program = nullptr;
    */
    this->program = new Program(mainWindow->getProgramFilename());
    this->program->compile();

    if(!this->program->getCompileValidityStatus()){
        string tempString = "";
        tempString.append("Compile failed to complete during syntax check.\n");
        tempString.append("Error: ");
        tempString.append(this->program->getCompileError());
        this->mainWindow->setFeedbackText(tempString);
        return;
    }
    if(this->persistenceManager->persistProgramObjects(this->program->getIds(), this->program->getStmts(), mainWindow->getProgramFilename())){
        string tempString = "Compilation successful. Compiled version successfully saved.";
        this->mainWindow->setFeedbackText(tempString);
        return;
    }
}

void MainController::runCompiledProgram()
{
    /*
    if(this->program != nullptr){
        delete this->program;
    }
    this->program = nullptr;
    */
    this->program = new Program(mainWindow->getProgramFilename(), this);
    this->persistenceManager->restoreProgramObjects(this->program, this->program->getIds(), this->program->getStmts(), mainWindow->getProgramFilename());
    this->program->execute();
}

string& MainController::promptUserForInput(){
    this->mainWindow->promptUserForInput("Please provide a value:");
    return this->mainWindow->getTempUserInput();
}

void MainController::appendToFeedbackText(std::string& formattedText){
    if(!formattedText.empty()){
        this->mainWindow->appendToFeedbackText(formattedText);
    }
}
