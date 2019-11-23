#include "userinputdialog.h"
#include "ui_userinputdialog.h"

UserInputDialog::UserInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserInputDialog)
{
    ui->setupUi(this);
}

UserInputDialog::~UserInputDialog()
{
    delete ui;
}

void UserInputDialog::on_pushButton_clicked()
{

}
