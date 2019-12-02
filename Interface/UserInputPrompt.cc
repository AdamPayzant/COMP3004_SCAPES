
#include "UserInputPrompt.h"
#include "MainWindow.h"

UserInputPrompt::UserInputPrompt(QWidget *parent, std::string labelText, std::string operation) :
    QDialog(parent),
    ui(new Ui::UserInputPrompt)
{
    ui->setupUi(this);
    if(!labelText.empty())
    ui->userPromptLabel->setText(labelText.data());
    this->operation = operation;
}

UserInputPrompt::~UserInputPrompt()
{
    delete ui;
}

void UserInputPrompt::on_userPromptConfirmationBar_accepted()
{
    if(ui->userPromptTextEdit->toPlainText().size() != 0){
        string tempUserInput = (ui->userPromptTextEdit->toPlainText()).toUtf8().constData();
        if(!tempUserInput.empty()){
            ((MainWindow*) parent())->setTempUserInput(tempUserInput);
            this->close();
        }
    }
}

void UserInputPrompt::on_userPromptConfirmationBar_rejected()
{
    this->close();
}
