
#include "MainController.h"

MainController::MainController(PersistenceManager* persistenceManagerPtr, MainWindow* mainWindowPtr)
{
    this->persistenceManager = persistenceManagerPtr;
    this->mainWindow = mainWindowPtr;
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
    persistenceManager->saveToFile(mainWindow->getEditorText(), mainWindow->getProgramFilename());
}

void MainController::loadSourceCode()
{
}

void MainController::compileSourceCode()
{
    this->program = new Program(mainWindow->getProgramFilename());
    program->compile();
    this->persistenceManager->persistProgramObjects(this->program->getIds(), this->program->getStmts(), mainWindow->getProgramFilename());
}

void MainController::runCompiledProgram()
{
}
