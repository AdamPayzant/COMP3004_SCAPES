
#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainController(nullptr),
    programFilename("")
{
    ui->setupUi(this);
    prepareInitialWindowState();
}
MainWindow::~MainWindow()
{
    delete ui;
}

string MainWindow::getEditorText()
{
    return (ui->sourceTextWindow->toPlainText()).toUtf8().constData();
}

void MainWindow::setEditorText(string text)
{
    ui->sourceTextWindow->setText(QString::fromStdString(text));
}

void MainWindow::setFeedbackText(string text)
{
    ui->feedbackWindow->setText(QString::fromStdString(text));
}

MainController* MainWindow::getMainController()
{
    return this->mainController;
}

void MainWindow::setMainController(MainController* controllerPtr)
{
    this->mainController = controllerPtr;
}

string& MainWindow::getProgramFilename()
{
    return this->programFilename;
}

void MainWindow:: setProgramFilename(string newFilename)
{
    this->programFilename = newFilename;
}

void MainWindow::on_menuButtonNewOption_triggered()
{
    ui->sourceTextWindow->setReadOnly(false);
    ui->sourceTextWindow->setText("");
    ui->sourceTextWindow->show();
    QPalette feedbackPalette;
    feedbackPalette.setColor(QPalette::Base, QColor(255,255,255));
    ui->feedbackWindow->setText("Editor window cleared for new source file.\n"
                                "To save your source file, please use the 'Save' menu option.\n"
                                "To compile your source file, please use the 'Compile' menu option.\n"
                                "Clarifications on program details or functionality can be found under the "
                                "'Help' menu option of the menu bar.\n\n"
                                "Please note that creating a new source file using the 'New' menu option without "
                                "saving your current source file will result in the loss of any unsaved changes.");
    ui->feedbackWindow->setPalette(feedbackPalette);
    ui->menuButtonSaveOption->setEnabled(true);
    ui->menuButtonCloseOption->setEnabled(true);
}

void MainWindow::on_menuButtonOpenOption_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("txt files (*.txt)"));
    programFilename = fileName.toUtf8().constData();
    mainController->clientRequestHandler("load");

    ui->sourceTextWindow->setReadOnly(false);
    ui->sourceTextWindow->setText("");
    ui->sourceTextWindow->show();
    QPalette feedbackPalette;
    feedbackPalette.setColor(QPalette::Base, QColor(255,255,255));
    ui->feedbackWindow->setText("Editor window cleared for new source file.\n"
                                "To save your source file, please use the 'Save' menu option.\n"
                                "To compile your source file, please use the 'Compile' menu option.\n"
                                "Clarifications on program details or functionality can be found under the "
                                "'Help' menu option of the menu bar.\n\n"
                                "Please note that creating a new source file using the 'New' menu option without "
                                "saving your current source file will result in the loss of any unsaved changes.");
    ui->feedbackWindow->setPalette(feedbackPalette);
    ui->menuButtonSaveOption->setEnabled(true);
    ui->menuButtonCloseOption->setEnabled(true);
    ui->menuButtonCompileOption->setEnabled(true);
    ui->menuButtonRunOption->setEnabled(true);
}

void MainWindow::on_menuButtonSaveOption_triggered()
{
    SaveWindow* saveWindow = new SaveWindow(this);
    ui->menuButtonCompileOption->setEnabled(true);
    ui->menuButtonRunOption->setEnabled(true);
    saveWindow->show();
}

void MainWindow::on_menuButtonCloseOption_triggered()
{
    prepareInitialWindowState();
}

void MainWindow::on_menuButtonCompileOption_triggered()
{
    mainController->clientRequestHandler("compile");
    ui->feedbackWindow->setText("Compilation Attempted. Run Functionality is not implemented.");
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
    ui->sourceTextWindow->setText("");
    ui->sourceTextWindow->hide();
    QPalette feedbackPalette;
    feedbackPalette.setColor(QPalette::Base, QColor(220,220,220));
    ui->feedbackWindow->setText("To display the editor window, please create ('New' menu option) "
                                "or open ('Open' menu option) a file.");
    ui->feedbackWindow->setPalette(feedbackPalette);
    ui->feedbackWindow->setReadOnly(true);
    ui->menuButtonSaveOption->setEnabled(false);
    ui->menuButtonCloseOption->setEnabled(false);
    ui->menuButtonCompileOption->setEnabled(false);
    ui->menuButtonRunOption->setEnabled(false);
}
