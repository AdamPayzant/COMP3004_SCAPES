
#include "SQLiteConnector.h"

SQLiteConnector::SQLiteConnector(string filename)
{
  database = QSqlDatabase::addDatabase("QSQLITE");
  database.setDatabaseName(QString::fromStdString(filename));
}

SQLiteConnector::~SQLiteConnector()
{
  this->disconnect();
}

void SQLiteConnector::connect()
{
  if(!(database.isOpen())){
    database.open();
  }
}

void SQLiteConnector::disconnect()
{
  if(database.isOpen()){
    database.commit();
    database.close();
    QSqlDatabase::removeDatabase("SQLITE");
  }
}

QSqlDatabase& SQLiteConnector::getSQLiteDatabase(){
    return database;
}
