
#include "SaveWindow.h"
#include "MainWindow.h"

SaveWindow::SaveWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveWindow)
{
    ui->setupUi(this);
}

SaveWindow::~SaveWindow()
{
    delete ui;
}

void SaveWindow::on_confirmationBar_accepted()
{
    string filename = (ui->filenameTextEdit->toPlainText()).toUtf8().constData();
    if(filename!=""){
        ((MainWindow*) parent())->setProgramFilename(filename);
        ((MainWindow*) parent())->getMainController()->clientRequestHandler("save");
        this->close();
    }
}
void SaveWindow::on_confirmationBar_rejected()
{
    this->close();
}
