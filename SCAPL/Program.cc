
#include "Program.h"
#include "./../ApplicationLogic/MainController.h"

Program::Program(std::string &f) {
    filename = f;
    stmts = new std::vector<Statement*>();
    ids = new std::vector<Identifier*>();
}

Program::Program(std::string &f, MainController* controllerPtr) {
    filename = f;
    stmts = new std::vector<Statement*>();
    ids = new std::vector<Identifier*>();
    this->controller = controllerPtr;
}

Program::~Program() {
    for(int i = 0; i < stmts->size(); i++) {
        std::cout << stmts->at(i)->getName() << std::endl;
        delete(stmts->at(i));
    }
    stmts->clear();
    delete(stmts);
    for(auto id : *ids) {
        delete(id);
    }
    ids->clear();
    delete(ids);
}

void Program::compile() {
    string errorText;
    try{
        bool labelFound;
        this->setCompileValidityStatus(true);
        ifstream inputFile;
        string formattedFilename = "";
        formattedFilename.append(filename);
        formattedFilename.append(".scapl");

        inputFile.open(formattedFilename);
        if(!inputFile.is_open()){
          this->setCompileValidityStatus(false);
          errorText = "Error occurred while opening file.";
          this->setCompileError(errorText);
          return;
        }

        //First loop to parse all source file labels for validity checks in second loop.
        string tempString;
        int i;
        int j;
        j = 0;
        for(std::string line ; getline(inputFile, line) && compileValidityStatus; ) {
            this->removeLeadingWhitespace(line);
            if(line.size() != 0) {
                if(line[0] == ':'){
                    this->setCompileValidityStatus(false);
                    errorText.clear();
                    errorText.append("Compilation Error: Invalid label on line ");
                    errorText.append(to_string(j+1));
                    this->setCompileError(errorText);
                    inputFile.close();
                    return;
                }
                if(line[0] != '#') {
                    tempString = "##_NOTVALID_##";
                    for(i = 0; i < line.size(); ++i) {
                        if(line.at(i) == ' ' || line.at(i) == '\"'){
                            break;
                        }
                        if(line.at(i) == ':') {
                            tempString = line.substr(0, i);
                            if(tempString.empty() || tempString.compare("##_NOTVALID_##")==0){
                                break;
                            }
                            ids->push_back(new Label(tempString));
                        }
                    }
                }
            }
            ++j;
        }
        inputFile.close();
        // Just a big 'ole map to track statements with their switch options
        std::map<std::string, int> stats = {{"dci", 1}, {"dca", 2}, {"rdi", 3},{"prt",4}, {"mov", 5}, {"add", 6}, {"cmp", 7}, {"jls", 8}, {"jmr", 9}, {"jeq", 10}, {"jmp", 11}, {"end", 12}};

        inputFile.open(formattedFilename);
        if(!inputFile.is_open()){
          this->setCompileValidityStatus(false);
          errorText = "Error occurred while opening file.";
          this->setCompileError(errorText);
          return;
        }

        j=0;
        for(std::string line ; getline(inputFile, line); ) {
            // Had issues loading in blank lines, this should work around it
            //line = line.substr(0,line.size()-1);
            if(line.size() > 0) {
                if(line[0] != '#') {
                    labelFound = false;
                    tempString = "##_NOTVALID_##";
                    for(i = 0; i < line.size(); ++i) {
                        if(line.at(i) == ' ' || line.at(i) == '\"'){
                            break;
                        }
                        if(line.at(i) == ':') {
                            tempString = line.substr(0, i);
                            if(tempString.empty() || tempString.compare("##_NOTVALID_##")==0){
                                break;
                            }
                            labelFound = true;
                            if(i+1 >= line.size()){
                                this->setCompileValidityStatus(false);
                                errorText.clear();
                                errorText.append("Line ");
                                errorText.append(to_string(j+1));
                                errorText.append(" is empty after its label.");
                                this->setCompileError(errorText);
                                inputFile.close();
                                return;
                            }
                            else{
                                line = line.substr(i+1);
                            }
                            break;
                        }
                    }

                    this->removeLeadingWhitespace(line);
                    if(line.size() < 5 && (line.compare((std::string) "end") != 0)){
                        this->setCompileValidityStatus(false);
                        errorText.clear();
                        errorText.append("Line ");
                        errorText.append(to_string(j+1));
                        errorText.append(" detected as too small to be a valid statement.");
                        this->setCompileError(errorText);
                        inputFile.close();
                        return;
                    }


                    // I'd rather change this to a map of lambas, but scoping, so now we just get a map and switch statments
                    int type = stats[line.substr(0,3)];
                    switch (type)
                    {
                    case 1:
                        stmts->push_back(new DeclIntStmt(this));
                        if(labelFound && !tempString.empty()){
                            stmts->at(stmts->size()-1)->setLabel(new Label(tempString));
                        }
                        stmts->at(stmts->size()-1)->compile(line);
                        if(!compileValidityStatus){
                            errorText = compileError;
                            errorText.append("\nError occurred on line ");
                            errorText.append(to_string(j+1));
                            this->setCompileError(errorText);
                            inputFile.close();
                            return;
                        }
                        break;
                    case 2:
                        stmts->push_back(new DeclArrStmt(this));
                        if(labelFound && !tempString.empty()){
                            stmts->at(stmts->size()-1)->setLabel(new Label(tempString));
                        }
                        stmts->at(stmts->size()-1)->compile(line);
                        if(!compileValidityStatus){
                            errorText = compileError;
                            errorText.append("\nError occurred on line ");
                            errorText.append(to_string(j+1));
                            this->setCompileError(errorText);
                            inputFile.close();
                            return;
                        }
                        break;
                    case 3:
                        stmts->push_back(new ReadStmt(this));
                        if(labelFound && !tempString.empty()){
                            stmts->at(stmts->size()-1)->setLabel(new Label(tempString));
                        }
                        stmts->at(stmts->size()-1)->compile(line);
                        if(!compileValidityStatus){
                            errorText = compileError;
                            errorText.append("\nError occurred on line ");
                            errorText.append(to_string(j+1));
                            this->setCompileError(errorText);
                            inputFile.close();
                            return;
                        }
                        break;
                    case 4:
                        stmts->push_back(new PrintStmt(this));
                        if(labelFound && !tempString.empty()){
                            stmts->at(stmts->size()-1)->setLabel(new Label(tempString));
                        }
                        stmts->at(stmts->size()-1)->compile(line);
                        if(!compileValidityStatus){
                            errorText = compileError;
                            errorText.append("\nError occurred on line ");
                            errorText.append(to_string(j+1));
                            this->setCompileError(errorText);
                            inputFile.close();
                            return;
                        }
                        break;
                    case 5:
                        stmts->push_back(new MovStmt(this));
                        if(labelFound && !tempString.empty()){
                            stmts->at(stmts->size()-1)->setLabel(new Label(tempString));
                        }
                        stmts->at(stmts->size()-1)->compile(line);
                        if(!compileValidityStatus){
                            errorText = compileError;
                            errorText.append("\nError occurred on line ");
                            errorText.append(to_string(j+1));
                            this->setCompileError(errorText);
                            inputFile.close();
                            return;
                        }
                        break;
                    case 6:
                        stmts->push_back(new AddStmt(this));
                        if(labelFound && !tempString.empty()){
                            stmts->at(stmts->size()-1)->setLabel(new Label(tempString));
                        }
                        stmts->at(stmts->size()-1)->compile(line);
                        if(!compileValidityStatus){
                            errorText = compileError;
                            errorText.append("\nError occurred on line ");
                            errorText.append(to_string(j+1));
                            this->setCompileError(errorText);
                            inputFile.close();
                            return;
                        }
                        break;
                    case 7:
                        stmts->push_back(new CompStmt(this));
                        if(labelFound && !tempString.empty()){
                            stmts->at(stmts->size()-1)->setLabel(new Label(tempString));
                        }
                        stmts->at(stmts->size()-1)->compile(line);
                        if(!compileValidityStatus){
                            errorText = compileError;
                            errorText.append("\nError occurred on line ");
                            errorText.append(to_string(j+1));
                            this->setCompileError(errorText);
                            inputFile.close();
                            return;
                        }
                        break;
                    case 8:
                        stmts->push_back(new JLessStmt(this));
                        if(labelFound && !tempString.empty()){
                            stmts->at(stmts->size()-1)->setLabel(new Label(tempString));
                        }
                        stmts->at(stmts->size()-1)->compile(line);
                        if(!compileValidityStatus){
                            errorText = compileError;
                            errorText.append("\nError occurred on line ");
                            errorText.append(to_string(j+1));
                            this->setCompileError(errorText);
                            inputFile.close();
                            return;
                        }
                        break;
                    case 9:
                        stmts->push_back(new JMoreStmt(this));
                        if(labelFound && !tempString.empty()){
                            stmts->at(stmts->size()-1)->setLabel(new Label(tempString));
                        }
                        stmts->at(stmts->size()-1)->compile(line);
                        if(!compileValidityStatus){
                            errorText = compileError;
                            errorText.append("\nError occurred on line ");
                            errorText.append(to_string(j+1));
                            this->setCompileError(errorText);
                            inputFile.close();
                            return;
                        }
                        break;
                    case 10:
                        stmts->push_back(new JEqStmt(this));
                        if(labelFound && !tempString.empty()){
                            stmts->at(stmts->size()-1)->setLabel(new Label(tempString));
                        }
                        stmts->at(stmts->size()-1)->compile(line);
                        if(!compileValidityStatus){
                            errorText = compileError;
                            errorText.append("\nError occurred on line ");
                            errorText.append(to_string(j+1));
                            this->setCompileError(errorText);
                            inputFile.close();
                            return;
                        }
                        break;
                    case 11:
                        stmts->push_back(new JumpStmt(this));
                        if(labelFound && !tempString.empty()){
                            stmts->at(stmts->size()-1)->setLabel(new Label(tempString));
                        }
                        stmts->at(stmts->size()-1)->compile(line);
                        if(!compileValidityStatus){
                            errorText = compileError;
                            errorText.append("\nError occurred on line ");
                            errorText.append(to_string(j+1));
                            this->setCompileError(errorText);
                            inputFile.close();
                            return;
                        }
                        break;
                    case 12:
                        stmts->push_back(new EndStmt(this));
                        if(labelFound && !tempString.empty()){
                            stmts->at(stmts->size()-1)->setLabel(new Label(tempString));
                        }
                        stmts->at(stmts->size()-1)->compile(line);
                        if(!compileValidityStatus){
                            errorText = compileError;
                            errorText.append("\nError occurred on line ");
                            errorText.append(to_string(j+1));
                            this->setCompileError(errorText);
                            inputFile.close();
                            return;
                        }
                        break;
                    default:
                        this->setCompileValidityStatus(false);
                        errorText.clear();
                        errorText.append("Unknown instruction on line ");
                        errorText.append(to_string(j+1));
                        errorText.append(".");
                        this->setCompileError(errorText);
                        inputFile.close();
                        return;
                    }
                }
            }
            ++j;
        }
        inputFile.close();
        return;
    }catch(std::exception& exceptionRef){
        this->setCompileValidityStatus(false);
        errorText = "Unexpected compilation error.";
        this->setCompileError(errorText);
        return;
    }
}

