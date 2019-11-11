#include "openoption.h"
#include "ui_openoption.h"

openoption::openoption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::openoption)
{
    ui->setupUi(this);
}

openoption::~openoption()
{
    delete ui;
}
