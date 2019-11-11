#include "mainWindow.h"
#include "ui_mainwindow.h"
//#include "PersistenceManager.h"
#include <QFileDialog>
#include <QString>
#include <QInputDialog>
#include <QFile>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_compile_clicked(bool)
{

}

void MainWindow::on_pushButton_clicked()
{
    savewindow * s = new savewindow(this);
    s->show();

}

void MainWindow::on_compile_clicked()
{


}

void MainWindow::on_Openbutton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("openTxtFile"), "/home", tr("txt files (*.txt)"));
    string  fn = fileName.toUtf8().constData();
    string code;

    //loadFromFile( &editorText, fileName);
    QString qstr = QString::fromStdString(code);
    ui->textEdit->setText(qstr);

}

void MainWindow::on_save_clicked()
{



    QString dir;
    QString fn;
    while(dir==""){
        dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);

       fn = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                             tr("file name:"), QLineEdit::Normal,
                                             QDir::home().dirName());

        qDebug()<<"directory"<<dir;
        qDebug()<<"name"<<fn;
    }
    if(dir!=""){

        QString s = ui->textEdit->toPlainText();
        string directory =  dir.toUtf8().constData();
        string name= fn.toUtf8().constData();
        string program = s.toUtf8().constData();
        string path = directory +"/"+name;
       // SaveToFile( program,  dir);




    }






}

void MainWindow::on_compilebutton_clicked()
{
    
    QString qs = ui->textEdit->toPlainText();
    ui->textEdit->setText("recieved");
    std::string utf8_text = qs.toUtf8().constData();
    qDebug() << "Custom coordinate type:" << qs;
    
    
    //Program *newProgram = new Program(fileName);
    //newProgram->compile();


}