void Program::execute() {
    Statement *curStmt = stmts->at(0);
    stmtPos = 0;
    while(true) {
    std::cout<<"this is stmt#"<<stmtPos<<endl;
        if(stmtPos >= stmts->size()) {
            break;
        }
        else {
            stmtPos++;
            curStmt->run();
            curStmt = stmts->at(stmtPos);
        }
    }
}

void Program::print() {

}

void Program::addPrint(std::string o) {
    output.push_back(o);
}

Identifier* Program::getID(std::string target) {
    for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
        if((*iter)->getNameValue().compare(target) == 0) {
            return(*iter);
        }
    }
}

void Program::changeStmt(Label *target) {
    // Find the statement target matches
    for(int i = 0; i < stmts->size(); i++) {
        if(stmts->at(i)->getLabel() == target) {
            stmtPos = i;
        }
    }
}

void Program::end() {
    stmtPos = stmts->size();
}

std::vector<Identifier*>* Program::getIds() {
    return ids;
};
std::vector<Statement*>* Program::getStmts() {
    return stmts;
};

// returns the pointer to the comparison flag so compare statements can modify it
int Program::getCFlag() {
    return comparisonFlag;
}

void Program::setCFlag(int v) {
    comparisonFlag = v;
}

std::string& Program::getUserInput(){
    return this->controller->promptUserForInput();
}


