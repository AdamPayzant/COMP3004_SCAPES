
#include "DatabaseConductor.h"
#include "./../SCAPL/Variable.h"
#include "./../SCAPL/Label.h"

DatabaseConductor::DatabaseConductor()
{
  this->connector = nullptr;
  this->identifier_vector = nullptr;
  this->statement_vector = nullptr;
  this->filename="";
}

DatabaseConductor::~DatabaseConductor()
{
}

bool DatabaseConductor::persistProgramObjects(std::vector<Identifier*>* identifier_vector, std::vector<Statement*>* statement_vector, string filename)
{
  setFilename(filename);
  this->connector = new SQLiteConnector(this->filename);
  this->connector->connect();
  this->identifier_vector = identifier_vector;
  this->statement_vector = statement_vector;

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
    "SID INTEGER PRIMARY KEY,"
    "SUBTYPE NUMBER(2) NOT NULL,"
    "LABEL VARCHAR2(64),"
    "FOREIGN KEY(LABEL) REFERENCES IDENTIFIER(NAME),"
    "FOREIGN KEY(SUBTYPE) REFERENCES STATEMENT_TYPE(STID)"
    ");");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS OPERAND ("
    "SID NUMBER(3),"
    "IDENTIFIER_NAME VARCHAR2(64),"
    "OPERNUM NUMBER(1) NOT NULL,"
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

  this->persistIdentifiers();
  this->persistStatements();
  //this->persistOperands();
  
  this->connector->disconnect();
  delete this->connector;
  this->connector = nullptr;
  return true;
}

bool DatabaseConductor::restoreProgramObjects(std::vector<Identifier*>* identifier_vector, std::vector<Statement*>* statement_vector, string filename)
{
  setFilename(filename);
  this->connector = new SQLiteConnector(this->filename);
  this->connector->connect();

  this->restoreIdentifiers();
  this->restoreStatements();

  this->connector->disconnect();
  delete this->connector;
  this->connector = nullptr;
  return true;
}

string DatabaseConductor::getFilename() const
{
  return this->filename;
}

void DatabaseConductor::setFilename(string newFilename)
{
  this->filename = newFilename;
}

bool DatabaseConductor::persistIdentifiers()
{
    int i;
    int tempInt;
    char identifierName[64];
    char identifierValue[12];
    char sqlstmt[128];
    string tempName;
    string identifierSubtype;
    QSqlQuery sqlcli;

    for(i=0; i< this->identifier_vector->size(); i++){
        sqlstmt[0]='\0';
        this->identifier_vector->at(i)->getName(tempName);
        snprintf(identifierName, 63, "%s", tempName.data());
        identifierName[63]='\0';
        identifierSubtype = this->identifier_vector->at(i)->getSubtype();

        if(identifierSubtype.compare("Label") == 0){
            identifierSubtype = "1";
            identifierValue[0] = 'N';
            identifierValue[1] = 'U';
            identifierValue[2] = 'L';
            identifierValue[3] = 'L';
            identifierValue[4] = '\0';
        }

        if(identifierSubtype.compare("Variable") == 0){
            identifierSubtype = "2";
            ((Variable*) (this->identifier_vector->at(i)))->getVal(tempInt);
            sprintf(identifierValue, "%d", tempInt);
        }
        sprintf(sqlstmt, "INSERT INTO IDENTIFIER VALUES('%s', %s, %s);", identifierName, identifierSubtype.data(), identifierValue);
        sqlcli.exec(sqlstmt);
    }
    return true;
}

