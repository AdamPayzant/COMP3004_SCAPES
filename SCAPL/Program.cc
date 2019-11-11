#include "Program.h"

Program::Program(std::string &f) {
    filename = f;
    stmts = new std::vector<Statement*>();
    ids = new std::vector<Identifier*>();
}

Program::~Program() {
    for(int i = 0; i < stmts->size(); i++) {
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
    std::ifstream file(filename);
    // Just a big 'ole map to track statements with their switch options
    std::map<std::string, int> stats = {{"dci", 0}, {"dca", 1}, {"rdi", 2},{"prt",3}, {"mov", 4}, {"add", 5}, {"cmp", 6}, {"jls", 7}, {"jmr", 8}, {"jeq", 9}, {"jmp", 10}, {"end", 11}};

    for(std::string line ; getline(file, line); ) {
        std::cout << line << std::endl;
        // Had issues loading in blank lines, this should work around it
        if(line.size() != 0) { 
            // This removes any white space at the start of the line
            while(line.at(0) == ' ') {
                line.erase(line.begin());
            }
            // Removes whitespace from the end of the line
            while(*(line.end()) == ' '); {
                line.pop_back();
            }
            if(line[0] != '#') {
                // I'd rather change this to a map of lambas, but scoping, so now we just get a map and switch statments
                int type = stats[line.substr(0,3)];
                switch (type) {
                    case 0:
                        stmts->push_back(new DeclIntStmt(this));
                        stmts->at(stmts->size()-1)->compile(line);
                    /*case 1:
                        stmts->push_back(new DeclArrStmt(this));
                        stmts->at(stmts->size()-1)->compile(line); */
                    case 2:
                        stmts->push_back(new ReadStmt(this));
                        stmts->at(stmts->size()-1)->compile(line);
                    case 3:
                        stmts->push_back(new PrintStmt(this));
                        stmts->at(stmts->size()-1)->compile(line);
                    /*case 4:
                        stmts->push_back(new MovStmt(this));
                        stmts->at(stmts->size()-1)->compile(line); */
                    /*case 5:
                        stmts->push_back(new AddStmt(this));
                        stmts->at(stmts->size()-1)->compile(line); */
                    case 6:
                        stmts->push_back(new CompStmt(this));
                        stmts->at(stmts->size()-1)->compile(line);
                    /*case 7:
                        stmts->push_back(new JLessStmt(this));
                        stmts->at(stmts->size()-1)->compile(line); */
                    case 8:
                        stmts->push_back(new JMoreStmt(this));
                        stmts->at(stmts->size()-1)->compile(line);
                    /*case 9:
                        stmts->push_back(new JEqStmt(this));
                        stmts->at(stmts->size()-1)->compile(line);  */
                    case 10:
                        stmts->push_back(new JumpStmt(this));
                        stmts->at(stmts->size()-1)->compile(line);
                    case 11:
                        stmts->push_back(new EndStmt(this));
                        stmts->at(stmts->size()-1)->compile(line);
                    default:
                        // Check and make sure it's a valid statement
                        // Call statement constructor then give it a label
                        for(int i = 1; i < line.size(); i++) {
                            if(line.at(i) == ' ') {
                                if(line.at(i-1) == ':') {
                                    // I hate that I copy and pasted this switch statement
                                    int t2 = stats[line.substr(i,3)];
                                    switch (t2) {
                                        case 0:
                                            stmts->push_back(new DeclIntStmt(this));
                                            stmts->at(stmts->size()-1)->compile(line);
                                        /*case 1:
                                            stmts->push_back(new DeclArrStmt(this));
                                            stmts->at(stmts->size()-1)->compile(line);*/
                                        case 2:
                                            stmts->push_back(new ReadStmt(this));
                                            stmts->at(stmts->size()-1)->compile(line);
                                        case 3:
                                            stmts->push_back(new PrintStmt(this));
                                            stmts->at(stmts->size()-1)->compile(line);
                                        /*case 4:
                                            stmts->push_back(new MovStmt(this));
                                            stmts->at(stmts->size()-1)->compile(line); */
                                        /*case 5:
                                            stmts->push_back(new AddStmt(this));
                                            stmts->at(stmts->size()-1)->compile(line); */
                                        case 6:
                                            stmts->push_back(new CompStmt(this));
                                            stmts->at(stmts->size()-1)->compile(line);
                                        /*case 7:
                                            stmts->push_back(new JLessStmt(this));
                                            stmts->at(stmts->size()-1)->compile(line); */
                                        case 8:
                                            stmts->push_back(new JMoreStmt(this));
                                            stmts->at(stmts->size()-1)->compile(line);
                                        /*case 9:
                                            stmts->push_back(new JEqStmt(this));
                                            stmts->at(stmts->size()-1)->compile(line); */
                                        case 10:
                                            stmts->push_back(new JumpStmt(this));
                                            stmts->at(stmts->size()-1)->compile(line);
                                        case 11:
                                            stmts->push_back(new EndStmt(this));
                                            stmts->at(stmts->size()-1)->compile(line);
                                    }
                                    // Adding Label
                                    std::string lName = line.substr(0, i-1);
                                    Label *l = new Label(lName);
                                    ids->push_back(l);
                                    stmts->at(stmts->size()-1)->setLabel(l);
                                }
                                else {
                                    // This will eventually be an error
                                }
                            }
                        }
                }
            }
        }
    }
}

// TODO
void Program::execute() {

}

// TODO
void Program::print() {

}

void Program::getIds(std::vector<Identifier*> *i) {
    i = ids;
}

// returns the pointer to the comparison flag so compare statements can modify it
void Program::getCFlag(int *cFlag) {
    cFlag = &comparisonFlag;
}