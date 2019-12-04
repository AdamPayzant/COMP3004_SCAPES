
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

    std::ifstream file(filename + ".scapl");

    // Adds all of the labels to ids
    string tempString;
    for(std::string line ; getline(file, line); ) {
        if(line.size() != 0) {
            if(line[0] != '#') {
                tempString = "##_NOTVALID_##";
                for(int i = 1; i < line.size(); i++) {
                    if(line.at(i) == ' ') {
                        if(line.at(i-1) == ':') {
                            tempString = line.substr(0, i-1);
                            if(tempString.empty() || tempString.compare("##_NOTVALID_##")==0){
                                continue;
                            }
                            ids->push_back(new Label(tempString));
                        }
                    }
                }
            }
        }
    }

    // Just a big 'ole map to track statements with their switch options
    std::map<std::string, int> stats = {{"dci", 1}, {"dca", 2}, {"rdi", 3},{"prt",4}, {"mov", 5}, {"add", 6}, {"cmp", 7}, {"jls", 8}, {"jmr", 9}, {"jeq", 10}, {"jmp", 11}, {"end", 12}};

    for(std::string line ; getline(file, line); ) {
        // Had issues loading in blank lines, this should work around it
        if(line.size() != 0) {
            if(line[0] != '#') {
                // I'd rather change this to a map of lambas, but scoping, so now we just get a map and switch statments
                int type = stats[line.substr(0,3)];
                switch (type)
                {
                case 1:
                    stmts->push_back(new DeclIntStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 2:
                    stmts->push_back(new DeclArrStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 3:
                    stmts->push_back(new ReadStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 4:
                    stmts->push_back(new PrintStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 5:
                    stmts->push_back(new MovStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 6:
                    stmts->push_back(new AddStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 7:
                    stmts->push_back(new CompStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 8:
                    stmts->push_back(new JLessStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 9:
                    stmts->push_back(new JMoreStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 10:
                    stmts->push_back(new JEqStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 11:
                    stmts->push_back(new JumpStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 12:
                    stmts->push_back(new EndStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                default:
                    break;
                }
            }
        }
    }



    /*
    std::ifstream file(filename + ".scapl");

    // Adds all of the labels to ids
    for(std::string line ; getline(file, line); ) {
        if(line.size() != 0) { 
            if(line[0] != '#') {
                for(int i = 1; i < line.size(); i++) {
                    if(line.at(i) == ' ') {
                        if(line.at(i-1) == ':') {
                            ids->push_back(new Label(line.substr(0, i-1)));
                        }
                    }
                }
            }
        }
    }

    // Just a big 'ole map to track statements with their switch options
    std::map<std::string, int> stats = {{"dci", 1}, {"dca", 2}, {"rdi", 3},{"prt",4}, {"mov", 5}, {"add", 6}, {"cmp", 7}, {"jls", 8}, {"jmr", 9}, {"jeq", 10}, {"jmp", 11}, {"end", 12}};

    for(std::string line ; getline(file, line); ) {
        // Had issues loading in blank lines, this should work around it
        if(line.size() != 0) { 
            if(line[0] != '#') {
                // I'd rather change this to a map of lambas, but scoping, so now we just get a map and switch statments
                int type = stats[line.substr(0,3)];
                switch (type)
                {
                case 1:
                    stmts->push_back(new DeclIntStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 2:
                    stmts->push_back(new DeclArrStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 3:
                    stmts->push_back(new ReadStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 4:
                    stmts->push_back(new PrintStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 5:
                    stmts->push_back(new MovStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 6:
                    stmts->push_back(new AddStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 7:
                    stmts->push_back(new CompStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 8:
                    stmts->push_back(new JLessStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 9:
                    stmts->push_back(new JMoreStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 10:
                    stmts->push_back(new JEqStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 11:
                    stmts->push_back(new JumpStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                case 12:
                    stmts->push_back(new EndStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                    break;
                default:
                    for(int i = 1; i < line.size(); i++) {
                        if(line.at(i) == ' ') {
                            if(line.at(i-1) == ':') {
                                // I hate that I copy and pasted this
                                int t2 = stats[line.substr(i+1,3)];
                                std::string st = line.substr(i, line.size() - i);
                                switch (t2)
                                {
                                case 1:
                                    stmts->push_back(new DeclIntStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                    stmts->at(stmts->size()-1)->setLabel(getId(line.substr(0, i-1)));
                                    break;
                                case 2:
                                    stmts->push_back(new DeclArrStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                    stmts->at(stmts->size()-1)->setLabel(getId(line.substr(0, i-1)));
                                    break;
                                case 3:
                                    stmts->push_back(new ReadStmt(this));
                                    stmts->at(stmts->size()-1)->compile(line);
                                    stmts->at(stmts->size()-1)->setLabel(getId(line.substr(0, i-1)));
                                    break;
                                case 4:
                                    stmts->push_back(new PrintStmt(this));
                                    stmts->at(stmts->size()-1)->compile(line);
                                    stmts->at(stmts->size()-1)->setLabel(getId(line.substr(0, i-1)));
                                    break;
                                case 5:
                                    stmts->push_back(new MovStmt(this));
                                    stmts->at(stmts->size()-1)->compile(line);
                                    stmts->at(stmts->size()-1)->setLabel(getId(line.substr(0, i-1)));
                                    break;
                                case 6:
                                    stmts->push_back(new AddStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                    stmts->at(stmts->size()-1)->setLabel(getId(line.substr(0, i-1)));
                                    break;
                                case 7:
                                    stmts->push_back(new CompStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                    stmts->at(stmts->size()-1)->setLabel(getId(line.substr(0, i-1)));
                                    break;
                                case 8:
                                    stmts->push_back(new JLessStmt(this));
                                    stmts->at(stmts->size()-1)->compile(line);
                                    stmts->at(stmts->size()-1)->setLabel(getId(line.substr(0, i-1)));
                                    break;
                                case 9:
                                    stmts->push_back(new JMoreStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                    stmts->at(stmts->size()-1)->setLabel(getId(line.substr(0, i-1)));
                                    break;
                                case 10:
                                    stmts->push_back(new JEqStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                    stmts->at(stmts->size()-1)->setLabel(getId(line.substr(0, i-1)));
                                    break;
                                case 11:
                                    stmts->push_back(new JumpStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                    stmts->at(stmts->size()-1)->setLabel(getId(line.substr(0, i-1)));
                                    break;
                                case 12:
                                    stmts->push_back(new EndStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                    stmts->at(stmts->size()-1)->setLabel(getId(line.substr(0, i-1)));
                                    break;
                                default:
                                    // Error case
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
    */
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


void Program::setCompileValidityStatus(bool newValue)
{
    this->compileValidityStatus = newValue;
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
