
#include "DatabaseConductor.h"

DatabaseConductor::DatabaseConductor()
{
  this.connector = NULL;
  this.identifier_array = NULL;
  this.statement_array = NULL;
  this.filename="";
}

DatabaseConductor::~DatabaseConductor()
{
}

bool DatabaseConductor::persistProgramObjects(Identifier** identity_array, Statement** statement_array, string filename)
{
  setFilename(filename);
  this.connector = new SQLiteConnector(this.filename);
  this.connector.connect();

  /**
   * 
   **/
  QSqlQuery sqlcli;

  //DDL
  sqlcli.exec("DROP TABLE IF EXISTS ARRAY_CONTAIN_VAR;");
  sqlcli.exec("DROP TABLE IF EXISTS OPERAND;");
  sqlcli.exec("DROP TABLE IF EXISTS STATEMENT;");
  sqlcli.exec("DROP TABLE IF EXISTS IDENTIFIER;");
  sqlcli.exec("DROP TABLE IF EXISTS STATEMENT_TYPE;");
  sqlcli.exec("DROP TABLE IF EXISTS IDENTIFIER_TYPE;");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS IDENTIFIER_TYPE ("
    "ITID NUMBER(1) PRIMARY KEY,"
    "TYPE_NAME VARCHAR2(64) NOT NULL"
    ");");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS STATEMENT_TYPE ("
    "STID NUMBER(2) PRIMARY KEY,"
    "TYPE_NAME VARCHAR2(64) NOT NULL"
    ");");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS IDENTIFIER ("
    "NAME VARCHAR2(64) PRIMARY KEY,"
    "SUBTYPE NUMBER(2) NOT NULL,"
    "VALUE NUMBER(10),"
    "FOREIGN KEY(SUBTYPE) REFERENCES IDENTIFIER_TYPE(ITID)"
    ");");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS STATEMENT ("
    "SID INTEGER PRIMARY KEY AUTOINCREMENT,"
    "SUBTYPE NUMBER(2) NOT NULL,"
    "LABEL VARCHAR2(64),"
    "FOREIGN KEY(LABEL) REFERENCES IDENTIFIER(NAME),"
    "FOREIGN KEY(SUBTYPE) REFERENCES STATEMENT_TYPE(STID)"
    ");");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS OPERAND ("
    "SID NUMBER(3),"
    "IDENTIFIER_NAME VARCHAR2(64),"
    "FOREIGN KEY(IDENTIFIER_NAME) REFERENCES IDENTIFIER(NAME),"
    "PRIMARY KEY(SID, IDENTIFIER_NAME)"
    ");");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS ARRAY_CONTAIN_VAR ("
    "CONTAINER_NAME VARCHAR2(64),"
    "ELEMENT_NAME VARCHAR2(64),"
    "ELEMENT_INDEX NUMBER(2) NOT NULL,"
    "FOREIGN KEY(CONTAINER_NAME) REFERENCES IDENTIFIER(NAME),"
    "FOREIGN KEY(ELEMENT_NAME) REFERENCES IDENTIFIER(NAME),"
    "PRIMARY KEY(CONTAINER_NAME, ELEMENT_NAME),"
    "CHECK(CONTAINER_NAME != ELEMENT_NAME)"
    ");");

  //Initial DML
  sqlcli.exec("INSERT INTO IDENTIFIER_TYPE VALUES (0, 'IDENTIFIER');");
  sqlcli.exec("INSERT INTO IDENTIFIER_TYPE VALUES (1, 'LABEL');");
  sqlcli.exec("INSERT INTO IDENTIFIER_TYPE VALUES (2, 'VARIABLE');");
  sqlcli.exec("INSERT INTO IDENTIFIER_TYPE VALUES (3, 'INTEGERVARIABLE');");
  sqlcli.exec("INSERT INTO IDENTIFIER_TYPE VALUES (4, 'ARRAYVARIABLE');");

  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (0, 'STATEMENT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (1, 'READSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (2, 'PRINTSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (3, 'DECLINTSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (4, 'DECLARRSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (5, 'MOVSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (6, 'ADDSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (7, 'COMPSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (8, 'JLESSSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (9, 'JMORESTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (10, 'JEQSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (11, 'JUMPSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (12, 'ENDSTMT');");

  persistIdentifiers();
  persistStatements();
  
  this.connector.disconnect();
  delete this.connector;
  this.connector = NULL;
}

bool DatabaseConductor::restoreProgramObjects(Identifier** identity_array, Statement** statement_array, string filename)
{
  setFilename(filename);
  this.connector = new SQLiteConnector(this.filename);
  this.connector.connect();

  restoreIdentifiers();
  restoreStatements();

  this.connector.disconnect();
  delete this.connector;
  this.connector = NULL;
}

string DatabaseConductor::getFilename() const
{
  return this.filename;
}

void DatabaseConductor::setFilename(string newFilename)
{
  this.filename = newFilename;
}

bool persistIdentifiers()
{
}

bool persistStatements()
{
}

bool restoreIdentifiers()
{
}

bool restoreStatements()
{
}
