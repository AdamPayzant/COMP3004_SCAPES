
#include "FileSupervisor.h"

FileSupervisor::FileSupervisor()
{
}

FileSupervisor::~FileSupervisor()
{
}

bool saveToFile(string& editorText, string filename)
{
  ofstream outputFile;
  outputFile.open(filename);
  if(!outputFile.is_open()){
    return false;
  }
  outputFile << editorText << endl;
  outputFile.close();
  return true;
}

bool loadFromFile(string& editorText, string filename)
{
  ifstream inputFile;
  inputFile.open(filename);
  if(!inputFile.is_open()){
    return false;
  }
  inputFile.get(editorText);
  inputFile.close();
  return true;
}
