
#include "FileSupervisor.h"

FileSupervisor::FileSupervisor()
{
}

FileSupervisor::~FileSupervisor()
{
}

bool FileSupervisor::saveToFile(string& editorText, string filename)
{
    try{
        ofstream outputFile;
        filename += ".scapl";
        outputFile.open(filename);
        if(!outputFile.is_open()){
            return false;
        }
        outputFile << editorText << endl;
        outputFile.close();
        return true;
    }catch(std::exception& exceptionRef){
        return false;
    }
}

bool FileSupervisor::loadFromFile(string& editorText, string filename)
{
    try{
        ifstream inputFile;
        inputFile.open(filename);
        if(!inputFile.is_open()){
          return false;
        }
        editorText = "";
        string currentLine;
        while(getline(inputFile, currentLine)){
          editorText.append(currentLine);
          editorText.append("\n");
        }
        inputFile.close();
        return true;
    }catch(std::exception& exceptionRef){
        return false;
    }

}
