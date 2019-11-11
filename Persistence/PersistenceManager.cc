
#include "PersistenceManager.h"

PersistenceManager::PersistenceManager():
    sourceCodeSnapshot("")
{
}

PersistenceManager::~PersistenceManager()
{
}

bool PersistenceManager::persistProgramObjects(Identifier** identifier_array, Statement** statement_array, string filename)
{
  return this->databaseConductor.persistProgramObjects(identifier_array, statement_array, filename);
}

bool PersistenceManager::restoreProgramObjects(Identifier** identifier_array, Statement** statement_array, string filename)
{
  return this->databaseConductor.restoreProgramObjects(identifier_array, statement_array, filename);
}

bool PersistenceManager::saveToFile(string editorText, string& filename)
{
  sourceCodeSnapshot=editorText;
  return this->fileSupervisor.saveToFile(sourceCodeSnapshot, filename);
}

bool PersistenceManager::loadFromFile(string& editorText, string& filename)
{
  return this->fileSupervisor.loadFromFile(editorText, filename);
}
