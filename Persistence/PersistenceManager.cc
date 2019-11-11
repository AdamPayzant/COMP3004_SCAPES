
#include "PersistenceManager.h"

PersistenceManager::PersistenceManager()
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

bool PersistenceManager::saveToFile(string& editorText, string filename)
{
  return this->fileSupervisor.saveToFile(editorText, filename);
}

bool PersistenceManager::loadFromFile(string& editorText, string filename)
{
  return this->fileSupervisor.loadFromFile(editorText, filename);
}
