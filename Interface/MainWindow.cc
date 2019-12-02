
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

string& MainWindow::getEditorText()
{
    this->editorSnapshot = (ui->sourceTextWindow->toPlainText()).toUtf8().constData();
    return editorSnapshot;
}

void MainWindow::refreshEditorText()
{
    ui->sourceTextWindow->setText(QString::fromStdString(editorSnapshot));
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

string& MainWindow::getTempUserInput()
{
    return this->tempUserInput;
}

void MainWindow::setTempUserInput(string& tempInput)
{
    this->tempUserInput = tempInput;
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
    ui->feedbackWindow->setPalette(feedbackPalette);
    ui->menuButtonSaveOption->setEnabled(true);
    ui->menuButtonCloseOption->setEnabled(true);
    ui->menuButtonCompileOption->setEnabled(true);
    ui->menuButtonRunOption->setEnabled(true);
}

void MainWindow::on_menuButtonSaveOption_triggered()
{
    UserInputPrompt* userInputPrompt = new UserInputPrompt(this, "Please provide the filename to be used for the source file:", "SaveSource");
    tempUserInput = "##_NOTVALID_##";
    userInputPrompt->exec();
    if(tempUserInput.empty() || tempUserInput.compare("##_NOTVALID_##")==0){
        ui->feedbackWindow->setText("Filename not provided or invalid.");
    }else{
        this->setProgramFilename(this->tempUserInput);
        this->mainController->clientRequestHandler("save");
    }
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

void MainWindow::prepareLoadedWindowState()
{
    ui->sourceTextWindow->setReadOnly(false);
    ui->sourceTextWindow->show();
    QPalette feedbackPalette;
    feedbackPalette.setColor(QPalette::Base, QColor(255,255,255));
    ui->feedbackWindow->setPalette(feedbackPalette);
    ui->menuButtonSaveOption->setEnabled(true);
    ui->menuButtonCloseOption->setEnabled(true);
    ui->menuButtonCompileOption->setEnabled(true);
    ui->menuButtonRunOption->setEnabled(true);
}
