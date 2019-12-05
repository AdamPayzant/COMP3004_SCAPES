
#include "PersistenceManager.h"

PersistenceManager::PersistenceManager():
    sourceCodeSnapshot("")
{
}

PersistenceManager::~PersistenceManager()
{
}

bool PersistenceManager::persistProgramObjects(std::vector<Identifier*>* identifier_vector, std::vector<Statement*>* statement_vector, string filename)
{
  return this->databaseConductor.persistProgramObjects(identifier_vector, statement_vector, filename);
}

bool PersistenceManager::restoreProgramObjects(Program* program, std::vector<Identifier*>* identifier_vector, std::vector<Statement*>* statement_vector, string filename)
{
  return this->databaseConductor.restoreProgramObjects(program, identifier_vector, statement_vector, filename);
}

bool PersistenceManager::saveToFile(string& editorSnapshot, string& filename)
{
  return this->fileSupervisor.saveToFile(editorSnapshot, filename);
}

bool PersistenceManager::loadFromFile(string& editorSnapshot, string& filename)
{
  return this->fileSupervisor.loadFromFile(editorSnapshot, filename);
}
