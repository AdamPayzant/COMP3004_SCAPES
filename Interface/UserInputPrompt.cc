
#include "UserInputPrompt.h"
#include "MainWindow.h"

UserInputPrompt::UserInputPrompt(QWidget *parent, std::string labelText) :
    QDialog(parent),
    ui(new Ui::UserInputPrompt)
{
    ui->setupUi(this);
    if(!labelText.empty())
    ui->userPromptLabel->setText(labelText.data());
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

void UserInputPrompt::setLabel(std::string text)
{
    if(!text.empty()){
        this->ui->userPromptLabel->setText(text.data());
    }
}
