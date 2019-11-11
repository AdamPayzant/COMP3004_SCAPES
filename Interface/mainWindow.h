#ifndef MAINWINDOW_H
#include <QMainWindow>
#include <QtGui>

#include "savewindow.h"
#include "openoption.h"
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     *
     *
     **/
    string& getEditorText();

    /**
     *
     *
     **/
    void setEditorText();



private slots:
    void on_menuButtonNewOption_triggered();

    void on_menuButtonOpenOption_triggered();

    void on_menuButtonSaveOption_triggered();

    void on_menuButtonCompileOption_triggered();

    void on_menuButtonRunOption_triggered();

    void on_menuButtonFuncDescOption_triggered();

    void on_menuButtonAboutOption_triggered();

private:
    Ui::MainWindow *ui;
    string  Filename;
};

#endif // MAINWINDOW_H
