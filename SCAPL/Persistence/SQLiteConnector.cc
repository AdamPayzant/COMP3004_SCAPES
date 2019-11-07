
#include "SQLiteConnector.h"

SQLiteConnector::SQLiteConnector(string filename)
{
  database = QSqlDatabase::addDatabase("QSQLITE");
  database.setDatabaseName(filename);
}

SQLiteConnector::~SQLiteConnector()
{
  this.disconnect();
}

void SQLiteConnector::connect()
{
  if(!(database == NULL)){
    database.open();
  }
}

void SQLiteConnector::disconnect()
{
  if(!(database == NULL)){
    database.close();
  }
}
