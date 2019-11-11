#include "savewindow.h"
#include "ui_savewindow.h"

savewindow::savewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::savewindow)
{
    ui->setupUi(this);
}

savewindow::~savewindow()
{
    delete ui;
}

void savewindow::on_buttonBox_accepted()
{

}
