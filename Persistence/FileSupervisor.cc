
#include "FileSupervisor.h"

FileSupervisor::FileSupervisor()
{
}

FileSupervisor::~FileSupervisor()
{
}

bool FileSupervisor::saveToFile(string& editorText, string& filename)
{
    try{
        ofstream outputFile;
        string formattedFilename = "";
        formattedFilename.append(filename);
        formattedFilename.append(".scapl");
        outputFile.open(formattedFilename);
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

bool FileSupervisor::loadFromFile(string& editorText, string& filename)
{
    try{
        ifstream inputFile;
        string formattedFilename = "";
        formattedFilename.append(filename);
        formattedFilename.append(".scapl");

        inputFile.open(formattedFilename);
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
