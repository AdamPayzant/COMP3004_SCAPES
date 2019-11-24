
#include "Program.h"

Program::Program(std::string &f) {
    filename = f;
    stmts = new std::vector<Statement*>();
    ids = new std::vector<Identifier*>();
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
    // Just a big 'ole map to track statements with their switch options
    std::map<std::string, int> stats = {{"dci", 1}, {"dca", 2}, {"rdi", 3},{"prt",4}, {"mov", 5}, {"add", 6}, {"cmp", 7}, {"jls", 8}, {"jmr", 9}, {"jeq", 10}, {"jmp", 11}, {"end", 12}};

    for(std::string line ; getline(file, line); ) {
        // Had issues loading in blank lines, this should work around it
        if(line.size() != 0) { 
            if(line[0] != '#') {
                // I'd rather change this to a map of lambas, but scoping, so now we just get a map and if/else statments
                int type = stats[line.substr(0,3)];
                // Doing a massive if/else tree
                if(type == 1) {
                    stmts->push_back(new DeclIntStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                } 
                else if(type == 3) {
                    stmts->push_back(new ReadStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                }
                else if(type == 4) {
                    stmts->push_back(new PrintStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                }
                else if(type == 7) {
                    stmts->push_back(new CompStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                }
                else if(type == 9) {
                    stmts->push_back(new JMoreStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                }
                else if(type == 11) {
                    stmts->push_back(new JumpStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                }
                else if(type == 12) {
                    stmts->push_back(new EndStmt(this));
                    stmts->at(stmts->size()-1)->compile(line);
                }
                // TODO: Fix
                else {
                    // Check and make sure it's a valid statement
                    // Call statement constructor then give it a label
                    for(int i = 1; i < line.size(); i++) {
                        if(line.at(i) == ' ') {
                            if(line.at(i-1) == ':') {
                                // I hate that I copy and pasted this
                                int t2 = stats[line.substr(i+1,3)];
                                std::string st = line.substr(i, line.size() - i);
                                if(t2 == 1) {
                                    stmts->push_back(new DeclIntStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                } 
                                else if(t2 == 3) {
                                    stmts->push_back(new ReadStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                }
                                else if(t2 == 4) {
                                    stmts->push_back(new PrintStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                }
                                else if(t2 == 7) {
                                    stmts->push_back(new CompStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                }
                                else if(t2 == 9) {
                                    stmts->push_back(new JMoreStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                }
                                else if(t2 == 11) {
                                    stmts->push_back(new JumpStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                }
                                else if(t2 == 12) {
                                    stmts->push_back(new EndStmt(this));
                                    stmts->at(stmts->size()-1)->compile(st);
                                }

                                std::string lName = line.substr(0, i-1);
                                Label *l = new Label(lName);
                                ids->push_back(l);
                                stmts->at(stmts->size()-1)->setLabel(l);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Program::execute() {
    curStmt = stmts->at(0);
    stmtPos = 0;
    while(true) {
        curStmt->run();
        if(curStmt == nullptr) {
            break;
        }
        else {
            stmtPos++;
            curStmt = stmts->at(stmtPos);
        }
    }
}

void Program::print() {

}

void Program::changeStmt(Label *l) {
    for(int i = 0; i < stmts->size(); i++) {
        if(l == stmts->at(i)->getLabel()) {
            curStmt = stmts->at(i);
            stmtPos = i;
        }
    }
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