bool DatabaseConductor::persistStatements()
{
    int i;
    char identifierName[64];
    char sqlstmt[128];
    string tempName;
    string compiledStatementSubtype;
    QSqlQuery sqlcli;
    Identifier* idPtr;

    for(i=0; i<this->statement_vector->size(); i++){
        sqlstmt[0]='\0';
        identifierName[0]='\0';
        snprintf(identifierName, 63, tempName.data());
        identifierName[63]='\0';
        compiledStatementSubtype = this->statement_vector->at(i)->getName();

        if(compiledStatementSubtype.compare("DeclIntStmt") == 0 ||
                compiledStatementSubtype.compare("ReadStmt") == 0 ||
                compiledStatementSubtype.compare("PrintStmt") == 0 ||
                compiledStatementSubtype.compare("CompStmt") == 0 ||
                compiledStatementSubtype.compare("EndStmt") == 0){
            identifierName[0] = 'N';
            identifierName[1] = 'U';
            identifierName[2] = 'L';
            identifierName[3] = 'L';
            identifierName[4] = '\0';
        }
        else{
            idPtr = this->statement_vector->at(i)->getLabel();
            if(idPtr != nullptr){
                idPtr->getName(tempName);
                snprintf(identifierName, 63, "%s", tempName.data());
                identifierName[63]='\0';
            }
            else{
                identifierName[0] = 'N';
                identifierName[1] = 'U';
                identifierName[2] = 'L';
                identifierName[3] = 'L';
                identifierName[4] = '\0';
            }
        }

        if(compiledStatementSubtype.compare("ReadStmt") == 0){
            compiledStatementSubtype = "1";
        }


        if(compiledStatementSubtype.compare("PrintStmt") == 0){
            compiledStatementSubtype = "2";
        }

        if(compiledStatementSubtype.compare("DeclIntStmt") == 0){
            compiledStatementSubtype = "3";
        }


        if(compiledStatementSubtype.compare("CompStmt") == 0){
            compiledStatementSubtype = "7";
        }


        if(compiledStatementSubtype.compare("JMoreStmt") == 0){
            compiledStatementSubtype = "9";
        }


        if(compiledStatementSubtype.compare("JumpStmt") == 0){
            compiledStatementSubtype = "11";
        }


        if(compiledStatementSubtype.compare("EndStmt") == 0){
            compiledStatementSubtype = "12";
        }

        sprintf(sqlstmt, "INSERT INTO STATEMENT VALUES(%d, %s, %s);", i, compiledStatementSubtype.data(), identifierName);
        sqlcli.exec(sqlstmt);
        sqlstmt[0]='\0';
        identifierName[0]='\0';
    }
    return true;
}

bool DatabaseConductor::persistOperands()
{
    int i;
    char identifierName[64];
    char sqlstmt[128];
    std::string tempName;
    QSqlQuery sqlcli;
    Identifier* idPtr;

    for(i=0; i<this->statement_vector->size(); i++){
        sqlstmt[0]='\0';
        identifierName[0]='\0';

        if(this->statement_vector->at(i)->getOperand1() != nullptr){
            this->statement_vector->at(i)->getOperand1()->getID(idPtr);
            if(idPtr){
                try {
                    idPtr->getName(tempName);
                    snprintf(identifierName, 63, "%s", tempName.data());
                    identifierName[63]='\0';
                    int example1 = 1;
                    int example2 = 1;
                    sprintf(sqlstmt, "INSERT INTO OPERAND VALUES(%d, %s, %d);", i, identifierName, 1);
                    sqlcli.exec(sqlstmt);
                    sqlstmt[0]='\0';
                }
                catch (int exception)
                {
                }
            }
        }

        /*
        if(this->statement_vector->at(i)->getOperand2() != nullptr){
            this->statement_vector->at(i)->getOperand2()->getID(idPtr);
            if(idPtr != nullptr){
                tempName = idPtr->getNameValue();
                snprintf(identifierName, 63, "%s", tempName.data());
                identifierName[63]='\0';
                sprintf(sqlstmt, "INSERT INTO OPERAND VALUES(%d, %s, %d);", i, idPtr->getNameValue().data(), 2);
                sqlcli.exec(sqlstmt);
                sqlstmt[0]='\0';
            }
        }
        */

    }
    return true;
}

bool DatabaseConductor::restoreIdentifiers()
{
    return true;
}

bool DatabaseConductor::restoreStatements()
{
    return true;
}