bool Program::getCompileValidityStatus()
{
    return this->compileValidityStatus;
}


void Program::setCompileValidityStatus(bool newValue)
{
    this->compileValidityStatus = newValue;
}


std::string& Program::getCompileError()
{
    return this->compileError;
}


void Program::setCompileError(std::string& errorMessage)
{
    this->compileError = errorMessage;
}


int Program::removeLeadingWhitespace(std::string& currentLine)
{
    if(currentLine.empty()){
        return -1;
    }
    int i;
    for(i=0;i < currentLine.size();++i)
    {
        if(currentLine[i] != ' '){
            currentLine = currentLine.substr(i);
            return i;
        }
    }
    currentLine.clear();
    return -1;
}

int Program::parseNextArg(std::string& currentLine, std::string& nextArg)
{
    if(currentLine.empty() || currentLine[0] == '\0'){
        currentLine.clear();
        return -1;
    }
    if(currentLine[0] == ' ')
    {
        return -2;
    }

    int i;
    if(currentLine[0] == '\"'){
        for(i=1;i < currentLine.size();++i)
        {
            if(currentLine[i] == '\"'){
                if(i+1 >= currentLine.size()){
                    nextArg = currentLine;
                    return i+1;
                }
                else{
                    nextArg = currentLine.substr(0, i+1);
                    return i+1;
                }
            }
        }
        if(i == currentLine.size()){
            return -4;
        }
    }

    for(i=0;i < currentLine.size();++i)
    {
        if(currentLine[i] == ' ' || currentLine[i] == '\0'){
            nextArg = currentLine.substr(0, i);
            return i;
        }
    }
    if(i == currentLine.size()){
        nextArg = currentLine;
        return i;
    }
    return -3;
}

