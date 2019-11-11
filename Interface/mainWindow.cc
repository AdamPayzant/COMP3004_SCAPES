#include "mainWindow.h"
#include "ui_mainWindow.h"
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
    prepareInitialWindowState();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_menuButtonNewOption_triggered()
{
    ui->sourceTextWindow->setReadOnly(false);
    ui->feedbackWindow->setText("");
    ui->sourceTextWindow->show();
    QPalette feedbackPalette;
    feedbackPalette.setColor(QPalette::Base, QColor(255,255,255));
    ui->feedbackWindow->setText("Editor window cleared for new source file.\n"
                                "To save your source file, please use the 'Save' menu option.\n"
                                "To compile your source file, please use the 'Compile' menu option.\n"
                                "Clarifications on program details or functionality can be found under the 'Help' menu option of the menu bar.\n\n"
                                "Please note that creating a new source file using the 'New' menu option without saving your current source file will "
                                "result in the loss of any unsaved changes.");
    ui->feedbackWindow->setPalette(feedbackPalette);
}

void MainWindow::on_menuButtonOpenOption_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), "/home", tr("txt files (*.txt)"));
    string  fn = fileName.toUtf8().constData();
    string code;

    //loadFromFile( &editorText, fileName);
    //QString qstr = QString::fromStdString(code);
    //ui->feedbackWindow->setText(qstr);
}

void MainWindow::on_menuButtonSaveOption_triggered()
{
    savewindow* s = new savewindow(this);
    s->show();

}

void MainWindow::on_menuButtonCompileOption_triggered()
{
}

void MainWindow::on_menuButtonRunOption_triggered()
{
}

void MainWindow::on_menuButtonFuncDescOption_triggered()
{
}

void MainWindow::on_menuButtonAboutOption_triggered()
{
}

void MainWindow::prepareInitialWindowState()
{
    ui->sourceTextWindow->setReadOnly(true);
    ui->sourceTextWindow->hide();
    QPalette feedbackPalette;
    feedbackPalette.setColor(QPalette::Base, QColor(220,220,220));
    ui->feedbackWindow->setText("To display the editor window, please create ('New' menu option) "
                                "or open ('Open' menu option) a file.");
    ui->feedbackWindow->setPalette(feedbackPalette);
    ui->feedbackWindow->setReadOnly(true);
}

/*
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
*/

/*
void MainWindow::on_compilebutton_clicked()
{
    
    QString qs = ui->textEdit->toPlainText();
    ui->textEdit->setText("recieved");
    std::string utf8_text = qs.toUtf8().constData();
    qDebug() << "Custom coordinate type:" << qs;
    
    
    //Program *newProgram = new Program(fileName);
    //newProgram->compile();


}
*/