int Program::removeNextArg(std::string& currentLine)
{
    if(currentLine.empty() || currentLine[0] == '\0'){
        return -1;
    }
    if(currentLine[0] == ' ')
    {
        return -2;
    }

    int i;
    if(currentLine[0] == '\"'){
        for(i=1;i < currentLine.size();++i)
        {
            if(currentLine[i] == '\"'){
                if(i+1 >= currentLine.size()){
                    currentLine.clear();
                    return i+1;
                }
                else{
                    currentLine = currentLine.substr(i+1);
                    return i+1;
                }
            }
        }
        if(i == currentLine.size()){
            return -4;
        }
    }

    for(i=0;i < currentLine.size();++i)
    {
        if(currentLine[i] == ' ' || currentLine[i] == '\0'){
            currentLine = currentLine.substr(i);
            return i;
        }
    }
    if(i == currentLine.size()){
        currentLine.clear();
        return i;
    }
    return -3;
}


/*
int Program::parseNextArg(std::string& currentLine, std::string& nextArg)
{
    if(currentLine.empty() || currentLine[0] == '\0'){
        return -1;
    }
    if(currentLine[0] == ' ')
    {
        return -2;
    }

    int i;
    if(currentLine[0] == '\"'){
        for(i=0;i < currentLine.size();++i)
        {
            if(currentLine[i] == '\"'){
                if(i+1 == currentLine.size()){
                    nextArg = currentLine;
                    return i+1;
                }
                else{
                    nextArg = currentLine.substr(0, i+1);
                    return i+1;
                }
            }
        }
        if(i == currentLine.size()){
            return -4;
        }
    }

    for(i=0;i < currentLine.size();++i)
    {
        if(currentLine[i] == ' ' || currentLine[i] == '\0'){
            nextArg = currentLine.substr(0, i);
            return i;
        }
    }
    if(i == currentLine.size()){
        nextArg = currentLine;
        return i;
    }
    return -3;
}

int Program::removeNextArg(std::string& currentLine)
{
    if(currentLine.empty() || currentLine[0] == '\0'){
        return -1;
    }
    if(currentLine[0] == ' ')
    {
        return -2;
    }

    int i;
    if(currentLine[0] == '\"'){
        for(i=0;i < currentLine.size();++i)
        {
            if(currentLine[i] == '\"'){
                if(i+1 == currentLine.size()){
                    currentLine.clear();
                    return i+1;
                }
                else{
                    currentLine = currentLine.substr(i+1);
                    return i+1;
                }
            }
        }
        if(i == currentLine.size()){
            return -4;
        }
    }

    for(i=0;i < currentLine.size();++i)
    {
        if(currentLine[i] == ' ' || currentLine[i] == '\0'){
            currentLine = currentLine.substr(i);
            return i;
        }
    }
    if(i == currentLine.size()){
        currentLine.clear();
        return i;
    }
    return -3;
}
*/
